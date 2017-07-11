#include "remote_setup.h"

uint8_t corr_mode_button = 0;

void buttons_handle_setup(void)
{

	
		if(!corr_mode_button)
		{
	
			if(pin_in1_long_press)
			{
				corr_mode_button = CORR_MODE_1_1;
				rgb_set(50, 0, 0, 0);
				SEGGER_RTT_printf(0, "setup 1 button");
				corr_mode_button = 0;
				remote_mode = WORK_MODE;
			}
			if (pin_in2_long_press)
			{
				corr_mode_button = CORR_MODE_2_1;
				rgb_set(0, 50, 0, 0);
				SEGGER_RTT_printf(0, "setup 2 button");
				corr_mode_button = 0;
				remote_mode = WORK_MODE;
			}
			if (pin_in3_long_press)
			{
				corr_mode_button = CORR_MODE_3_1;
				rgb_set(0, 0, 50, 0);
				SEGGER_RTT_printf(0, "setup 3 button");
				corr_mode_button = 0;
				remote_mode = WORK_MODE;
			}
			if (pin_in4_long_press)
			{
				rgb_set(50, 50, 50, 0);
			}
		
		}
		
		button_event = 0;
}
