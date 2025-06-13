#include "buttons.h"

static button_status_t buttons[BUTTON_COUNT];

void init_buttons(void)
{
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
	/* PAO0 button */
	GPIOA->MODER &= ~GPIO_MODER_MODER0;
	
	/* matrix buttons to turn on */
	GPIOA->MODER &= ~GPIO_MODER_MODER15;
			GPIOA->MODER |= GPIO_MODER_MODER15_0;
	GPIOC->MODER &= ~GPIO_MODER_MODER12;
			GPIOC->MODER |= GPIO_MODER_MODER12_0;
			
	/* matrix buttons to get info from */
	GPIOA->MODER &= ~GPIO_MODER_MODER4;
	GPIOA->MODER &= ~GPIO_MODER_MODER5;
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR4;
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR5;
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR4_1;
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR5_1;
}

uint8_t get_button_raw_val(button_t b)
{
	uint8_t but_val = 0;
	
	switch (b)
	{
		case BUTTON_LEFT:
			GPIOA->ODR |= GPIO_ODR_15;
			but_val = GPIOA->IDR & GPIO_IDR_4;
			GPIOA->ODR &= ~GPIO_ODR_15;
			break;
		case BUTTON_RIGHT:
			GPIOA->ODR |= GPIO_ODR_15;
			but_val = GPIOA->IDR & GPIO_IDR_5;
			GPIOA->ODR &= ~GPIO_ODR_15;
			break;
		case BUTTON_DOWN:
			GPIOC->ODR |= GPIO_ODR_12;
			but_val = GPIOA->IDR & GPIO_IDR_5;
			GPIOC->ODR &= ~GPIO_ODR_12;
			break;
		case BUTTON_UP:
			GPIOC->ODR |= GPIO_ODR_12;
			but_val = GPIOA->IDR & GPIO_IDR_4;
			GPIOC->ODR &= ~GPIO_ODR_12;
			break;
		case BUTTON_COUNT:
			while(1);
	}
	return but_val;
}

button_event_t get_button_event(button_t button)
{
	button_status_t* button_ptr = &buttons[button];
	button_event_t event = button_ptr->event;
	button_ptr->event = BUTTON_EVENT_NONE;
	return event;
}

void update_buttons_status(void) {
	button_status_t* buttons_arr = buttons;
	int count = BUTTON_COUNT;
	for (int i = 0; i < count; i++)
	{
		button_t button = (button_t )i;
		button_status_t* status = &buttons_arr[button];
		//status->event = BUTTON_EVENT_NONE;

    uint8_t rawState = get_button_raw_val(button);

    if (rawState != status->candidate_state)
		{
        status->candidate_state = rawState;
        status->candidate_repentance = 0;
    }
		
		if (status->candidate_repentance >= DEBOUNCE_BOUNDARY)
		{
			if (status->state != status->candidate_state)
			{
					status->state = status->candidate_state;
					status->event = (status->candidate_state != 0) ? BUTTON_EVENT_PRESSED : BUTTON_EVENT_RELEASED;
			}
    }
		else
		{
			status->candidate_repentance += 1;
		}
	}
}
