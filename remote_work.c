#include "remote_work.h"


uint32_t cor_value_auto = 0;
uint8_t correct_mode = COR_MANUAL;
uint8_t cor_set = 0;
uint32_t current_correct = 0;


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

void cor_auto_handle(void)
{
	if((remote_mode == WORK_MODE)&&(cal_turn_on > 0)&&(cor_value_auto))
	{
		if((adc_value > cal_turn_on) && (!cor_set))
		{
			correct_value(cor_value_auto);
			cor_set = 1;
			SEGGER_RTT_printf(0, "corr %d set\n\r", cor_value_auto);
		}
		else if (((adc_value < cal_turn_on)||(adc_value > 10000000)) && (cor_set))
		{
			correct(0,0,0);
			cor_set = 0;
			SEGGER_RTT_printf(0, "corr %d reset\n\r", cor_value_auto);
		}
	}
		
}

void buttons_handle(void)
{
	if(remote_mode == WORK_MODE)
	{
		if (pin_in1_is_release)
		{
			if(num_cor_buts > 3)
			{
				switch(pin_in1_is_release)
				{
				case 1:
						rgb_set(50, 0, 0, 1, 500);
						current_correct = corr_1_1;
				break;

				case 2:
						rgb_set(50, 0, 0, 2, 500);
						current_correct = corr_1_2;
				break;
				
				case 3:
					rgb_set(50, 0, 0, 3, 500);
					current_correct = corr_1_3;
					pin_in1_is_release = 0;
				break;
				}
			}
			
			else
			{
					rgb_set(50, 0, 0, 1, 500);
					current_correct = corr_1_1;
			}
			
		}
		
		else if (pin_in2_is_release)
		{
			if(num_cor_buts > 3)
			{
			switch(pin_in2_is_release)
			{
				case 1:
					rgb_set(0, 50, 0, 1, 500);
					current_correct = corr_2_1;
				break;

				case 2:
					rgb_set(0, 50, 0, 2, 500);
					current_correct = corr_2_2;
				break;
				
				case 3:
					rgb_set(0, 50, 0, 3, 500);
					current_correct = corr_2_3;
					pin_in2_is_release = 0;
				break;
			}
		}
		else
		{
		rgb_set(0, 50, 0, 1, 500);
					current_correct = corr_2_1;
		}			
		
		}
	  else if (pin_in3_is_release)
		{
			
			if(num_cor_buts > 3)
			{
				switch(pin_in3_is_release)
			{
				case 1:
					rgb_set(0, 0, 50, 1, 500);
					current_correct = corr_3_1;
				break;

				case 2:
					rgb_set(0, 0, 50, 2, 500);
					current_correct = corr_3_2;
				break;
				
				case 3:
					rgb_set(0, 0, 50, 3, 500);
					current_correct = corr_3_3;
					pin_in3_is_release = 0;
				break;
			}
			}
			
			else
			{
					rgb_set(0, 0, 50, 1, 500);
					current_correct = corr_3_1;
					pin_in3_is_release = 0;
				
			}
			
		}
		else if (pin_in4_is_release )
		{
			rgb_set(50, 50, 50, 1, 500);
			correct(0,0,0);
			cor_value_auto = 0;
			current_correct = 0;
			if(correct_mode == COR_AUTO)
			{
			time_to_sleep = TIME_TO_SLEEP;
			}
		}
		
					
		if(correct_mode == COR_MANUAL)
			{
					correct_value(current_correct);
					SEGGER_RTT_printf(0, "manual %d\n\r", current_correct);
			}
			
		else if (correct_mode == COR_AUTO)	
			{
						cor_value_auto = current_correct;
						if(feedback == 1)
						{
								
								correct_value(cor_feedback);
								stop_timer();
								start_timer(time_feedback);
							
						}
						
						else if (feedback == 2)
						{
							correct_value(current_correct);
							stop_timer();
							start_timer(time_feedback);
						}
						
						
						
					SEGGER_RTT_printf(0, "auto %d\n\r", cor_value_auto);	
			}
	}
}
