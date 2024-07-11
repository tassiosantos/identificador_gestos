idf_component_register(SRCS "main.c" "image_sender.c" "led_control.c" "wifi_connection.c" "server_connection.c"
                    INCLUDE_DIRS "."
                    PRIV_REQUIRES esp_camera nvs_flash esp_wifi fatfs)


# add_subdirectory(protocol_examples_common)
# add_subdirectory(esp32-camera-master)

set(HDRS
    wifi_connection.h
    led_control.h
    image_sender.h
                )
                