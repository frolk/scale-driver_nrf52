#include "scale_setup.h"

uint32_t cal_zero_value = 0;
uint32_t cal_load_value = 0;
uint32_t cal_turn_on = 0;
uint8_t entry_to_cal = 0;
uint8_t start_average_adc = 0;
uint8_t count_average_adc = 0;
uint32_t average_adc = 0;
uint32_t adc_array[AVERAGE_ADC_TIMES];
uint8_t scale_feedback = 0;
uint32_t cal_coef = 0;

uint8_t scale_type = SCALE_600;

uint32_t adc_need = 0;




void set_weight(uint16_t weight_value)
{
	adc_need = weight_value*((cal_load_value - cal_zero_value)/20)+cal_zero_value; 
	start_timer_adc();
	SEGGER_RTT_printf(0, "adc_need = %d\r\n", adc_need);
}

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
				//uint32_t average_adc_arr = 0;
			
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
									fds_update_value(&cal_zero_value, file_id, fds_rk_cal_zero);
									SEGGER_RTT_printf(0, "zero - %d\n\r", cal_zero_value);
								break;
								
								case 2:
									cal_load_value = average_adc;
									if((scale_type == SCALE_600) && cal_zero_value)
										{
											cal_coef = (cal_load_value - cal_zero_value)/20;
											SEGGER_RTT_printf(0, "cal_coef - %d\n\r", cal_coef);
										}
									fds_update_value(&cal_load_value, file_id, fds_rk_cal_zero+1);
									SEGGER_RTT_printf(0, "load - %d\n\r", cal_load_value);
								break;
								
								case 3:
									cal_turn_on = average_adc;
									fds_update_value(&cal_turn_on, file_id, fds_rk_cal_zero+2);
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


void init_cal_values(void)
{
		fds_get_data(&cal_zero_value, file_id, fds_rk_cal_zero);
		fds_get_data(&cal_load_value, file_id, fds_rk_cal_zero+1);
		fds_get_data(&cal_turn_on, file_id, fds_rk_cal_zero+2);
		
}


void scale_setup(void)
{
	
	if(remote_mode != WORK_MODE && pin_in4_is_release)
						{
								remote_mode = WORK_MODE;
								SEGGER_RTT_printf(0, "WORK MODE\n\r");
								rgb_set(50, 50, 50, 2, 1000);
						}

	
	  if((remote_mode == CALL_MODE) && !short_delay)
		{
				
				if(pin_in1_is_release)
					{
						cal_unload();		
						rgb_set(50, 0, 0, 1, 1000);
					}
					
				else if (pin_in2_is_release)	
					{
						cal_load();
						rgb_set(0, 50, 0, 1, 1000);
						
					}
				
				else if (pin_in3_is_release)
					{
						define_corr_on();
						rgb_set(0, 0, 50, 1, 1000);
					}
					
					
				
					
			
					
				else if (pin_in4_long_press)
						{
							{
									remote_mode = FEEDBACK_SET_MODE;
									rgb_set(50, 0, 0, 1, 3000);
									SEGGER_RTT_printf(0, "FEEDBACK SET MODE\n\r");
									
							}
							
							// save data to flash
						}
		}
		
		
	
		else if (remote_mode == FEEDBACK_SET_MODE)
		{
					if(pin_in1_is_release)
					{
						scale_feedback = 0;
						SEGGER_RTT_printf(0, "scale_feedback = 0\r\n");
					}
					
					else if (pin_in2_is_release)
					{
						scale_feedback = 1;
						SEGGER_RTT_printf(0, "scale_feedback = 1\r\n");
					}
					
					else if (pin_in3_is_release)
					{
						set_weight(11);
						
					}
					
					else if (pin_in4_long_press)
					
					{
						remote_mode = FACTORY_MODE;
						rgb_set(0, 50, 0, 1, 3000);
						SEGGER_RTT_printf(0, "FACTORY_MODE\r\n");
					}
					
		}
		
		else if (remote_mode == FACTORY_MODE)
				{
					if(pin_in1_is_release)
					{
						fds_test_find_and_delete();
						SEGGER_RTT_printf(0, "database is cleared\r\n");	
					}
					void return_to_work_mode();
				}

		else if(remote_mode == WORK_MODE)
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
							SEGGER_RTT_printf(0, "CAL MODE\r\n");
							short_delay = 0;
							

						}
						
					else if (pin_in4_long_press)
					{
						//remote_mode = CORR_SETUP_MODE;
						
						SEGGER_RTT_printf(0, "COR_AUTO_MODE\r\n");
						if(correct_mode == COR_MANUAL)
							{
								correct_mode = COR_AUTO;
								rgb_set(0,50,0,1,5000);
							}
						else if (correct_mode == COR_AUTO)
							{
								rgb_set(50,0,0,1,5000);
								correct_mode = COR_MANUAL;
							}
					}
				}						
}
