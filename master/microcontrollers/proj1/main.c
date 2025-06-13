#include "stm32f0xx.h"

#include "leds.h"
#include "buttons.h"

#include <stdbool.h>
#include <stddef.h>

/*
static int movement = 1;
static led_t next_led = LED_UP;

*/

static volatile uint32_t time_ms = 0;
static volatile uint32_t time_for_adc_ms = 0;

static void init_spi2(void)
{
	//PB15_SPI12_MOSI
	//PB13_SPI12_SCK
	//ref. manual - p. 801 (28.9)
	
	RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;
	
	SPI2->CR1 = SPI_CR1_SSM | SPI_CR1_SSI | SPI_CR1_BR | SPI_CR1_MSTR;
	SPI2->CR2 = SPI_CR2_DS | SPI_CR2_RXNEIE;
	SPI2->CR1 |= SPI_CR1_SPE;
		
	NVIC_EnableIRQ(SPI2_IRQn);
	NVIC_SetPriority(SPI2_IRQn, 0);

	RCC->AHBENR |= RCC_AHBENR_GPIOBEN | RCC_AHBENR_GPIOAEN;
	GPIOA->MODER &= ~GPIO_MODER_MODER8;
	GPIOA->MODER |= GPIO_MODER_MODER8_0;
	
	GPIOB->AFR[1] &= ~((0xF << (4 * (13 - 8))) | (0xF << (4 * (15 - 8))));
  GPIOB->AFR[1] |= ((0 << (4 * (13 - 8))) | (0 << (4 * (15 - 8))));
	
	GPIOB->MODER &= ~(GPIO_MODER_MODER13 | GPIO_MODER_MODER15);
	GPIOB->MODER |= GPIO_MODER_MODER13_1 | GPIO_MODER_MODER15_1;	
}


#define ADC_ARRAY_SIZE 1024
static uint16_t ADC_array[ADC_ARRAY_SIZE];

static void adc_init(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;
	
	GPIOA->MODER &= ~GPIO_MODER_MODER0;
	GPIOA->MODER |= GPIO_MODER_MODER0_1 | GPIO_MODER_MODER0_0;
	
	if ((ADC1->CR & ADC_CR_ADEN) != 0)
	{
		ADC1->CR |= ADC_CR_ADDIS;
	}
	while ((ADC1->CR & ADC_CR_ADEN) != 0){}

	ADC1->CFGR1 &= ~ADC_CFGR1_DMAEN;
	ADC1->CR |= ADC_CR_ADCAL;
	while ((ADC1->CR & ADC_CR_ADCAL) != 0){}
	if ((ADC1->ISR & ADC_ISR_ADRDY) != 0)
	{
		ADC1->ISR |= ADC_ISR_ADRDY;
	}
	ADC1->CR |= ADC_CR_ADEN;
	while ((ADC1->ISR & ADC_ISR_ADRDY) == 0){}

	ADC1->CFGR1 |= ADC_CFGR1_CONT | ADC_CFGR1_DMAEN | ADC_CFGR1_DMACFG | ADC_CFGR1_OVRMOD;
	ADC1->CHSELR |= ADC_CHSELR_CHSEL1;

	DMA1_Channel1->CPAR = (uint32_t) (&(ADC1->DR));
	DMA1_Channel1->CMAR = (uint32_t)(ADC_array);
	DMA1_Channel1->CNDTR = ADC_ARRAY_SIZE;
	DMA1_Channel1->CCR |= DMA_CCR_MINC | DMA_CCR_MSIZE_0 | DMA_CCR_PSIZE_0 | DMA_CCR_TCIE | DMA_CCR_HTIE | DMA_CCR_CIRC;
	DMA1_Channel1->CCR |= DMA_CCR_EN;

	// ADC1->IER |= ADC_IER_EOCIE;

	//NVIC_EnableIRQ(ADC1_COMP_IRQn);
	NVIC_EnableIRQ(DMA1_Channel1_IRQn);
	NVIC_SetPriority(DMA1_Channel1_IRQn, 1);
}

#include <math.h>
#define SAMPLES 512
/* 8 000 000 base freq; with PERIOD 7999 -> 1000 cycles per second with 512 samples = 2 sine-like signals per second */
#define PERIOD 79
static uint16_t sineTable[SAMPLES];
static uint16_t sineTable2[SAMPLES];

static void initSineTable(uint16_t period) {
  for (int i = 0; i < SAMPLES; ++i) {
    float theta = (2.0f * 3.1415926535f * i) / SAMPLES;
    // shift sin from [-1..1] to [0..1] then scale by timer period
    sineTable[i] = (uint16_t)((sinf(theta) * 0.5f + 0.5f) * period);
  }
	for (int i = 0; i < SAMPLES; ++i) {
    float theta = ((2.0f * 3.1415926535f + 0.5f * 3.1415926535f) * i) / SAMPLES;
    // shift sin from [-1..1] to [0..1] then scale by timer period
    sineTable2[i] = (uint16_t)((sinf(theta) * 0.5f + 0.5f) * period);
  }
}

