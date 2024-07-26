#include "../components/http_server/include/http_server.h"
#include "../components/relay_control/include/relay_control.h"
#include "../components/wifi/include/wifi.h"
#include "nvs_flash.h"

void app_main(void)
{
    // Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    // Initialize gpio
    init_relays();

    // Initialize wifi
    wifi_init();

    // Start http server
    start_webserver();
}
