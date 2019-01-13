//   _____ _____ _____
//  |   | |__   |   | | ESP32/Servo/main/servo.c
//  | | | |   __| | | | Nikolai Nymo
//  |_|___|_____|_|___| 12-12-18

#include "servo.h"

#include "driver/mcpwm.h"
#include "soc/mcpwm_reg.h"
#include "soc/mcpwm_struct.h"

/**
 * @brief Degree to pulse width calculation
 * @param   deg Requested position [degrees]
 * @return  Requested position as pulsewidth [us]
 */
uint32_t deg_to_pw(uint32_t deg){
    return (PW_MIN + (((PW_MAX - PW_MIN) * deg)/DEG_MAX));
}


void servo_init(){
    // Initialize PWM Unit 0 to GPIO pin at SERVO_PIN:
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, SERVO_PIN);

    // Configure PWM Unit 0:
    mcpwm_config_t pwmConfig;
    pwmConfig.frequency = 50;
    pwmConfig.cmpr_a = 0;
    pwmConfig.cmpr_b = 0;
    pwmConfig.counter_mode = MCPWM_UP_COUNTER;
    pwmConfig.duty_mode = MCPWM_DUTY_MODE_0;

    //Initialize PWM Unit 0 with configurations:
    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwmConfig);
}


void servo_setPos_pw(uint32_t pw){
    mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, pw);
}


void servo_setPos_deg(uint32_t deg){
    servo_setPos_pw(deg_to_pw(deg));
}

void servo_setPos_percentage(uint32_t percentage){
    servo_setPos_pw((PW_MAX * percentage) / 100);
}


void servo_setMax(){
    servo_setPos_pw(PW_MAX);
}


void servo_setMin(){
    servo_setPos_pw(PW_MIN);
}