#ifndef WIFI_H
#define WIFI_H

// Replace with your Wi-Fi network credentials
#define WIFI_SSID "TFD"
#define WIFI_PASS "awake1now"

// static void wifi_event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data);
void wifi_init(void);

#endif // !WIFI_H
