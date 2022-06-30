
#include "pwm_motor.h"

int duty_angle(int angle)
{
    double   hight_time=0.5+(2.0*angle)/180;
    double   zhankong =hight_time/20;

    int duty=8191*zhankong;
    return duty;
}

void pwm_motor_init()
{
    int ch;
    ledc_timer_config_t ledc_timer = {
        .duty_resolution = LEDC_TIMER_13_BIT, // resolution of PWM duty
        .freq_hz = 50,                      // frequency of PWM signal
        .speed_mode = LEDC_LS_MODE,           // timer mode
        .timer_num = LEDC_LS_TIMER,            // timer index
        .clk_cfg = LEDC_AUTO_CLK,              // Auto select the source clock
    };
    ledc_timer_config(&ledc_timer);

    ledc_channel_config_t ledc_channel[LEDC_TEST_CH_NUM] = {
        {
            .channel    = LEDC_LS_CH0_CHANNEL,
            .duty       = 0,
            .gpio_num   = LEDC_LS_CH0_GPIO,
            .speed_mode = LEDC_LS_MODE,
            .hpoint     = 0,
            .timer_sel  = LEDC_LS_TIMER
        },
        {
            .channel    = LEDC_LS_CH1_CHANNEL,
            .duty       = 0,
            .gpio_num   = LEDC_LS_CH1_GPIO,
            .speed_mode = LEDC_LS_MODE,
            .hpoint     = 0,
            .timer_sel  = LEDC_LS_TIMER
        }
    };
    

    for (ch = 0; ch < LEDC_TEST_CH_NUM; ch++) {
        ledc_channel_config(&ledc_channel[ch]);
    }

}
void pwm_motor_rate(int angle)
{
    ledc_channel_config_t ledc_channel[LEDC_TEST_CH_NUM] = {

        {
            .channel    = LEDC_LS_CH0_CHANNEL,
            .duty       = 0,
            .gpio_num   = LEDC_LS_CH0_GPIO,
            .speed_mode = LEDC_LS_MODE,
            .hpoint     = 0,
            .timer_sel  = LEDC_LS_TIMER
        },
        {
            .channel    = LEDC_LS_CH1_CHANNEL,
            .duty       = 0,
            .gpio_num   = LEDC_LS_CH1_GPIO,
            .speed_mode = LEDC_LS_MODE,
            .hpoint     = 0,
            .timer_sel  = LEDC_LS_TIMER
        }
    };
    int duty=duty_angle(angle);
    for (int ch = 0; ch < LEDC_TEST_CH_NUM; ch++) {
        ledc_set_duty(ledc_channel[ch].speed_mode, ledc_channel[ch].channel, duty);
        ledc_update_duty(ledc_channel[ch].speed_mode, ledc_channel[ch].channel);
    }
   
}
