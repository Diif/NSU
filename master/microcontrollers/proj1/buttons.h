#ifndef BUTTONS_H
#define BUTTONS_H

#include "stm32f0xx.h"

typedef enum
{
	BUTTON_UP = 0,
	BUTTON_RIGHT,
	BUTTON_DOWN,
	BUTTON_LEFT,
	BUTTON_COUNT
} button_t;

#define DEBOUNCE_BOUNDARY 6

typedef enum {
    BUTTON_EVENT_NONE = 0,
    BUTTON_EVENT_PRESSED,
    BUTTON_EVENT_RELEASED
} button_event_t;

typedef struct {
    uint8_t candidate_state;
    uint8_t candidate_repentance;
		uint8_t state;
    button_event_t event;
} button_status_t;

void init_buttons(void);

uint8_t get_button_raw_val(button_t b);
button_event_t get_button_event(button_t button);
void update_buttons_status(void);


#endif
