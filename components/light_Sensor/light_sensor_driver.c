#include "include/light_sensor_driver.h"

void light_sensor_config(adc_oneshot_unit_handle_t *adc1_handle , adc_channel_t pin_num , uint8_t alert_led)
{

    // Step 1 : adc uint config
    adc_oneshot_unit_init_cfg_t adc_unit_config = {
        .unit_id = ADC_UNIT_1
    };

    adc_oneshot_new_unit(&adc_unit_config,adc1_handle);

    // Step 2 : adc_channel config 
    adc_oneshot_chan_cfg_t adc_channel_config = {
        .bitwidth = ADC_BITWIDTH_DEFAULT,
        .atten = ADC_ATTEN_DB_12
    };

    adc_oneshot_config_channel(*adc1_handle,pin_num,&adc_channel_config);

    gpio_config_t alert_led_config = {
        .pin_bit_mask = (1ULL << alert_led),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE
    };

    gpio_config(&alert_led_config);

    gpio_set_level(alert_led,0);

}

float light_sensor_data_read(adc_oneshot_unit_handle_t adc1_handle , adc_channel_t adc_channel)
{

    int raw_voltage = 0;
    adc_oneshot_read(adc1_handle,adc_channel,&raw_voltage);

    return (float) (raw_voltage/4950.0f)*100.0f;
    
}