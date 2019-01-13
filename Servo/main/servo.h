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
 * @brief   Initializes servo at gpio pin SERVO_PIN.
 */
void servo_init();

/**
 * @brief   Set servo position.
 * @param   pw  Requested position in [us].
 */
void servo_setPos_pw(uint32_t pw);

/**
 * @brief   Set servo position.
 * @param   deg Requested position in [degrees].
 */
void servo_setPos_deg(uint32_t pw);

/**
 * @brief Set servo position in percentage between min and max.
 * @param percentage position between min and max.
 */
void servo_setPos_percentage(uint32_t percentage);

/**
 * @brief   Set max servo position.
 */
void servo_setMax();

/**
 * @brief   Set min servo position.
 */
void servo_setMin();




