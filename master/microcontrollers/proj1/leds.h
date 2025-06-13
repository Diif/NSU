#ifndef LEDS_H
#define LEDS_H

typedef enum
{
	LED_UP = 0,
	LED_RIGHT,
	LED_DOWN,
	LED_LEFT,
	LED_COUNT
} led_t;

typedef enum
{
	LED_OFF = 0,
	LED_ON
} led_state_t;

typedef struct
{
	led_state_t state;
} led_status_t;

void init_leds(void);

void light_on(led_t x);
void light_off(led_t x);
void switch_led(led_t led);

#endif
