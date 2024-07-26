idf_component_register(SRCS "smart-panel.c"
                       INCLUDE_DIRS "."
                       REQUIRES http_server relay_control wifi power_monitor nvs_flash)
