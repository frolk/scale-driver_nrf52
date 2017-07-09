#include "remote.h"
#include "correct.h"
#include "rgb_led.h"
#include "SEGGER_RTT.h"
#include "flash_storage.h"
#include "app_timer.h"


uint32_t pwm_value = 250;
uint32_t pwm_value2 = 250;
uint32_t test_value = 333;


APP_TIMER_DEF(m_timer_remote);

uint8_t pin_in1_is_set = 0;
uint8_t pin_in1_long_press = 0;


void timer_3s_handler(void *p_context)
{
		SEGGER_RTT_printf(0, "hello from timer\r\n");
}

void timer_remote_butts_init(void)
{
	app_timer_init();
	app_timer_create(&m_timer_remote, APP_TIMER_MODE_REPEATED, timer_3s_handler); 
	
}



void start_timer_3s(void)
{
	//app_timer_init();
	app_timer_start(m_timer_remote, APP_TIMER_TICKS(1000), NULL);
	
}

void in_pin_handler1(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
//	pwm_value += 10;
//	fds_update_value(&pwm_value, file_id, fds_rk_cor1);
//	uint8_t button = 1;
//	rgb_set(50, 0, 0, 2);
//	correct(pwm_value, 0, 0);		
		if(nrf_drv_gpiote_in_is_set(PIN_IN_1))
		{
				start_timer_3s();
			 pin_in1_is_set = 1;
		}
		else
		{
			app_timer_stop(m_timer_remote);
			pin_in1_is_set = 0;
			pin_in1_long_press = 0;
			SEGGER_RTT_printf(0, "pin_in_1 low");
		}
}

void in_pin_handler2(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
	
//	uint8_t button = 2;
//	pwm_value2+=15;
//	fds_update_value(&pwm_value2, file_id, fds_rk_cor2);
	rgb_set(0, 50, 0, 0);
//	correct(pwm_value, 0, 0);
}

void in_pin_handler3(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
//	uint8_t button = 3;
//	fds_get_data(&pwm_value, file_id, fds_rk_cor1);
//	correct(0, pwm_value, 0);
	rgb_set(50, 0, 0, 0);
//	SEGGER_RTT_printf(0, "button = %d, pwm_value = %d\n", button, pwm_value);
}

void in_pin_handler4(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{ 
//	uint8_t button = 4;
//	correct(0, 0, 0);
//	fds_get_data(&pwm_value2, file_id, fds_rk_cor2);
//	rgb_set(150, 150, 150, 0);
//	SEGGER_RTT_printf(0, "button = %d, pwm_value = %d\n", button, pwm_value2);
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
		//start_timer_3s();
	}
	
	