//   _____ _____ _____
//  |   | |__   |   | | ESP32/Servo/main/main.c
//  | | | |   __| | | | Nikolai Nymo
//  |_|___|_____|_|___| 11-12-18

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/*  Put in servo.h  */
#define PW_BUF  50 // A buffer at max and end to avoid breaking servo
#define PW_MIN  500  // Min pulse width [us]
#define PW_MAX  2300  // Max pulse width [us]
#define DEG_MIN    0 // Min servo position [degree]
#define DEG_MAX   90 // Max servo position [degree]
#define SERVO_PIN 18

//void servo_init();

/* Put in servo.c */
#include "driver/mcpwm.h"
#include "soc/mcpwm_reg.h"
#include "soc/mcpwm_struct.h"

/**
 * @brief Degree to pulse width calculation
 * 
 * @param deg Requested position [degrees]
 * 
 * @return
 *     - Requiested position as pulsewidth [us]
 */
uint32_t deg_to_pw(uint8_t deg){
    return (PW_MIN + (((PW_MAX - PW_MIN) * deg)/DEG_MAX));
}

static void servo_init(void* arg){
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, 18);

    mcpwm_config_t pwmConfig;
    pwmConfig.frequency = 50;
    pwmConfig.cmpr_a = 0;
    pwmConfig.cmpr_b = 0;
    pwmConfig.counter_mode = MCPWM_UP_COUNTER;
    pwmConfig.duty_mode = MCPWM_DUTY_MODE_0;
    
    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwmConfig);

    uint32_t deg, pw, i;
    while(true){
        while(true){
            while(true){
                mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, PW_MIN);
                printf("%d\n",PW_MIN);
                vTaskDelay(1000);
                mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, PW_MAX);
                printf("%d\n",PW_MAX);
                vTaskDelay(1000);

            }

            for(i = 400; i < 2000; i+=100){
                mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, i);
                printf("%d\n", i);
                vTaskDelay(500);
            }
            for(; i > 200; i-=100){
                mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, i);
                printf("%d\n", i);
                vTaskDelay(500);
            }
        }




        for(deg = DEG_MAX; deg > DEG_MIN; deg--){
            pw = deg_to_pw(deg);
            mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, pw);
            printf("deg = %d [degree], pw = %d[ms]\n", deg, pw);
            vTaskDelay(500);
        }
        for(deg = 0; deg < DEG_MAX; deg ++){
            pw = deg_to_pw(deg);
            mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, pw);
            printf("deg = %d [degree], pw = %d[ms]\n", deg, pw);
            vTaskDelay(500);
        }
    }
}
/* Put in main.c*/

void app_main(){
    printf("Hello World!\n");
    xTaskCreate(servo_init, "servo_init", 4096, NULL, 5, NULL);
}