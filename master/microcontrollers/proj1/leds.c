#include "leds.h"

#include "stm32f0xx.h"

static led_status_t leds[LED_COUNT];

void init_leds(void)
{
	/* PC6 - PC9 - LEDs */
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN;

	GPIOC->MODER &= ~GPIO_MODER_MODER6;
			GPIOC->MODER |= GPIO_MODER_MODER6_0;
	GPIOC->MODER &= ~GPIO_MODER_MODER9;
			GPIOC->MODER |= GPIO_MODER_MODER9_0;
	GPIOC->MODER &= ~GPIO_MODER_MODER8;
			GPIOC->MODER |= GPIO_MODER_MODER8_0;
	GPIOC->MODER &= ~GPIO_MODER_MODER7;
			GPIOC->MODER |= GPIO_MODER_MODER7_0;
}

void light_on(led_t x)
{
	switch (x)
	{
		case LED_LEFT:
			GPIOC->ODR |= GPIO_ODR_6;
			break;
		case LED_UP:
			GPIOC->ODR |= GPIO_ODR_9;
			break;
		case LED_DOWN:
			GPIOC->ODR |= GPIO_ODR_8;
			break;
		case LED_RIGHT:
			GPIOC->ODR |= GPIO_ODR_7;
			break;
		case LED_COUNT:
			while(1);
	}
}

void light_off(led_t x)
{
	switch (x)
	{
		case LED_LEFT:
			GPIOC->ODR &= ~GPIO_ODR_6;
			break;
		case LED_UP:
			GPIOC->ODR &= ~GPIO_ODR_9;
			break;
		case LED_DOWN:
			GPIOC->ODR &= ~GPIO_ODR_8;
			break;
		case LED_RIGHT:
			GPIOC->ODR &= ~GPIO_ODR_7;
			break;
		case LED_COUNT:
			while(1);
	}
}

void switch_led(led_t led)
{
	if (leds[led].state == LED_ON)
	{
		light_off(led);
		leds[led].state = LED_OFF;
	}
	else
	{
		light_on(led);
		leds[led].state = LED_ON;
	}
}
