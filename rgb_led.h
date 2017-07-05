#ifndef RGB_LED_H
#define RGB_LED_H


#include <stdio.h>
#include <string.h>
#include "nrf_drv_pwm.h"
#include "app_util_platform.h"
#include "app_error.h"
#include "boards.h"
#include "bsp.h"
#include "app_timer.h"
#include "nrf_drv_clock.h"
#define NRF_LOG_MODULE_NAME "APP"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"


#define APP_TIMER_PRESCALER     0
#define APP_TIMER_OP_QUEUE_SIZE 2



#define RED 		1
#define GREEN 	2
#define BLUE  	3
#define WHITE   4
#define PURPLE  5
#define YELLOW  6


#define RED_FIRE 		10
#define GREEN_FIRE 	11
#define BLUE_FIRE  	12


#define RGB_TOP 255
#define RED_PIN 4
#define GREEN_PIN 2
#define BLUE_PIN 3




void pwm_init_rgb(void);
void rgb_set(uint16_t red, uint16_t green, uint16_t blue);

#endif //
