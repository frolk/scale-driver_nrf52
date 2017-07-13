#include "scale_setup.h"

uint32_t cal_zero_value = 0;
uint32_t cal_load_value = 0;
uint32_t cal_turn_on = 0;
uint8_t first_entry = 1;
uint8_t entry_to_cal = 0;
uint8_t start_average_adc = 0;
uint8_t count_average_adc = 0;
uint32_t average_adc = 0;
uint32_t adc_array[AVERAGE_ADC_TIMES];


void sort_array(uint32_t* array, uint8_t size)
{
	for(int i = size-1; i>=0; i--)
		{
			for (int j=0; j<i; j++)
				{
					if(array[j] > array[j+1])
						{
							uint32_t tmp = array[j];
							array[j] = array[j+1];
							array[j+1] = tmp;
							//nrf_delay_ms(100);
						}
				}
		}
}


void find_average_in_array(uint32_t* array, uint8_t size)
		{
				uint8_t start_id = NUM_EXCEED_MEMBERS/2;
				uint8_t end_id = size - start_id;
				uint32_t average_adc_arr = 0;
			
				for(uint8_t i = start_id; i < end_id; i++)
					{
						
						average_adc = average_adc + adc_value;
					//	SEGGER_RTT_printf(0, "arr[%d] %d\n\r",i, array[i]);
					//	nrf_delay_ms(100);
						
					}
					
					average_adc = average_adc/(size - NUM_EXCEED_MEMBERS);
					
		}


void print_array(uint32_t* array, uint8_t size)
	{
		for(int i = 0; i<size; i++)
			{
					SEGGER_RTT_printf(0, "arr[%d] %d\n\r",i, array[i]);
					nrf_delay_ms(100);
			}
	}


void find_average_adc(void)
{
			  rgb_set(50,0,0,0,1000);
				adc_array[count_average_adc] = adc_value;
				count_average_adc++;
				
				
	
	
				if(count_average_adc == AVERAGE_ADC_TIMES)
						{
							
							sort_array(adc_array, AVERAGE_ADC_TIMES);
							find_average_in_array(adc_array, AVERAGE_ADC_TIMES);
							
							switch(start_average_adc)
							{
								case 1:
									cal_zero_value = average_adc;
									SEGGER_RTT_printf(0, "zero - %d\n\r", cal_zero_value);
								break;
								
								case 2:
									cal_load_value = average_adc;
									SEGGER_RTT_printf(0, "load - %d\n\r", cal_load_value);
								break;
								
								case 3:
									cal_turn_on = average_adc;
									SEGGER_RTT_printf(0, "turn_on - %d\n\r", cal_turn_on);
								break;
								
								}
								count_average_adc = 0;
								start_average_adc = 0;
								average_adc = 0;
								stop_timer_02s();
								
								
								rgb_set(0,0,0,0,0);
								
								//SEGGER_RTT_printf(0, "============\n\r");
								//SEGGER_RTT_printf(0, "%d\n\r", cal_zero_value);
								
							//	print_array(adc_array, AVERAGE_ADC_TIMES);
								//SEGGER_RTT_printf(0, "============\n\r");
								
								//print_array(adc_array, AVERAGE_ADC_TIMES);
								//SEGGER_RTT_printf(0, "============\n\r");
								
								
								
						}
					
				

}



void cal_unload(void)
{
	
	start_average_adc = 1;
	start_timer_02s();
	
}

void cal_load(void)
{
	start_average_adc = 2;
	start_timer_02s();
	
}

void define_corr_on(void)
{
	start_average_adc = 3;
	start_timer_02s();
	
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
		

	
	
	  if((remote_mode == CALL_MODE) && !short_delay)
		{
				
				if(pin_in1_is_release)
					{
						cal_unload();		
						rgb_set(50, 0, 0, 1, 1000);
						first_entry = 0;
					}
					
				else if (pin_in2_is_release)	
					{
						cal_load();
						rgb_set(0, 50, 0, 1, 1000);
						first_entry = 0;
						
					}
				
				else if (pin_in3_is_release)
					{
						define_corr_on();
						rgb_set(0, 0, 50, 1, 1000);
						first_entry = 0;
					}
					
				else if (pin_in4_is_release)
				
						{
							if(!first_entry)
							{
								remote_mode = WORK_MODE;
								init_cal_value();
								rgb_set(50, 50, 50, 2, 1000);
								first_entry = 0;
							}
							
						}
					
				else if (pin_in4_long_press)
						{
								if(!first_entry)
							{
								first_entry = 0;
								remote_mode = WORK_MODE;
								init_cal_value();
								rgb_set(50, 50, 50, 5, 1000);
								save_cal_data();	
							}
							
							// save data to flash
						}
						
			
			
				
		}
		
		
		if(remote_mode == WORK_MODE)
				{
					 //SEGGER_RTT_printf(0, "I entry\r\n");
					if(short_delay && pin_in4_long_press)
					
						{
							rgb_set(50,0,0,1,1000);
							nrf_delay_ms(200);
							rgb_set(0,50,0,1,1000);
							nrf_delay_ms(200);
							rgb_set(0,0,50,1,1000);
							remote_mode = CALL_MODE;
							SEGGER_RTT_printf(0, "call mode\r\n");
							short_delay = 0;
							

						}
				}						
		
		
		
}
