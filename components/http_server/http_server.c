
#include "include/http_server.h"
#include "../relay_control/include/relay_control.h"
#include "driver/gpio.h"
#include "esp_http_server.h"

static const char *TAG = "http";

esp_err_t led_on_handler(httpd_req_t *req)
{
    // gpio_set_level(GPIO_NUM_2, 1);
    relay_set_state(1, RELAY_ON);
    httpd_resp_send(req, "LED is ON", HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

esp_err_t led_off_handler(httpd_req_t *req)
{
    // gpio_set_level(GPIO_NUM_2, 0);
    relay_set_state(1, RELAY_OFF);
    httpd_resp_send(req, "LED is OFF", HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

httpd_uri_t led_on_uri = {.uri = "/led_on", .method = HTTP_GET, .handler = led_on_handler, .user_ctx = NULL};

httpd_uri_t led_off_uri = {.uri = "/led_off", .method = HTTP_GET, .handler = led_off_handler, .user_ctx = NULL};

void start_webserver(void)
{
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    httpd_handle_t server = NULL;

    if (httpd_start(&server, &config) == ESP_OK)
    {
        httpd_register_uri_handler(server, &led_on_uri);
        httpd_register_uri_handler(server, &led_off_uri);
    }
}
