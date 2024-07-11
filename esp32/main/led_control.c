#include "led_control.h"
#include "esp_log.h"
#include "driver/gpio.h"

#define TAG "esp32-cam_led_control"

void set_leds(int count) {
    int led_ports[] = {LED_PORT1, LED_PORT2, LED_PORT3, LED_PORT4, LED_PORT5};
    for (int i = 0; i < 5; i++) {
        esp_rom_gpio_pad_select_gpio(led_ports[i]);
        gpio_set_level(led_ports[i], i < count ? 1 : 0);
    }
}


void init_leds() {
    esp_err_t err;
    int led_ports[] = {LED_PORT1, LED_PORT2, LED_PORT3, LED_PORT4, LED_PORT5};
    for (int i = 0; i < 5; i++) {
        err = gpio_set_direction(led_ports[i], GPIO_MODE_OUTPUT);
        if (err != ESP_OK) {
            ESP_LOGE(TAG, "Failed to set direction for GPIO %d", led_ports[i]);
            return;
        }else{
            ESP_LOGI(TAG, "GPIO as output: %d", led_ports[i]);
        }
        err = gpio_set_level(led_ports[i], 0);
        if (err != ESP_OK) {
            ESP_LOGE(TAG, "Failed to set level for GPIO %d", led_ports[i]);
            return;
        }else{
            ESP_LOGW(TAG, "GPIO set to LOW: %d", led_ports[i]);
        }
    }
    err = gpio_set_direction(FLASH_LED_PIN, GPIO_MODE_OUTPUT);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to set direction for GPIO %d", FLASH_LED_PIN);
        return;
    }
    err = gpio_set_level(FLASH_LED_PIN, 1);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to set level for GPIO %d", FLASH_LED_PIN);
        return;
    }
}
