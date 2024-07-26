

#include "include/relay_control.h"
#include "driver/gpio.h"
#include "hal/gpio_types.h"

// Define the GPIO pins for the relays
static relay relays[NUM_RELAYS] = {{.pin = GPIO_NUM_21, .state = RELAY_OFF},
                                   {.pin = GPIO_NUM_2, .state = RELAY_OFF},
                                   {.pin = GPIO_NUM_23, .state = RELAY_OFF},
                                   {.pin = GPIO_NUM_19, .state = RELAY_OFF}};

// Initialize all the relay pins as outputs
void init_relays(void)
{
    for (int i = 0; i < NUM_RELAYS; i++)
    {
        gpio_reset_pin(relays[i].pin);
        gpio_set_direction(relays[i].pin, GPIO_MODE_OUTPUT);
    }
}

// Set and update the state of the relay (ON or OFF)
void relay_set_state(int relay_index, relay_state state)
{
    gpio_set_level(relays[relay_index].pin, state);
    relays[relay_index].state = state;
}
