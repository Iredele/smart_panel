#include "include/nv_storage.h"
#include "esp_log.h"
#include "nvs.h"
#include "nvs_flash.h"

#define TAG "storage"

nvs_handle_t my_handle;

esp_err_t nvs_storage_init(void)
{
    // Initialize NVS
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);

    // Open
    err = nvs_open("storage", NVS_READWRITE, &my_handle);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "Error (%s) opening NVS handle!", esp_err_to_name(err));
        return err;
    }
    return ESP_OK;
}

esp_err_t nv_storage_set_int(const char *key, int32_t value)
{
    esp_err_t err = nvs_set_i32(my_handle, key, value);
    if (err != ESP_OK)
    {
        return err;
    }
    err = nvs_commit(my_handle);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to commit value for key %s", key);
    }
    return err;
}

esp_err_t nv_storage_get_int(const char *key, int32_t *value)
{
    esp_err_t err = nvs_get_i32(my_handle, key, value);

    return err;
}

esp_err_t nv_storage_set_string(const char *key, char *value)
{
    esp_err_t err = nvs_set_str(my_handle, key, value);
    if (err != ESP_OK)
    {
        return err;
    }
    err = nvs_commit(my_handle);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to commit string value for key %s", key);
    }
    return err;
}

esp_err_t nv_storage_get_string(const char *key, char *value, size_t max_length)
{
    size_t required_size;
    esp_err_t err = nvs_get_str(my_handle, key, NULL, &required_size);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to get string size for key %s", key);
        return err;
    }
    if (required_size > max_length)
    {
        ESP_LOGE(TAG, "Buffer size %d too small for key %s, required size is %d", max_length, key, required_size);
        return ESP_ERR_NVS_INVALID_LENGTH;
    }
    err = nvs_get_str(my_handle, key, value, &required_size);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to get string value for key %s", key);
    }
    return err;
}
