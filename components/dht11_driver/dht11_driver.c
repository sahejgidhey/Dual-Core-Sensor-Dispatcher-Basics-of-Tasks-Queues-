#include "include/dht11_driver.h"
#include "esp_timer.h"
#include "esp_log.h"

#define TAG "DHT11"

// this function is used for calculating the time of a bit 
static int64_t wait_for_state(int state, int64_t timeout_us , int pin_num) 
{
    int64_t start_time = esp_timer_get_time(); // this get the start time 

    while (gpio_get_level(pin_num) != state) // this check when the state change so the bit time is over
    {
        if ((esp_timer_get_time() - start_time) > timeout_us) // this check if the bit is lower the timeout 
        {
            return -1; // Timeout failed
        }
    }
    return esp_timer_get_time() - start_time; // this is returned when timeout is passed 
}


void dht11_sensor_wake_up(int pin_num)
{

    gpio_config_t pin_config = {
        .pin_bit_mask = (1ULL << pin_num),
        .mode = GPIO_MODE_OUTPUT,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .pull_up_en = GPIO_PULLUP_DISABLE
    };

    gpio_config(&pin_config); // this is config to output mode

    gpio_set_level(pin_num,0);
    vTaskDelay(pdMS_TO_TICKS(20));
    // this will make the line low 20 milliseconds

    gpio_set_level(pin_num,1);
    esp_rom_delay_us(30); //this will make the line high for 30 microseconds

    pin_config.mode = GPIO_MODE_INPUT; // this turn the sensor pin in input pin 
    pin_config.pull_up_en = GPIO_PULLUP_ENABLE;

    gpio_config(&pin_config); // this config to input mode

    // Expect DHT11 to pull line LOW for ~80us
    if (wait_for_state(0 , 100 , pin_num) < 0 || wait_for_state(1 , 100 , pin_num) < 0) 
    {
        ESP_LOGE(TAG, "Handshake Error: Sensor did not respond LOW.");
    }

    // Expect DHT11 to release line HIGH for ~80us
    if (wait_for_state(0, 100 , pin_num) < 0) 
    {
        ESP_LOGE(TAG, "Handshake Error: Sensor did not respond HIGH.");
    }

    // these two if statement check if the sensor is init and working fine

}

void dht11_data_read(int pin_num , uint8_t *data)
{

    for (int i = 0; i < 40; i++) 
    {
            // Every bit starts with a 50us LOW period. Wait for it to end (line goes HIGH).
            if (wait_for_state(1, 100 , pin_num) < 0) 
            {
                ESP_LOGE(TAG, "Data Timeout during LOW signal carrier.");
                continue;
            }

            // The line is now HIGH. Measure exactly how long it stays HIGH.
            int64_t high_duration = wait_for_state(0, 100,pin_num);

            if (high_duration < 0)
            {
                ESP_LOGE(TAG, "Data Timeout during HIGH payload signal.");
                continue;
            }

            // Determine bit index in our 5-byte array
            int byte_idx = i / 8;
            
            // Shift existing bits to the left to make room for the new bit
            data[byte_idx] <<= 1; 

            // Logic check:
            // ~26-28us = Bit 0
            // ~70us    = Bit 1
            // We use a threshold of 45us to distinguish them.
            if (high_duration > 45) 
            {
                data[byte_idx] |= 1; // Append a 1 bit
            }
        }

}