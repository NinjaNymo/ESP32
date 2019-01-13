//   _____ _____ _____
//  |   | |__   |   | | ESP32/Servo/main/main.c
//  | | | |   __| | | | Nikolai Nymo
//  |_|___|_____|_|___| 11-12-18

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "servo.h"


void task_servoMinMaxTest(void *arg){
    servo_init();
    while(true){
        servo_setMax();
        vTaskDelay(250);
        servo_setMin();
        vTaskDelay(250);
    }
}


void app_main(){
    xTaskCreate(task_servoMinMaxTest, "servo_minMaxTest", 4096, NULL, 5, NULL);
}