#ifndef LIGHT_SENSOR_DRIVER_H
#define LIGHT_SENSOR_DRIVER_H
#include "esp_adc/adc_oneshot.h"
#include "driver/gpio.h"

void light_sensor_config(adc_oneshot_unit_handle_t *adc1_handle , adc_channel_t pin_num , uint8_t alert_led);
float light_sensor_data_read(adc_oneshot_unit_handle_t adc1_handle , adc_channel_t pin_num);

#endif 