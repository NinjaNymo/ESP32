//   _____ _____ _____
//  |   | |__   |   | | ESP32/Servo/main/main.c
//  | | | |   __| | | | Nikolai Nymo
//  |_|___|_____|_|___| 11-12-18

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/*  Put in servo.h  */
#define PW_BUF  50 // A buffer at max and end to avoid breaking servo
#define PW_MIN  900  // Min pulse width [us]
#define PW_MAX  1800  // Max pulse width [us]
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
uint16_t deg_to_pw(uint8_t deg){
    return (PW_MIN + ((PW_MAX - PW_MIN) * (deg/DEG_MAX)));
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

    uint8_t count;
    while(true){
        for(count = DEG_MAX; count > DEG_MIN; count--){
            mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, deg_to_pw(count));
            vTaskDelay(1000);
        }
        for(count = 0; count < DEG_MAX; count ++){
            mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, deg_to_pw(count));
            vTaskDelay(1000);
        }
    }
}
/* Put in main.c*/

void app_main(){
    printf("Hello World!\n");
    xTaskCreate(servo_init, "servo_init", 4096, NULL, 5, NULL);
}