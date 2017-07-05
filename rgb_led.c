#include "rgb_led.h"

nrf_drv_pwm_t m_pwm_rgb = NRF_DRV_PWM_INSTANCE(1);
nrf_pwm_values_individual_t seq_value_rgb;
nrf_pwm_sequence_t seq_rgb;

void pwm_init_rgb()

{
  uint32_t err_code;
	nrf_drv_pwm_config_t const config0 =
	{
			.output_pins =
			{
					RED_PIN, // channel 0
					GREEN_PIN,             // channel 1
					BLUE_PIN,             // channel 2
					NRF_DRV_PWM_PIN_NOT_USED,             // channel 3
			},
			.irq_priority = APP_IRQ_PRIORITY_LOW,
			.base_clock   = NRF_PWM_CLK_1MHz,
			.count_mode   = NRF_PWM_MODE_UP,
			.top_value    = RGB_TOP,
			.load_mode    = NRF_PWM_LOAD_INDIVIDUAL,
			.step_mode    = NRF_PWM_STEP_AUTO
	};
	
	err_code = nrf_drv_pwm_init(&m_pwm_rgb, &config0, NULL);
	
	seq_value_rgb.channel_0 = RGB_TOP;
	seq_value_rgb.channel_1 = RGB_TOP;
	seq_value_rgb.channel_2 = RGB_TOP;
	
	
	

	seq_rgb.values.p_individual = &seq_value_rgb;
	seq_rgb.length = NRF_PWM_VALUES_LENGTH(seq_value_rgb);
	seq_rgb.repeats             = 0;
  seq_rgb.end_delay           = 0;
	nrf_drv_pwm_simple_playback(&m_pwm_rgb, &seq_rgb, 0, NRF_DRV_PWM_FLAG_LOOP);
	
	
}

void rgb_set(uint16_t value, uint16_t value1, uint16_t value2)
	{
	
	seq_value_rgb.channel_0 = RGB_TOP - value;
	seq_value_rgb.channel_1 = RGB_TOP  - value1;
	seq_value_rgb.channel_2 = RGB_TOP  - value2;
	seq_rgb.values.p_individual = &seq_value_rgb;
	seq_rgb.length = NRF_PWM_VALUES_LENGTH(seq_value_rgb);
	nrf_drv_pwm_simple_playback(&m_pwm_rgb, &seq_rgb, 0, NRF_DRV_PWM_FLAG_LOOP);
		
}
