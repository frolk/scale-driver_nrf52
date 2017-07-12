#include "scale_setup.h"

uint32_t cal_zero_value = 0;
uint32_t cal_load_value = 0;
uint32_t cal_turn_on = 0;
uint8_t first_entry = 1;

void cal_unload(void)
{
	cal_zero_value = adc_value;
	SEGGER_RTT_printf(0, "zero - %d\n\r", cal_zero_value);
}

void cal_load(void)
{
	cal_load_value = adc_value;
	SEGGER_RTT_printf(0, "load - %d\n\r", cal_load_value);
}

void define_corr_on(void)
{
	cal_turn_on = adc_value;
	SEGGER_RTT_printf(0, "turn_on - %d\n\r", cal_turn_on);
}


void init_cal_value(void)
{
	// get cal data from flash
}

void save_cal_data(void)
{
	// save cal data
}


void scale_setup(void)
	
{
	  if(remote_mode == CALL_MODE)
		{
				
				if(pin_in1_is_release)
					{
						cal_unload();					
						first_entry = 0;
					}
					
				else if (pin_in2_is_release)	
					{
						cal_load();
						first_entry = 0;
						
					}
				
				else if (pin_in3_is_release)
					{
						define_corr_on();
						first_entry = 0;
					}
					
				else if (pin_in4_is_release)
				
						{
							if(!first_entry)
							{
								remote_mode = WORK_MODE;
								init_cal_value();
								rgb_set(50, 50, 50, 2, 1000);
							}
							
						}
					
				else if (pin_in4_long_press)
						{
								if(!first_entry)
							{
								remote_mode = WORK_MODE;
								init_cal_value();
								rgb_set(50, 50, 50, 5, 1000);
								save_cal_data();	
							}
							
							// save data to flash
						}
				
		}
		
		
		
}
