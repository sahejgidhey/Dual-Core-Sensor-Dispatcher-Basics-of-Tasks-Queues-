#include <stdio.h>
#include "esp_log.h"
#include "include/dht11_driver.h"
#include "include/light_sensor_driver.h"
#include "include/buzzer_driver.h"

#define DHT11_data GPIO_NUM_4
#define LDR_SENSOR ADC_CHANNEL_6 // gpio 34
#define LED_ALERT GPIO_NUM_14
#define BUZZER_PIN GPIO_NUM_23

uint8_t data[5];
adc_oneshot_unit_handle_t ldr_handle;

void app_main(void)
{

    

}
