#ifndef HX711_H__
#define HX711_H__


#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "nrf_delay.h"
#include "app_timer.h"
#include "nrf_drv_pwm.h"



#define HX_DATA	27
#define HX_SCK	28


extern uint32_t adc_value;
extern char buffer[24];
static uint8_t adc_ready;
extern uint8_t adc_value_ready;

void HX711_init(void);
uint32_t Weighing(void);
void ConvertADC(void);

#endif
