#include "hx711.h"
#include "nrf_drv_gpiote.h"
#include "nrf_gpio.h"
#include "nrf_drv_timer.h"
//#include "nrf_drv_pwm.h"
#include "nrf_drv_ppi.h"



uint32_t adc_value;

void in_data_handler (nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action)

{
	adc_ready = 1;
}

void HX711_init(void)
{
	nrf_drv_gpiote_init();
	nrf_gpio_pin_set(HX_DATA);
	nrf_drv_gpiote_in_config_t in_data_config = GPIOTE_CONFIG_IN_SENSE_HITOLO(true);
	in_data_config.pull = NRF_GPIO_PIN_PULLUP;
	
	nrf_drv_gpiote_in_init (HX_DATA, &in_data_config, in_data_handler);
	nrf_drv_gpiote_in_event_enable(HX_DATA, true);
	
	nrf_gpio_cfg_output(HX_SCK);
		
}

uint32_t Weighing(void)
{
	
	//adc_value = 0;
	uint8_t i = 0;
	
	nrf_gpio_pin_clear(HX_SCK);
	
	if (adc_ready == 1)
	{
		adc_value = 0;
		nrf_drv_gpiote_in_event_disable(HX_DATA);
				for(i = 0; i<24; i++)
				{
					
					nrf_gpio_pin_set(HX_SCK);
					nrf_delay_us(1);
					adc_value <<= 1;
					nrf_gpio_pin_clear(HX_SCK);
					nrf_delay_us(1);
				
					if(nrf_drv_gpiote_in_is_set(HX_DATA))
						{
							adc_value++;
						}
				}
		nrf_gpio_pin_set(HX_SCK);
		nrf_delay_us(1);
		nrf_gpio_pin_clear(HX_SCK);
		nrf_delay_us(1);
				
				
		adc_ready = 0;
		nrf_drv_gpiote_in_event_enable(HX_DATA, true);
	}
	return adc_value;
}

void ConvertADC(void)
	{
		if(adc_value > 0)
		{
			//ultoa(adc_value, buffer+1, 10);
			
		}
	}
	






