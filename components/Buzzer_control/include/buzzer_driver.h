#ifndef BUZZER_DRIVER_H
#define BUZZER_DRIVER_H
#include "driver/ledc.h"

#define BUZZER_LEDC_MODE LEDC_LOW_SPEED_MODE 
#define BUZZER_LEDC_CHANNEL LEDC_CHANNEL_0
#define BUZZER_LEDC_TIMER LEDC_TIMER_0
#define BUZZER_RESOLUTION LEDC_TIMER_10_BIT

void buzzer_config(uint8_t buzzer_pin);
void buzzer_on(uint32_t freq);
void buzzer_off();

#endif