#include "app_config.h"

adc_oneshot_unit_handle_t ldr_handle; // this is adc handle is used for LDR
QueueHandle_t data_queue = NULL; // this contains the data from the core 0 and take it core 1

void sensor_read_task(void *vParameter)
{

    uint8_t data[5] = {0};
    task_data_t task_data; // this contains the temp humidity and light data 

    light_sensor_config(&ldr_handle, LDR_SENSOR , LED_ALERT); // this will config the ldr and alert led

    while(1)
    {

        task_data.light = light_sensor_data_read(ldr_handle , LDR_SENSOR); // this will read the data from the light sensor

        vTaskDelay(pdMS_TO_TICKS(1000)); // this wait is use to wait for the sensor to be up
        dht11_sensor_wake_up(DHT11_data); // this function will turn the sensor on

        //vTaskDelay(pdMS_TO_TICKS(2000)); // this wait is used because of 1hz sampling rate
        dht11_data_read(DHT11_data,data);

        // this checks if the data sent is correct or not from dht11
        if(data[4] == data[0]+data[1]+data[2]+data[3])
        {
            task_data.humidity = data[0];
            task_data.temprature = data[2]; 
        }
        else 
        {
            task_data.humidity = -1;
            task_data.temprature = -1; 
        }

        if(xQueueSend(data_queue , (void*) &task_data , pdMS_TO_TICKS(50)) == pdTRUE)
        {

            ESP_LOGI("Sensor data" , "Sent sucessfully");
            ESP_LOGI("DHT11" , "Temprature -> %d Humidity ->%d Light -> %.2f" , task_data.temprature , task_data.humidity , task_data.light);

        }
        else
        {
            ESP_LOGW("Sensor data" , "Queue is full");
        }
 
    }

}

void alert_output_task(void *vParameter)
{

    task_data_t task_data;
    buzzer_config(BUZZER_PIN);

    while(1)
    {

        if(xQueueReceive(data_queue,&task_data,portMAX_DELAY) == pdPASS)// this will wait until the data is recieved
        {

            ESP_LOGI("Alert" , "Sucessfull recived");

        }


        if(task_data.light < 50.0f)
        {

            gpio_set_level(LED_ALERT , 1); // This will turn on the led when light is below 60%

        }
        else
        {

            gpio_set_level(LED_ALERT , 0);

        }

        if(task_data.temprature >= 33)
        {

            buzzer_on(2500);
            vTaskDelay(pdMS_TO_TICKS(300)); // this will turn the buzzer on for 300 milliseconds
            buzzer_off();

        }

    }

} 

void app_main(void)
{

    data_queue = xQueueCreate(2 , sizeof(task_data_t)); // Here the queue lenght is set

    xTaskCreatePinnedToCore(sensor_read_task , "Sensor read" , 2048 , NULL , 1 , NULL , 0);
    xTaskCreatePinnedToCore(alert_output_task , "Alert task" , 2048 , NULL , 1 , NULL , 1);
}
