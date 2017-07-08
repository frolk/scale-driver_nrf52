#ifndef REMOTE_H__
#define REMOTE_H__

#include "nrf_drv_gpiote.h"




#define PIN_IN_1 12
#define PIN_IN_2 13
#define PIN_IN_3 14
#define PIN_IN_4 15

extern uint32_t pwm_value; 
extern uint32_t* pwm_point;
void nrf_gpiote(void);

#endif
