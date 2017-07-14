#ifndef REMOTE_H__
#define REMOTE_H__

#include "nrf_drv_gpiote.h"
#include "correct.h"
#include "rgb_led.h"
#include "SEGGER_RTT.h"
#include "flash_storage.h"
#include "app_timer.h"
#include "remote_work.h"
#include "remote_setup.h"
#include "scale_setup.h"

#define PIN_IN_1 12
#define PIN_IN_2 13
#define PIN_IN_3 14
#define PIN_IN_4 15

#define WORK_MODE 					0
#define CORR_BUT_MODE 		1
#define CALL_MODE 					2
#define FEEDBACK_SET_MODE 	3
#define CORR_SETUP_MODE	  	4  // auto correct setup

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


extern uint8_t short_delay;



extern uint8_t push_count1;
extern uint8_t push_count2;
extern uint8_t push_count3;
extern uint8_t push_count4;

extern uint8_t remote_mode;


void nrf_gpiote(void);
void timer_remote_butts_init(void);
void flag_analize(void);
void reset_long_press_flags(void);
void reset_release_flags(void);
void start_timer_05s(void);
void start_timer_02s(void);
void stop_timer_02s(void);
#endif
