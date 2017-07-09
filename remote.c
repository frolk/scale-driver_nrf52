#include "remote.h"


uint32_t pwm_value = 250;
uint32_t pwm_value2 = 250;
uint32_t test_value = 333;


APP_TIMER_DEF(m_timer_remote);


uint8_t button_event = 0;

uint8_t pin_in1_is_set = 0;
uint8_t pin_in1_long_press = 0;

uint8_t pin_in2_is_set = 0;
uint8_t pin_in2_long_press = 0;

uint8_t pin_in3_is_set = 0;
uint8_t pin_in3_long_press = 0;

uint8_t pin_in4_is_set = 0;
uint8_t pin_in4_long_press = 0;

void reset_long_press_flags(void)
{
	pin_in1_long_press = 0;
	pin_in2_long_press = 0;
	pin_in3_long_press = 0;
	pin_in4_long_press = 0;
}

void reset_press_flags()
{
	pin_in1_is_set = 0;
	pin_in2_is_set = 0;
	pin_in3_is_set = 0;
	pin_in4_is_set = 0;
}


void flag_analize()
{
	SEGGER_RTT_printf(0, "%d,%d\r\n", pin_in1_is_set, pin_in1_long_press);
	SEGGER_RTT_printf(0, "%d,%d\r\n", pin_in2_is_set, pin_in2_long_press);
	SEGGER_RTT_printf(0, "%d,%d\r\n", pin_in3_is_set, pin_in3_long_press);
	SEGGER_RTT_printf(0, "%d,%d\r\n", pin_in4_is_set, pin_in4_long_press);
	SEGGER_RTT_printf(0, "--------\r\n");
}


void timer_2s_handler(void *p_context)
{
	button_event = 1;
	if(pin_in1_is_set == 1)
	{
		//rgb_set(50, 0, 0, 1000);
		pin_in1_long_press = 1;
					
	}
	else if (pin_in2_is_set == 1)
	{
		//rgb_set(0, 50, 0, 1000);
		pin_in2_long_press = 1;
					
	}
	else if (pin_in3_is_set == 1)
	{
		//rgb_set(0, 0, 50, 1000);
		pin_in3_long_press = 1;
					
	}
	else if (pin_in4_is_set == 1)
	{
		//rgb_set(50, 50, 50, 1000);
		pin_in4_long_press = 1;
					

	}
}

void timer_remote_butts_init(void)
{
	app_timer_init();
	app_timer_create(&m_timer_remote, APP_TIMER_MODE_SINGLE_SHOT, timer_2s_handler); 
	
}



void start_timer_2s(void)
{
	app_timer_start(m_timer_remote, APP_TIMER_TICKS(2000), NULL);
}




void in_pin_handler1(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
//	pwm_value += 10;
//	fds_update_value(&pwm_value, file_id, fds_rk_cor1);
//	uint8_t button = 1;
//	rgb_set(50, 0, 0, 2);
//	correct(pwm_value, 0, 0);		
	button_event = 1;
		if(nrf_drv_gpiote_in_is_set(PIN_IN_1))
		{
			 start_timer_2s();
			 pin_in1_is_set = 1;
			 reset_long_press_flags();
		}
		else
		{
			app_timer_stop(m_timer_remote);
			pin_in1_is_set = 0;
			if(!pin_in1_long_press)
			{
				//rgb_set(50, 0, 0, 0);
			}
		}
}

void in_pin_handler2(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
	
//	uint8_t button = 2;
//	pwm_value2+=15;
//	fds_update_value(&pwm_value2, file_id, fds_rk_cor2);
//	rgb_set(0, 50, 0, 0);
//	correct(pwm_value, 0, 0);
	button_event = 1;
			if(nrf_drv_gpiote_in_is_set(PIN_IN_2))
		{
			 start_timer_2s();
			 pin_in2_is_set = 1;
			 reset_long_press_flags();
		}
		else
		{
			app_timer_stop(m_timer_remote);
			pin_in2_is_set = 0;
			if(!pin_in2_long_press)
			{
			//	rgb_set(0, 50, 0, 0);
			}
		}
}

void in_pin_handler3(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
//	uint8_t button = 3;
//	fds_get_data(&pwm_value, file_id, fds_rk_cor1);
//	correct(0, pwm_value, 0);
//	SEGGER_RTT_printf(0, "button = %d, pwm_value = %d\n", button, pwm_value);
	button_event = 1;
		if(nrf_drv_gpiote_in_is_set(PIN_IN_3))
		{
			 start_timer_2s();
			 pin_in3_is_set = 1;
			 reset_long_press_flags();
		}
		else
		{
			app_timer_stop(m_timer_remote);
			pin_in3_is_set = 0;
			if(!pin_in3_long_press)
			{
			//	rgb_set(0, 0, 50, 0);
			}
		}
}

void in_pin_handler4(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{ 
//	uint8_t button = 4;
//	correct(0, 0, 0);
//	fds_get_data(&pwm_value2, file_id, fds_rk_cor2);
//	rgb_set(150, 150, 150, 0);
//	SEGGER_RTT_printf(0, "button = %d, pwm_value = %d\n", button, pwm_value2);
	button_event = 1;
		if(nrf_drv_gpiote_in_is_set(PIN_IN_4))
		{
			 start_timer_2s();
			 pin_in4_is_set = 1;
			 reset_long_press_flags();
		}
		else
		{
			app_timer_stop(m_timer_remote);
			pin_in4_is_set = 0;
			if(!pin_in4_long_press)
			{
				//rgb_set(50, 50, 50, 0);
			}
		}
}

void nrf_gpiote(void)
	{
		nrf_drv_gpiote_init();
		
		nrf_drv_gpiote_in_config_t in_config = GPIOTE_CONFIG_IN_SENSE_TOGGLE(true);
		in_config.pull = NRF_GPIO_PIN_PULLUP;
		
		nrf_drv_gpiote_in_init(PIN_IN_1, &in_config, in_pin_handler1);
		nrf_drv_gpiote_in_init(PIN_IN_2, &in_config, in_pin_handler2);
		nrf_drv_gpiote_in_init(PIN_IN_3, &in_config, in_pin_handler3);
		nrf_drv_gpiote_in_init(PIN_IN_4, &in_config, in_pin_handler4);
		
		nrf_drv_gpiote_in_event_enable(PIN_IN_1, true);	
		nrf_drv_gpiote_in_event_enable(PIN_IN_2, true);	
		nrf_drv_gpiote_in_event_enable(PIN_IN_3, true);	
		nrf_drv_gpiote_in_event_enable(PIN_IN_4, true);	
		
		timer_remote_butts_init();
	}
	
	