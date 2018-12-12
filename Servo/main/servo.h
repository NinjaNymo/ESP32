//   _____ _____ _____
//  |   | |__   |   | | ESP32/Servo/main/servo.h
//  | | | |   __| | | | Nikolai Nymo
//  |_|___|_____|_|___| 12-12-18

#include <stdint.h>

#include "driver/mcpwm.h"
#include "soc/mcpwm_reg.h"
#include "soc/mcpwm_struct.h"


//
//      Servo Parameters
//       SG92R @ GPIO18
//
#define PW_MIN      500     // [us]
#define PW_MAX      2300    //
#define DEG_MIN     0       // [degree]
#define DEG_MAX     180     //
#define SERVO_PIN   18      // ESP32-GPIO#


/**
 * @brief   Degree to pulse width calculation
 * @param   servoPin    GPIO servo pin
 */
void servo_init(uint32_t servoPin);

/**
 * @brief   Set servo position
 * @param   pw  Requested position in [us]
 */
void servo_setPos_pw(uint32_t pw);

/**
 * @brief   Set servo position
 * @param   deg Requested position in [degrees]
 */
void servo_setPos_deg(uint32_t pw);

/**
 * @brief   Set ,ax servo position
 */
void servo_setMax();

/**
 * @brief   Set min servo position
 */
void servo_setMin();