static void initPWM(void)
{
	// 1) Clocks
	initSineTable(PERIOD);
	RCC->AHBENR  |= RCC_AHBENR_GPIOCEN;
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

	// 2) GPIOC AF0 on PC8, PC9
	GPIOC->AFR[1] &= ~((0xF << (4*0)) | (0xF << (4*1))); // clear AF for pins 8,9
	GPIOC->MODER &= ~(GPIO_MODER_MODER8 | GPIO_MODER_MODER9);
	GPIOC->MODER |=  GPIO_MODER_MODER8_1 | GPIO_MODER_MODER9_1;

	// 3) TIM3 setup for ??20 kHz ??PWM
	TIM3->PSC = 0;
	TIM3->ARR = PERIOD;
	// output mode
	TIM3->CCMR2 &= ~(TIM_CCMR2_CC3S | TIM_CCMR2_CC4S);
	// PWM mode 1 on CH3, CH4
	TIM3->CCMR2 = TIM_CCMR2_OC3M_1 
            | TIM_CCMR2_OC3M_2 
            | TIM_CCMR2_OC4M_1 
            | TIM_CCMR2_OC4M_2;
	
	TIM3->CCR3 = sineTable[0];
	TIM3->CCR4 = sineTable[0];
	
		// 1) Enable the Update Interrupt in the DMA/Interrupt Enable Register
	TIM3->DIER |= TIM_DIER_UIE;    // UIE = Update Interrupt Enable

	// 2) Enable the TIM3 IRQ in the NVIC
	NVIC_SetPriority(TIM3_IRQn, 2);
	NVIC_EnableIRQ(TIM3_IRQn);

	TIM3->CCER  = TIM_CCER_CC3E | TIM_CCER_CC4E;
	TIM3->CR1  |= TIM_CR1_CEN;
}

static void init(void)
{
	//init_leds();
	init_buttons();
	init_spi2();
	initPWM();
	//adc_init();

	SystemCoreClockUpdate();

	SysTick->LOAD = SystemCoreClock / 1000 - 1;
	SysTick->VAL = 0;
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_TICKINT_Msk;
	// SysTick_Config(SystemCoreClock / 10);
}

#define COLUMNS_NUM 8

static volatile uint16_t curCol = 0;

static volatile uint16_t display[COLUMNS_NUM] = 
	{
    0x8000,
    0x0000,
    0x0000,
    0x0000,
    0x8000,
    0x0000,
    0x0000,
    0x0000
  };

static int idxs[] = {1, 1};
static int coeffs[] = {1, 1};

static void add_one_coeff(uint16_t *d, int start_col, int *coeff)
{
	start_col = start_col + (*coeff) / 8;
	d[start_col] = (d[start_col] >> 1) + 0x8000;
	++(*coeff);
}

static void remove_one_coeff(uint16_t *d, int start_col, int *coeff)
{
	--(*coeff);
	start_col = start_col + (*coeff) / 8;
	d[start_col] = (d[start_col] << (uint16_t) 1);
}
	
#define BIT(x) (1 << x)
	
static void transmit_data_to_matrix_nonblocking(uint32_t data)
{
	GPIOA->BSRR = GPIO_BSRR_BS_8;
	GPIOA->BSRR = GPIO_BSRR_BR_8;
	SPI2->DR = data;
}

void SysTick_Handler(void)
{
	time_ms += 1;
	update_buttons_status();
}
/*
static void upd_nex_led(void)
{
	next_led +=  movement;
	next_led %= LED_COUNT;
}

static int button_changed(void)
{
	int but_val = GPIOA->IDR & GPIO_IDR_0;
	if (but_val == 1 && last_but_val != 1)
	{
		movement = movement == 1? -1 : 1;
		last_but_val  = but_val;
		return 1;
	}
	else if (but_val == 0 && last_but_val == 1)
	{
		last_but_val  = but_val;
	}
	return 0;
}

static void light_for_a_sec(led_t x)
{
	light_on(x);
	unsigned long long start = time_ms;
	while ((time_ms - start) < 1000){}
	light_off(x);
}

static void
update_led_state(button_t b, led_t led)
{
	if (get_button_event(b)== BUTTON_EVENT_PRESSED)
	{
		switch_led(led);
	}
}
*/

