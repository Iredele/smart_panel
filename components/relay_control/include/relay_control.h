#include "soc/gpio_num.h"

#define NUM_RELAYS 4

typedef enum
{
    RELAY_OFF = 0,
    RELAY_ON
} relay_state;

typedef struct
{

    gpio_num_t pin;
    relay_state state;
} relay;

void init_relays(void);
static void save_relay_state(int relay_index);
void relay_set_state(int relay_index, relay_state state);
relay_state relay_get_state(int relay_index);
