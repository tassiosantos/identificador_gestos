#pragma once

#include "driver/gpio.h"
#include "esp_log.h"

// Portas dos LEDs
#define LED_PORT1 12
#define LED_PORT2 13
#define LED_PORT3 14
#define LED_PORT4 15
#define LED_PORT5 2 
#define FLASH_LED_PIN 4

void set_leds(int count);
void init_leds();
