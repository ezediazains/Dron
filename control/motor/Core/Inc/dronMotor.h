/*
 * dronMotor.h
 *
 *  Created on: Mar 7, 2026
 *      Author: juand
 */

#ifndef INC_DRONMOTOR_H_
#define INC_DRONMOTOR_H_

#include "main.h"
#include "tim.h"

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    DRON_MOTOR_IDLE = 0,
    DRON_MOTOR_ARMING,
    DRON_MOTOR_ARMED,
	DRON_MOTOR_STOP
} dronMotor_state_t;

void dronMotor_Init(void);
void dronMotor_StartArm(void);
uint8_t dronMotor_Update(void);
void dronMotor_Disarm(void);

bool dronMotor_IsArmed(void);
dronMotor_state_t dronMotor_GetState(void);


#endif /* INC_DRONMOTOR_H_ */
