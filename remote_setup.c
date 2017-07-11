#include "remote_setup.h"

uint8_t corr_mode_button = 0;

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
							rgb_set(50, 0, 0, 0);
							SEGGER_RTT_printf(0,"set corr_1_1\r\n");
							
						}
					if (pin_in2_long_press)
						{
							corr_mode_button = CORR_MODE_2_1;
							rgb_set(0, 50, 0, 0);
						}
					if (pin_in3_long_press)
						{
							corr_mode_button = CORR_MODE_3_1;
							rgb_set(0, 0, 50, 0);
						}
					if (pin_in4_long_press)
						{
							rgb_set(50, 50, 50, 0);
						}
						
					//	reset_long_press_flags();
						
					 
					 break;
						
					
					
					 case CORR_MODE_1_1:
							if(pin_in1_is_release)
							{
								corr_1_1++;
								correct_value(corr_1_1);
								SEGGER_RTT_printf(0,"corr_1_1 = %d\r\n", corr_1_1);
							}
							else if (pin_in1_long_press)
							{
								corr_mode_button = CORR_MODE_1_2;
								SEGGER_RTT_printf(0,"set corr_1_2\r\n");
							}
							
						break;
							
					 case CORR_MODE_1_2:
						 
							if(pin_in1_is_release)
							{
								corr_1_2++;
								correct_value(corr_1_2);
								SEGGER_RTT_printf(0,"corr_1_2 = %d\r\n", corr_1_2);
							}
							else if (pin_in1_long_press)
							{
								corr_mode_button = CORR_MODE_1_3;
								SEGGER_RTT_printf(0,"set corr_1_3\r\n");
							}
							
							break;
							
						case CORR_MODE_1_3:
						 
							if(pin_in1_is_release)
							{
								corr_1_3++;
								correct_value(corr_1_3);
								SEGGER_RTT_printf(0,"corr_1_3 = %d\r\n", corr_1_3);
							}
						
							
							break;
						
						
				}
				
			}
		button_event = 0;
}
	
				

//		else
//		{
//			
//			if (pin_in1_is_release)
//				{
//					  case 3:
//							rgb_set(50, 0, 0, 3);
//							correct_value(corr_1_3);
//							SEGGER_RTT_printf(0, "pin_in1_is_release = %d,corr_1_3 = %d\r\n", pin_in1_is_release, corr_1_3);
//						break;
//					}
//				}
//			
//						
//		}
		
		
		
