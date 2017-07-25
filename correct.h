#ifndef CORRECT_H__
#define CORRECT_H__


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
#include "flash_storage.h"
#include "rgb_led.h"
#include "remote.h"

#define CORR_KG_PLUS 27 
#define CORR_KG_MINUS 26
#define CORR_PERCENT 17

#define TOP_VALUE 1000


extern uint32_t corr_1_1; 
extern uint32_t corr_1_2; 
extern uint32_t corr_1_3; 

extern uint32_t corr_2_1; 
extern uint32_t corr_2_2; 
extern uint32_t corr_2_3; 

extern uint32_t corr_3_1; 
extern uint32_t corr_3_2; 
extern uint32_t corr_3_3; 


extern uint32_t corr_counter;

void correct(uint32_t value, uint32_t value1, uint32_t value2);
void pwm_init_corr(void);

void corr_plus(uint32_t value);
void corr_minus(uint32_t value);
void corr_perc(uint32_t value);

void correct_value(uint32_t value);



#endif
