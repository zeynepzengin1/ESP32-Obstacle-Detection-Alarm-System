#include <stdio.h>
#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define SENSOR_PIN GPIO_NUM_23
#define BUZZER_PIN GPIO_NUM_5
#define RED_LED_PIN GPIO_NUM_2
#define GREEN_LED_PIN GPIO_NUM_4
#define OBSTACLE_ACTIVE_LEVEL 0 
//bu sensör bir nesen algılaığında 0 değerini verir ve bu değeri OBSTACLE_ACTIVE_LEVEL ile karşılaştırırız

void app_main(void)
//void app esp32 için kodun başladığı yerdir void geriye değer göndermez 
{
 /
    gpio_reset_pin(SENSOR_PIN);
    gpio_set_direction(SENSOR_PIN, GPIO_MODE_INPUT);
    gpio_set_pull_mode(SENSOR_PIN, GPIO_PULLUP_ONLY);

   
    gpio_reset_pin(BUZZER_PIN);
    gpio_set_direction(BUZZER_PIN, GPIO_MODE_OUTPUT);

   
    gpio_reset_pin(RED_LED_PIN);
    gpio_set_direction(RED_LED_PIN, GPIO_MODE_OUTPUT);

    
    gpio_reset_pin(GREEN_LED_PIN);
    gpio_set_direction(GREEN_LED_PIN, GPIO_MODE_OUTPUT);

   
    gpio_set_level(BUZZER_PIN, 0);
    gpio_set_level(RED_LED_PIN, 0);
    gpio_set_level(GREEN_LED_PIN, 1);

    printf("Engel algilayici alarm sistemi basladi.\n");

 // her koşulda çalışılacak sonsuz döngü
    while (1)
    {
        
        int sensor_value = gpio_get_level(SENSOR_PIN);

        
        bool obstacle_detected = (sensor_value == OBSTACLE_ACTIVE_LEVEL);

        if (obstacle_detected)
        {
            printf("ENGEL ALGILANDI! Alarm calisiyor.\n");

        
            gpio_set_level(RED_LED_PIN, 1);

        
            gpio_set_level(GREEN_LED_PIN, 0);

      
            gpio_set_level(BUZZER_PIN, 1);
            vTaskDelay(200 / portTICK_PERIOD_MS);

            gpio_set_level(BUZZER_PIN, 0);
            vTaskDelay(200 / portTICK_PERIOD_MS);
        }
        else
        {
            printf("Engel yok. Sistem normal.\n");

         
            gpio_set_level(BUZZER_PIN, 0);


            gpio_set_level(RED_LED_PIN, 0);

        
            gpio_set_level(GREEN_LED_PIN, 1);

            vTaskDelay(500 / portTICK_PERIOD_MS);
        }
    }

}