//   _____ _____ _____
//  |   | |__   |   | | ESP32/Servo/main/servo.c
//  | | | |   __| | | | Nikolai Nymo
//  |_|___|_____|_|___| 12-12-18

#include "servo.h"

/**
 * @brief Degree to pulse width calculation
 * @param   deg Requested position [degrees]
 * @return  Requiested position as pulsewidth [us]
 */
uint32_t deg_to_pw(uint32_t deg){
    return (PW_MIN + (((PW_MAX - PW_MIN) * deg)/DEG_MAX));
}


void servo_init(uint32_t servoPin){
    //
}


void servo_setPos_pw(uint32_t pw){
    //
}


void servo_setPos_deg(uint32_t pw){
    servo_setPos_pw(deg_to_pw(deg));
}


void servo_setMax(){
    servo_setPos_pw(PW_MAX);
}


void servo_setMin(){
    servo_setPos_pw(PW_MIN);
}