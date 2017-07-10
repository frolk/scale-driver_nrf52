#include "correct.h"

nrf_drv_pwm_t m_pwm_cor = NRF_DRV_PWM_INSTANCE(0);
nrf_pwm_values_individual_t seq_value;
nrf_pwm_sequence_t seq_corr;


uint32_t corr_1_1 = 300; 
uint32_t corr_1_2 = 350; 
uint32_t corr_1_3 = 400; 
uint32_t corr_2_1 = 310; 
uint32_t corr_2_2 = 360; 
uint32_t corr_2_3 = 410; 
uint32_t corr_3_1 = 420; 
uint32_t corr_3_2 = 700; 
uint32_t corr_3_3 = 900; 


void pwm_init_corr(void)

{
  
	nrf_drv_pwm_config_t const config0 =
	{
			.output_pins =
			{
					CORR_KG_PLUS, // channel 0
					CORR_KG_MINUS,             // channel 1
					CORR_PERCENT,             // channel 2
					NRF_DRV_PWM_PIN_NOT_USED,             // channel 3
			},
			.irq_priority = APP_IRQ_PRIORITY_LOW,
			.base_clock   = NRF_PWM_CLK_8MHz,
			.count_mode   = NRF_PWM_MODE_UP,
			.top_value    = TOP_VALUE,
			.load_mode    = NRF_PWM_LOAD_INDIVIDUAL,
			.step_mode    = NRF_PWM_STEP_AUTO
	};
	
	nrf_drv_pwm_init(&m_pwm_cor, &config0, NULL);
	
	seq_value.channel_0 = TOP_VALUE;
	seq_value.channel_1 = TOP_VALUE;
	seq_value.channel_2 = TOP_VALUE;

	seq_corr.values.p_individual = &seq_value;
	seq_corr.length = NRF_PWM_VALUES_LENGTH(seq_value);
	seq_corr.repeats             = 0;
  seq_corr.end_delay           = 0;
	nrf_drv_pwm_simple_playback(&m_pwm_cor, &seq_corr, 0, NRF_DRV_PWM_FLAG_LOOP);
	
}

void correct(uint16_t value, uint16_t value1, uint16_t value2)
	{
	
	seq_value.channel_0 = TOP_VALUE - value;
	seq_value.channel_1 = TOP_VALUE - value1;
	seq_value.channel_2 = TOP_VALUE - value2;
	seq_corr.values.p_individual = &seq_value;
	seq_corr.length = NRF_PWM_VALUES_LENGTH(seq_value);
	nrf_drv_pwm_simple_playback(&m_pwm_cor, &seq_corr, 0, NRF_DRV_PWM_FLAG_LOOP);
		
}
