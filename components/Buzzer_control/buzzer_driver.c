#include "include/buzzer_driver.h"

void buzzer_on(uint32_t freq)
{
    // this set the frequency which needs to be played 
    ledc_set_freq(BUZZER_LEDC_MODE,BUZZER_LEDC_TIMER,freq);
    // this set the duty cycle which controls the loudness 
    ledc_set_duty(BUZZER_LEDC_MODE,BUZZER_LEDC_CHANNEL,512);
    ledc_update_duty(BUZZER_LEDC_MODE,BUZZER_LEDC_CHANNEL);

}

void buzzer_off()
{

    // this make the duty cycle zero so it turn off the buzzer
    ledc_set_duty(BUZZER_LEDC_MODE,BUZZER_LEDC_CHANNEL,0);
    ledc_update_duty(BUZZER_LEDC_MODE,BUZZER_LEDC_CHANNEL);

}

void buzzer_config(uint8_t buzzer_pin)
{

    //Step 1 : Ledc timmer config
    ledc_timer_config_t ledc_timer_cfg = {
        .speed_mode = BUZZER_LEDC_MODE,
        .timer_num = BUZZER_LEDC_TIMER,
        .duty_resolution = BUZZER_RESOLUTION,
        .freq_hz = 2000,
        .clk_cfg = LEDC_AUTO_CLK
    };

    ledc_timer_config(&ledc_timer_cfg);

    //Step 2 : Config ledc pwm timmer channel linked to gpio 
    ledc_channel_config_t ledc_channel = {
        .speed_mode = BUZZER_LEDC_MODE,
        .channel = BUZZER_LEDC_CHANNEL,
        .timer_sel = BUZZER_LEDC_TIMER,
        .intr_type = LEDC_INTR_DISABLE,
        .gpio_num = buzzer_pin,
        .duty = 0,
        .hpoint = 0
    };

    ledc_channel_config(&ledc_channel);

}