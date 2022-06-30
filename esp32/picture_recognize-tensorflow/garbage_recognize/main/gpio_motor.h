

#ifndef __GPIO_MOTOR_H
#define __GPIO_MOTOR_H		

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
/*

*/

// dir   +13
// pul   +15
// 
#define dir 13 
#define pul 15 

void gpio_motor_init();
void motor_rotate(int count,int flag,int var);
void motor_test(int count,int n);

#endif