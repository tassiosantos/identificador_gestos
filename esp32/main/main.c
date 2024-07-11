#include "esp_camera.h"
#include "esp_system.h"
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "nvs_flash.h"

#include "wifi_connection.h"
#include "server_connection.h"
#include "led_control.h"
#include "image_sender.h"
#include "esp_log.h"

#include "driver/gpio.h"


#define TAG "esp32-cam_main"

// Configuração da câmera
camera_config_t camera_config = {
    .ledc_channel = LEDC_CHANNEL_0,
    .ledc_timer = LEDC_TIMER_0,
    .pin_pwdn = 32,
    .pin_reset = -1,
    .pin_xclk = 0,
    .pin_sscb_sda = 26,
    .pin_sscb_scl = 27,
    .pin_d7 = 35,
    .pin_d6 = 34,
    .pin_d5 = 39,
    .pin_d4 = 36,
    .pin_d3 = 21,
    .pin_d2 = 19,
    .pin_d1 = 18,
    .pin_d0 = 5,
    .pin_vsync = 25,
    .pin_href = 23,
    .pin_pclk = 22,
    .xclk_freq_hz = 20000000,
    .pixel_format = PIXFORMAT_JPEG, 
    .frame_size = FRAMESIZE_VGA,
    .jpeg_quality = 35,
    .fb_count = 2
};

void app_main(){
    //Inicia os LEDs
    init_leds();
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        // NVS partition was truncated and needs to be erased
        ESP_ERROR_CHECK(nvs_flash_erase());
        // Retry nvs_flash_init
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);

    wifi_connect();
    server_connect();
    
    // Inicializar a câmera
    esp_err_t erro = esp_camera_init(&camera_config);
    if (erro != ESP_OK) {
        ESP_LOGE(TAG, "Camera initialization failed with error 0x%x", err);
        return;
    }
    // ESP_LOGE(TAG, "Camera initialized successfully");
    
    

    

    while (true) {
        send_image_to_server();
        //vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}   
