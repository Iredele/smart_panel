#include "include/wifi.h"
#include "../../components/nv_storage/include/nv_storage.h"
#include "esp_err.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_netif_ip_addr.h"
#include "esp_wifi.h"
#include "freertos/task.h"
#include <stdio.h>
#include <string.h>

#define TAG "wifi"

static void wifi_event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START)
    {
        esp_wifi_connect();
    }
    else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED)
    {
        esp_wifi_connect();
        ESP_LOGI(TAG, "Retrying connection to the WiFi network...");
    }
    else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP)
    {
        ip_event_got_ip_t *event = (ip_event_got_ip_t *)event_data;
        ESP_LOGI(TAG, "got ip: " IPSTR, IP2STR(&event->ip_info.ip));
    }
}

void wifi_init(void)
{
    esp_netif_init();
    esp_event_loop_create_default();
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);

    esp_event_handler_instance_t instance_any_id;
    esp_event_handler_instance_t instance_got_ip;
    esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL, &instance_any_id);
    esp_event_handler_instance_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_event_handler, NULL, &instance_got_ip);

    char wifi_ssid[32];
    char wifi_pass[32];
    esp_err_t err = nv_storage_get_string("wifi_ssid", wifi_ssid, sizeof(wifi_ssid));
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to get WiFi SSID from NVS: %s", esp_err_to_name(err));
        return;
    }
    err = nv_storage_get_string("wifi_pass", wifi_pass, sizeof(wifi_pass));
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to get WiFi password from NVS: %s", esp_err_to_name(err));
        return;
    }

    wifi_config_t wifi_config = {
        .sta =
            {
                .ssid = "",
                .password = "",
            },
    };
    strlcpy((char *)wifi_config.sta.ssid, wifi_ssid, sizeof(wifi_config.sta.ssid));
    strlcpy((char *)wifi_config.sta.password, wifi_pass, sizeof(wifi_config.sta.password));
    esp_wifi_set_mode(WIFI_MODE_STA);
    esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config);
    esp_wifi_start();
}
