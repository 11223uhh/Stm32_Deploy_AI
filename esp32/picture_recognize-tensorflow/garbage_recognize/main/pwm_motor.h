#ifndef __PWM_MOTOR_H
#define __PWM_MOTOR_H

#include "driver/ledc.h"

#define LEDC_LS_TIMER          LEDC_TIMER_1
#define LEDC_LS_MODE           LEDC_LOW_SPEED_MODE

#define LEDC_LS_CH0_GPIO       (14)
#define LEDC_LS_CH0_CHANNEL    LEDC_CHANNEL_0
#define LEDC_LS_CH1_GPIO       (15)
#define LEDC_LS_CH1_CHANNEL    LEDC_CHANNEL_1


#define LEDC_TEST_CH_NUM       (2)
#define LEDC_TEST_DUTY         (4000)

int duty_angle(int angle);

void pwm_motor_init();
void pwm_motor_rate(int angle);

#endif