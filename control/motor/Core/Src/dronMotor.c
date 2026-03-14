/*
 * dronMotor.c
 *
 *  Created on: Mar 7, 2026
 *      Author: juand
 */
// LIBRERIA EXCLUSIVA PARA STM32
#include "dronMotor.h"

#define ESC_PULSE_MIN_US      1000U
#define ESC_PULSE_MAX_US      2000U
#define ESC_ARM_TIME_MS       2000U

static uint32_t t_dronMotor;
static uint16_t esc_pulse_us;
static dronMotor_state_t motor_state;

static void dronMotor_SetAllMotors(uint16_t pulse_us)
{
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, pulse_us);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, pulse_us);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, pulse_us);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, pulse_us);
}

void dronMotor_Init(void)
{
    esc_pulse_us = ESC_PULSE_MAX_US;
    dronMotor_SetAllMotors(esc_pulse_us);
    t_dronMotor = HAL_GetTick();
    motor_state = DRON_MOTOR_IDLE;
}

void dronMotor_StartArm(void)
{
    if (motor_state != DRON_MOTOR_IDLE) {
        return;
    }

    esc_pulse_us = ESC_PULSE_MIN_US;
    dronMotor_SetAllMotors(esc_pulse_us);
    t_dronMotor = HAL_GetTick();
    motor_state = DRON_MOTOR_ARMING;

}
uint8_t dronMotor_Update(void)
{
    switch (motor_state){
    case DRON_MOTOR_IDLE:
    	if ((HAL_GetTick() - t_dronMotor) >= ESC_ARM_TIME_MS){
    		dronMotor_StartArm();
    	}
        break;

    case DRON_MOTOR_ARMING:
        if ((HAL_GetTick() - t_dronMotor) >= ESC_ARM_TIME_MS){
            motor_state = DRON_MOTOR_ARMED;
            return 1;
        }
        break;

    case DRON_MOTOR_ARMED:
    	esc_pulse_us = ESC_PULSE_MAX_US;
    	dronMotor_SetAllMotors(esc_pulse_us);
        break;

    default:
        break;
    }

    return 0;
}
void dronMotor_Disarm(void)
{
    esc_pulse_us = ESC_PULSE_MIN_US;
    dronMotor_SetAllMotors(esc_pulse_us);
    t_dronMotor = HAL_GetTick();
    motor_state = DRON_MOTOR_IDLE;
}
bool dronMotor_IsArmed(void){		// está función sirve para consultar si está armado o no
    return (motor_state == DRON_MOTOR_ARMED);
}
dronMotor_state_t dronMotor_GetState(void){	//Esta funcion sirve para saber el estado actual
    return motor_state;
}
