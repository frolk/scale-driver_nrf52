#ifndef REMOTE_H__
#define REMOTE_H__

#include "nrf_drv_gpiote.h"
#include "correct.h"
#include "rgb_led.h"
#include "SEGGER_RTT.h"
#include "flash_storage.h"
#include "app_timer.h"



#define PIN_IN_1 12
#define PIN_IN_2 13
#define PIN_IN_3 14
#define PIN_IN_4 15

extern uint32_t pwm_value; 
extern uint32_t pwm_value2; 

extern uint8_t button_event;

extern uint8_t pin_in1_is_set;
extern uint8_t pin_in1_is_release;
extern uint8_t pin_in1_long_press;

extern uint8_t pin_in2_is_set;
extern uint8_t pin_in2_is_release;
extern uint8_t pin_in2_long_press;

extern uint8_t pin_in3_is_set;
extern uint8_t pin_in3_is_release;
extern uint8_t pin_in3_long_press;

extern uint8_t pin_in4_is_set;
extern uint8_t pin_in4_is_release;
extern uint8_t pin_in4_long_press;

void nrf_gpiote(void);
void timer_remote_butts_init(void);
void flag_analize();

#endif
