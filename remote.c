#include "remote.h"
#include "correct.h"
#include "rgb_led.h"
#include "SEGGER_RTT.h"
#include "flash_storage.h"


uint32_t pwm_value = 250;
uint32_t test_value = 333;
uint32_t* pwm_point;

void in_pin_handler1(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
	fds_read_value(pwm_point, file_id_update, rec_key_update);
	uint8_t button = 1;
	//pwm_value += 50;
	rgb_set(50, 0, 0, 2);
	correct(pwm_value, 0, 0);		
}

void in_pin_handler2(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
	uint8_t button = 2;
	pwm_value+=100;
	fds_write_value(&pwm_value);
	rgb_set(0, 50, 0, 3);
	correct(pwm_value, 0, 0);
}

void in_pin_handler3(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
	uint8_t button = 3;
	pwm_value+=11;
	fds_update_value(&pwm_value);
	correct(0, pwm_value, 0);
	rgb_set(50, 0, 0, 0);
	SEGGER_RTT_printf(0, "button = %d, pwm_value = %d\n", button, pwm_value);
}

void in_pin_handler4(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{ 
	uint8_t button = 4;
	correct(0, 0, 0);
	//pwm_value+=11;
	//fds_update_value(&pwm_value);
	rgb_set(150, 150, 150, 0);
	SEGGER_RTT_printf(0, "button = %d, pwm_value = %d\n", button, pwm_value);
}

void nrf_gpiote(void)
	{
		nrf_drv_gpiote_init();
		
		nrf_drv_gpiote_in_config_t in_config = GPIOTE_CONFIG_IN_SENSE_LOTOHI(true);
		in_config.pull = NRF_GPIO_PIN_PULLUP;
		
		nrf_drv_gpiote_in_init(PIN_IN_1, &in_config, in_pin_handler1);
		nrf_drv_gpiote_in_init(PIN_IN_2, &in_config, in_pin_handler2);
		nrf_drv_gpiote_in_init(PIN_IN_3, &in_config, in_pin_handler3);
		nrf_drv_gpiote_in_init(PIN_IN_4, &in_config, in_pin_handler4);
		
		nrf_drv_gpiote_in_event_enable(PIN_IN_1, true);	
		nrf_drv_gpiote_in_event_enable(PIN_IN_2, true);	
		nrf_drv_gpiote_in_event_enable(PIN_IN_3, true);	
		nrf_drv_gpiote_in_event_enable(PIN_IN_4, true);	

	}
	
	