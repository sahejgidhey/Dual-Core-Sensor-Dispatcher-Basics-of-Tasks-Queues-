#ifndef DHT11_DRIVER_H
#define DHT11_DRIVER_H
#include "driver/gpio.h"
#include "esp_rom_sys.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdint.h>

void dht11_sensor_wake_up(int pin_num);
void dht11_data_read(int pin_num , uint8_t* data);


#endif