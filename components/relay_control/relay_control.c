

#include "include/relay_control.h"
#include "../../components/nv_storage/include/nv_storage.h"
#include "driver/gpio.h"
#include "esp_err.h"
#include "esp_log.h"
#include "hal/gpio_types.h"
#include <stdint.h>
#include <stdio.h>

#define TAG "relays"
// Define the GPIO pins for the relays
static relay relays[NUM_RELAYS] = {{.pin = GPIO_NUM_21, .state = RELAY_OFF},
                                   {.pin = GPIO_NUM_2, .state = RELAY_OFF},
                                   {.pin = GPIO_NUM_23, .state = RELAY_OFF},
                                   {.pin = GPIO_NUM_19, .state = RELAY_OFF}};

// Initialize all the relay pins as outputs
void init_relays(void)
{
    relay_state state = RELAY_OFF;

    for (int i = 0; i < NUM_RELAYS; i++)
    {
        char key[15];
        snprintf(key, sizeof(key), "relay_state_%d", i);
        esp_err_t err = nv_storage_get_int(key, (int32_t *)&state);
        if (err == ESP_OK)
        {
            relays[i].state = (relay_state)state;
        }
        else
        {
            ESP_LOGE(TAG, "Relay %d not Initialized in nv storage", i);
        }
        gpio_reset_pin(relays[i].pin);
        gpio_set_direction(relays[i].pin, GPIO_MODE_OUTPUT);
        gpio_set_level(relays[i].pin, relays[i].state);
    }
}

static void save_relay_state(int relay_index)
{
    char key[15];
    snprintf(key, sizeof(key), "relay_state_%d", relay_index);
    esp_err_t err = nv_storage_set_int(key, relays[relay_index].state);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to save state for relay %d", relay_index);
    }
}

// Set and update the state of the relay (ON or OFF)
void relay_set_state(int relay_index, relay_state state)
{
    gpio_set_level(relays[relay_index].pin, state);
    relays[relay_index].state = state;
    save_relay_state(relay_index);
}

// Get the state of a specific relay
relay_state relay_get_state(int relay_index)
{
    return relays[relay_index].state;
}
