#include "gpio_motor.h"

void gpio_motor_init()
{
    gpio_pad_select_gpio(dir);//选中激活方向引脚
    gpio_set_direction(dir, GPIO_MODE_OUTPUT);//设置为输出

    gpio_pad_select_gpio(pul);//选中激活GPIO2引脚
    gpio_set_direction(pul, GPIO_MODE_OUTPUT);//设置为输出
    gpio_set_level(dir, 1);

  

}




void motor_test(int angle,int dir_n)
{
	int count=0;
    gpio_set_level(dir, dir_n);
    int delay_ms=12;
	//GPIO_SetBits(GPIOC,GPIO_Pin_6);//正转 DIR  向右
	//6000 3.7cm
	for(count=0;count<(int)(angle*2.222);count++)
	{
		gpio_set_level(pul,0);//脉冲
        vTaskDelay(delay_ms / portTICK_PERIOD_MS);              
		gpio_set_level(pul,1);//脉冲
        vTaskDelay(delay_ms / portTICK_PERIOD_MS);              
	}
	
	//GPIO_SetBits(GPIOC,GPIO_Pin_6);//正转 DIR  向右
	//6000 3.7cm

}