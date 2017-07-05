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


#define CORR_KG_PLUS 27 
#define CORR_KG_MINUS 26
#define CORR_PERCENT 30

#define TOP_VALUE 1000


void correct(uint16_t value, uint16_t value1, uint16_t value2);
void pwm_init_corr();


#endif
