#include "remote_work.h"


void init_corr_values(void)
{
	fds_get_data(&corr_1_1, file_id, fds_rk_cor1);
		fds_get_data(&corr_1_2, file_id, fds_rk_cor1+1);
		fds_get_data(&corr_1_3, file_id, fds_rk_cor1+2);
		fds_get_data(&corr_2_1, file_id, fds_rk_cor1+3);
		fds_get_data(&corr_2_2, file_id, fds_rk_cor1+4);
		fds_get_data(&corr_2_3, file_id, fds_rk_cor1+5);
		fds_get_data(&corr_3_1, file_id, fds_rk_cor1+6);
		fds_get_data(&corr_3_2, file_id, fds_rk_cor1+7);
		fds_get_data(&corr_3_3, file_id, fds_rk_cor1+8);
}



void buttons_handle(void)
{
	
	
	if(button_event)
	{
			
		if (pin_in1_is_release)
		{
			switch(pin_in1_is_release)
			{
				case 1:
					rgb_set(50, 0, 0, 1);
					correct(corr_1_1, 0, 0);
					SEGGER_RTT_printf(0, "pin_in1_is_release = %d,corr_1_1 = %d\r\n", pin_in1_is_release, corr_1_1);
				break;

				case 2:
					rgb_set(50, 0, 0, 2);
					correct(corr_1_2, 0, 0);
					SEGGER_RTT_printf(0, "pin_in1_is_release = %d,corr_1_2 = %d\r\n", pin_in1_is_release, corr_1_2);
				break;
				
				case 3:
					rgb_set(50, 0, 0, 3);
					correct(corr_1_3, 0, 0);
					SEGGER_RTT_printf(0, "pin_in1_is_release = %d,corr_1_3 = %d\r\n", pin_in1_is_release, corr_1_3);
				break;
			}
		}
		if (pin_in2_is_release)
		{
			rgb_set(0, 50, 0, 1);
			correct(0, 0, corr_3_2);
			SEGGER_RTT_printf(0, "corr_3_2 = %d\r\n", corr_3_2);
		}
		if (pin_in3_is_release)
		{
			rgb_set(0, 0, 50, 1);
			correct(0, 0, corr_3_3);
			SEGGER_RTT_printf(0, "corr_3_3 = %d\r\n", corr_3_3);
			
		}
		if (pin_in4_is_release)
		{
			rgb_set(50, 50, 50, 1);
			correct(0, 0, 0);
		}
		
		
		
		
		
		
		
		if(pin_in1_long_press)
		{
			rgb_set(50, 0, 0, 0);
		}
		if (pin_in2_long_press)
		{
			rgb_set(0, 50, 0, 0);
		}
		if (pin_in3_long_press)
		{
			rgb_set(0, 0, 50, 0);
		}
		if (pin_in4_long_press)
		{
			rgb_set(50, 50, 50, 0);
		}
	





		//flag_analize();
		button_event = 0;
		
	}
		
}
