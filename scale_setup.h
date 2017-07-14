#ifndef SCALE_SETUP_H__
#define SCALE_SETUP_H__

#include "hx711.h"
#include "flash_storage.h"
#include "remote.h"


#define AVERAGE_ADC_TIMES 30
#define NUM_EXCEED_MEMBERS 6


extern uint32_t cal_zero_value;
extern uint32_t cal_load_value;
extern uint32_t cal_turn_on;
extern uint8_t start_average_adc;

void cal_unload(void);
void cal_load(void);
void scale_setup(void);
void define_corr_on(void);
void save_call_data(void);
void find_average_adc(void);
void init_cal_values(void);


#endif
