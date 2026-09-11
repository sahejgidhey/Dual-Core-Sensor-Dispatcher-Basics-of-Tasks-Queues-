#include <stdio.h>
#include "esp_log.h"
#include "include/dht11_driver.h"
#include "esp_adc/adc_oneshot.h"

#define DHT11_data GPIO_NUM_4
#define LDR_SENSOR ADC_CHANNEL_6 // gpio 34
#define LED_ALERT GPIO_NUM_14

uint8_t data[5];

void app_main(void)
{

    

}
