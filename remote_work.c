#include "remote_work.h"





void buttons_handle(void)
{
	if(button_event)
	{
		if(pin_in1_long_press)
		{
			rgb_set(50, 0, 0, 100);
		}
		if (pin_in2_long_press)
		{
			rgb_set(0, 50, 0, 100);
		}
		if (pin_in3_long_press)
		{
			rgb_set(0, 0, 50, 100);
		}
		if (pin_in4_long_press)
		{
			rgb_set(50, 50, 50, 100);
		}
		if (pin_in1_is_release)
		{
			rgb_set(50, 0, 0, 0);
		}
		if (pin_in2_is_release)
		{
			rgb_set(0, 50, 0, 0);
		}
		if (pin_in3_is_release)
		{
			rgb_set(0, 0, 50, 0);
		}
		if (pin_in4_is_release)
		{
			rgb_set(50, 50, 50, 0);
		}

		flag_analize();
		button_event = 0;
		
	}
		
}
