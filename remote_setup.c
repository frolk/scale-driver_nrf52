#include "remote_setup.h"

uint8_t corr_mode_button = 0;


void change_but_level(uint32_t* value)

{
				uint32_t corr = *value;
				if(0 < *value && *value <= 1000) // plus correct
					{
						*value = 1200;
						correct(0,0,0);
						correct_value(*value);
						rgb_set(50, 0, 0, 1, 1000);
					}
					else if (1000 < *value && *value <= 2000) // minus correct
					{
						*value = 2200;
						correct(0,0,0);
						correct_value(*value);
						rgb_set(0, 50, 0, 1, 1000);
//						SEGGER_RTT_printf(0, "2 - %d, percent mode\r\n", *value);
//						SEGGER_RTT_printf(0, "corr_1_1 - %d \r\n", corr_1_1);
//						SEGGER_RTT_printf(0, "corr_1_2 - %d \r\n", corr_1_2);
//						SEGGER_RTT_printf(0, "corr_1_3 - %d \r\n", corr_1_3);
					}
					else if (2000 < *value && *value <= 3000)  // percent correct
					{
						*value = 200;
						correct(0,0,0);
						correct_value(*value);
						rgb_set(0, 0, 50, 1, 1000);
					}
}


void save_corr_values(void)
{
		fds_update_value(&corr_1_1, file_id, fds_rk_cor1);
		fds_update_value(&corr_1_2, file_id, fds_rk_cor1+1);
		fds_update_value(&corr_1_3, file_id, fds_rk_cor1+2);
		fds_update_value(&corr_2_1, file_id, fds_rk_cor1+3);
		fds_update_value(&corr_2_2, file_id, fds_rk_cor1+4);
		fds_update_value(&corr_2_3, file_id, fds_rk_cor1+5);
		fds_update_value(&corr_3_1, file_id, fds_rk_cor1+6);
		fds_update_value(&corr_3_2, file_id, fds_rk_cor1+7);
		fds_update_value(&corr_3_3, file_id, fds_rk_cor1+8);
}


void buttons_handle_setup(void)
{
	if(remote_mode == CORR_SETUP_MODE)
	{
			 switch (corr_mode_button)
				{

					 case 0:
						 
							if(pin_in1_long_press)
								{
									corr_mode_button = CORR_MODE_1_1;
									rgb_set(50, 0, 0, 1, 3000);
									correct_value(corr_1_1);
								
								}
							if (pin_in2_long_press)
								{
									corr_mode_button = CORR_MODE_2_1;
									rgb_set(0, 50, 0, 1, 3000);
									correct_value(corr_1_2);
								}
							if (pin_in3_long_press)
								{
									corr_mode_button = CORR_MODE_3_1;
									rgb_set(0, 0, 50, 1, 3000);
									correct_value(corr_1_3);
								}
							if (pin_in4_long_press)
								{
									//SEGGER_RTT_printf(0,"save values\r\n");
									rgb_set(50, 50, 50, 0, 0);
									//save_corr_values();
									remote_mode = WORK_MODE;
									corr_mode_button = 0;
								}
								
							//	reset_long_press_flags();
							 
					 break;
						
					
					 case CORR_MODE_1_1:
					
							if(pin_in1_is_release) // change correct value by one
							{
								corr_1_1++;
								correct_value(corr_1_1);
								rgb_set(50, 0, 0, 1, 500);
							}
							else if (pin_in1_long_press) // fast correct mode
							{
								start_timer_02s(); // fast correct way
							}
							
							if(pin_in2_is_release)  //switch correct mode (minus, plus or percent)
							{
									change_but_level(&corr_1_1);
							}
							
							if(pin_in3_is_release)  //switch button
							{
								  correct(0,0,0);
									corr_mode_button = CORR_MODE_1_2;
									rgb_set(0, 50, 0, 2, 2000);
									correct_value(corr_1_2);
							}
												
							break;

					 case CORR_MODE_1_2:
						 
							
							if(pin_in1_is_release)
							{
								corr_1_2++;
								correct_value(corr_1_2);
								SEGGER_RTT_printf(0, "corr_1_2 - %d \r\n", corr_1_2);
								rgb_set(0, 50, 0, 1, 500);
							}
							else if (pin_in1_long_press)
							{
								start_timer_02s(); // fast correct way
							}
							
							if(pin_in2_is_release)
							{
									change_but_level(&corr_1_2);
							}
							
							if(pin_in3_is_release)
							{
									corr_mode_button = CORR_MODE_1_3;
									rgb_set(0, 0, 50, 3, 2000);
									correct_value(corr_1_3);
							}
												
							break;
							
							
						case CORR_MODE_1_3:
					 
						
							if(pin_in1_is_release)
							{
								corr_1_3++;
								correct_value(corr_1_3);
								SEGGER_RTT_printf(0, "correct 1_3 \r\n");
								rgb_set(0, 0, 50, 1, 500);
							}
							else if (pin_in1_long_press)
							{
								start_timer_02s(); // fast correct way
							}
							
							if(pin_in2_is_release)
							{
									change_but_level(&corr_1_3);
							}
							
							if(pin_in3_is_release)
							{
									corr_mode_button = CORR_MODE_1_1;
									rgb_set(50, 0, 0, 3, 2000);
									correct_value(corr_1_1);
							}
											
						break;
							
				}
				
				if(pin_in4_is_release)
				{
					rgb_set(50, 50, 50, 0, 0);
					correct(0, 0, 0);
					init_corr_values();
					remote_mode = WORK_MODE;
					corr_mode_button = 0;
				}
				
				if (pin_in4_long_press)
						{
							SEGGER_RTT_printf(0,"save\r\n");
							SEGGER_RTT_printf(0,"rem_mode %d\r\n", remote_mode);
							rgb_set(50, 50, 50, 0, 0);
							save_corr_values();
							remote_mode = WORK_MODE;
							corr_mode_button = 0;
							correct(0, 0, 0);
						}
				
				
	}
		button_event = 0;
}
	
