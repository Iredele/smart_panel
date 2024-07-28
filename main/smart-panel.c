#include "../components/http_server/include/http_server.h"
#include "../components/nv_storage/include/nv_storage.h"
#include "../components/relay_control/include/relay_control.h"
#include "../components/wifi/include/wifi.h"
#include "esp_err.h"
#include "esp_log.h"
#include <stdint.h>

#define TAG "main"

void app_main(void)
{
    ESP_LOGI(TAG, "Starting Smart Panel...");

    // Initialize data storage
    esp_err_t err = nvs_storage_init();
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to initialize data storage: %s", esp_err_to_name(err));
        return;
    }
    // Initialize gpio
    init_relays();

    nv_storage_set_string("wifi_ssid", "TFD");
    nv_storage_set_string("wifi_pass", "awake1now");

    // Initialize wifi
    wifi_init();

    // Start http server
    start_webserver();
}
