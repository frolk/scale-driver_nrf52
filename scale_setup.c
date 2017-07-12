#include "scale_setup.h"

void cal_unload(void)
{
	
}

void cal_load(void)
{

}

void define_corr_on(void)
{

}


void scale_setup(void)
	
{
	  if(remote_mode == CALL_MODE)
		{
				
				if(pin_in1_is_release)
					{
						cal_unload();						
					}
					
				else if (pin_in2_is_release)	
					{
						cal_load();
						
					}
				
				else if (pin_in3_is_release)
					{
						define_corr_on();
					}
		}
		
		
		
}
