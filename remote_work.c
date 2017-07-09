#include "remote_work.h"





void buttons_handle()
{
	if(button_event)
	{
		if(pin_in1_long_press)
		{
			rgb_set(50, 0, 0, 1000);
		}
		else if (pin_in2_long_press)
		{
			rgb_set(0, 50, 0, 1000);
		}
		else if (pin_in3_long_press)
		{
			rgb_set(0, 0, 50, 1000);
		}
		button_event = 0;
	}
		
}