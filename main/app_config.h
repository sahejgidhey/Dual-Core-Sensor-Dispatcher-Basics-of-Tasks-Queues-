#ifndef APP_CONFIG_H
#define APP_CONFIG_H

#include <stdio.h>
#include "esp_log.h"
#include "include/dht11_driver.h"
#include "include/light_sensor_driver.h"
#include "include/buzzer_driver.h"
#include "freertos/queue.h"

#define DHT11_data GPIO_NUM_4
#define LDR_SENSOR ADC_CHANNEL_6 // gpio 34
#define LED_ALERT GPIO_NUM_14
#define BUZZER_PIN GPIO_NUM_23

// this struct will contain the data form the sensor read task
typedef struct data{
    uint8_t temprature;
    uint8_t humidity;
    float light;
}task_data_t;

#endif