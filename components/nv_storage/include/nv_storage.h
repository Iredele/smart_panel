#include "esp_err.h"
#include <stdint.h>

esp_err_t nvs_storage_init(void);
esp_err_t nv_storage_set_int(const char *key, int32_t value);
esp_err_t nv_storage_get_int(const char *key, int32_t *value);
esp_err_t nv_storage_set_string(const char *key, char *value);
esp_err_t nv_storage_get_string(const char *key, char *value, size_t max_length);
