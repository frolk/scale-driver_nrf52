#ifndef SCALE_SETUP_H__
#define SCALE_SETUP_H__

#include "hx711.h"
#include "flash_storage.h"
#include "remote.h"
#include <stdlib.h>


#define AVERAGE_ADC_TIMES 30
#define NUM_EXCEED_MEMBERS 6

#define SCALE_600   				1   
#define SCALE_5000  				2			
#define SCALE_AUTOVESI			3


extern uint32_t cal_zero_value;
extern uint32_t cal_load_value;
extern uint8_t scale_type;
extern uint32_t cal_turn_on;
extern uint8_t start_average_adc;
extern uint8_t scale_feedback;
extern uint32_t adc_need;
extern uint32_t activate_code;

void cal_unload(void);
void cal_load(void);
void scale_setup(void);
void define_corr_on(void);
void save_call_data(void);
void find_average_adc(void);
void init_cal_values(void);
void set_weight(uint16_t weight_value);

#endif