static void handle_button_state(button_t b)
{
	if (get_button_event(b)== BUTTON_EVENT_PRESSED)
	{
		switch(b)
		{
			case BUTTON_LEFT:
				if (coeffs[0] > 1)
					remove_one_coeff(display, 0, coeffs);
				break;
			case BUTTON_RIGHT:
				if (coeffs[0] < 32)
					add_one_coeff(display, 0, coeffs);
				break;
			case BUTTON_DOWN:
				if (coeffs[1] > 1)
					remove_one_coeff(display, 4, coeffs + 1);
				break;
			case BUTTON_UP:
				if (coeffs[1] < 32)
					add_one_coeff(display, 4, coeffs + 1);
				break;
			case BUTTON_COUNT:
				while(1);
		}
	}
}
	
int main(void)
{
	init();
	
	/* to enable interrupts */
	transmit_data_to_matrix_nonblocking(display[curCol] | BIT(curCol));
	curCol = (curCol + 1) % COLUMNS_NUM;
	/*ADC1->CR |= ADC_CR_ADSTART;
	switch_led(LED_UP);
	switch_led(LED_DOWN);*/
	while (1)
	{
		handle_button_state(BUTTON_UP);
		handle_button_state(BUTTON_DOWN);
		handle_button_state(BUTTON_LEFT);
		handle_button_state(BUTTON_RIGHT);
		//for (int i = 0; i < 10000000;i++);
		//update_led_state(BUTTON_UP, LED_UP);
		//update_led_state(BUTTON_DOWN, LED_DOWN);
		//update_led_state(BUTTON_RIGHT, LED_RIGHT);
		//update_led_state(BUTTON_LEFT, LED_LEFT);
		//update_button_status(BUTTON_RIGHT);
		//update_button_status(BUTTON_LEFT);
		//update_but_state();
		//light_for_a_sec(next_led);
		//upd_nex_led();
	}
}

void SPI2_IRQHandler(void) {
  if (SPI2->SR & SPI_SR_RXNE)
	{
    volatile uint32_t recv = SPI2->DR;
    transmit_data_to_matrix_nonblocking(display[curCol] | BIT(curCol));
		curCol = (curCol + 1) % COLUMNS_NUM;
  }
}

/*
static uint16_t map(uint16_t x,
                    uint16_t in_min,
                    uint16_t in_max,
                    uint16_t out_min,
                    uint16_t out_max)
{
    // Prevent division by zero
    if (in_max == in_min)
		{
			return out_min;
    }

    uint32_t numerator   = (uint32_t)(x - in_min) * (out_max - out_min);
    uint32_t denominator = (uint32_t)(in_max - in_min);

    uint16_t result = (uint16_t)(numerator / denominator + out_min);
    return result;
}

static void shiftDisplayLeft(void) {
    for (int i = 0; i < COLUMNS_NUM - 1; ++i) {
        display[i] = display[i + 1];
    }
}

void ADC1_IRQHandler(void)
{
	uint16_t data;
	uint16_t line;

	if(ADC1->ISR & ADC_ISR_EOC)
	{
		data = (uint16_t ) ADC1->DR;
		if (time_for_adc_ms >= 50)
		{
			line = map(data, 0, 4095, 0, 7);
			shiftDisplayLeft();
			display[COLUMNS_NUM - 1] = (uint16_t) ((1 << 8) << line);
			time_for_adc_ms = 0;
		}
		ADC1->CR |= ADC_CR_ADSTART;
	}
}

static void
onDmaTransferComplete(uint16_t *arr, uint32_t size)
{
	uint32_t data = 0;
	uint16_t line;
	
	for(uint32_t i = 0; i < size; i++)
	{
		data += (uint16_t ) arr[i];
	}
	data /= size;
	if (time_for_adc_ms >= 50)
	{
		line = map((uint16_t) data, 0, 4095, 0, 7);
		shiftDisplayLeft();
		display[COLUMNS_NUM - 1] = (uint16_t) ((1 << 8) << line);
		time_for_adc_ms = 0;
	}
}

void DMA1_Ch1_IRQHandler(void)
{
	if (DMA1->ISR & DMA_ISR_TCIF1)
	{
		DMA1->IFCR = DMA_IFCR_CTCIF1;
		onDmaTransferComplete(ADC_array, ADC_ARRAY_SIZE / 2);
  }
	if (DMA1->ISR & DMA_ISR_HTIF1)
	{
		DMA1->IFCR = DMA_IFCR_CHTIF1;
		onDmaTransferComplete(ADC_array + ADC_ARRAY_SIZE / 2, ADC_ARRAY_SIZE / 2);
  }
}
*/

void	TIM3_IRQHandler(void)
{
    if (TIM3->SR & TIM_SR_UIF) {
			TIM3->SR &= ~TIM_SR_UIF;
			TIM3->CCR3 = sineTable[idxs[0]];
			TIM3->CCR4 = sineTable2[idxs[1]];
			idxs[0] += coeffs[0];
			idxs[1] += coeffs[1];
			if (idxs[0] >= SAMPLES)
				idxs[0] = 0;
			if (idxs[1] >= SAMPLES)
				idxs[1] = 0;
    }
}
