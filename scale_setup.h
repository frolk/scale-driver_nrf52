#ifndef SCALE_SETUP_H__
#define SCALE_SETUP_H__

#include "hx711.h"
#include "flash_storage.h"
#include "remote.h"


extern uint32_t cal_zero_value;
extern uint32_t cal_load_value;
extern uint32_t cal_turn_on;

void init_cal_values(void);

void cal_unload(void);
void cal_load(void);
void scale_setup(void);
void define_corr_on(void);
void save_call_data(void);



#endif
