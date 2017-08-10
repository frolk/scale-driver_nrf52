#ifndef FLASH_STORAGE_H__
#define FLASH_STORAGE_H__


#include "fds.h"
#include "fstorage.h"
#include "SEGGER_RTT.h"


#define DEMO						1

#define EXP_DEMO_CORR   2
#define EXP_DEMO_RESET  3
#define EXP_DEMO_TIME   4


#define FULL 						5

#define EXP_FULL_CORR 	6
#define EXP_FULL_RESET 	7
#define EXP_FULL_TIME 	8

#define EXP_ACTIVATE_ATTEMPTS 9

extern uint16_t file_id;
extern uint16_t file_id_c;

extern uint16_t fds_rk_cor1;
extern uint16_t fds_rk_cor2;
extern uint16_t fds_rk_cor3;
extern uint16_t fds_rk_init;
extern uint16_t fds_rk_clock;
extern uint16_t fds_rk_power_down;
extern uint16_t fds_rk_activate_status;
extern uint16_t fds_rk_activate_attempts;

extern uint16_t fds_rk_num_cor_but;

extern uint16_t fds_rk_corr_counter;

extern uint16_t fds_rk_cal_zero;


extern uint16_t fds_rk_cor_feedback;
extern uint16_t fds_rk_time_feedback;
extern uint16_t fds_rk_feedback;


extern uint32_t fds_is_values_init;

extern uint32_t life_counter;
extern uint32_t activate_status;
extern uint32_t activate_attempts;



extern volatile uint8_t write_flag;
extern uint32_t my_data;
extern uint32_t power_down_count;
extern uint32_t num_cor_buts;

void fds_init_flash(uint32_t* value, uint16_t file_id, uint16_t rec_key);
ret_code_t fds_get_data(uint32_t* value, uint16_t file_id, uint16_t rec_key);

void fds_init_values(void);
ret_code_t fds_read(void);
ret_code_t fds_test_init (void);
ret_code_t fds_test_find_and_delete (void);
ret_code_t fds_write_value(uint32_t* value, uint16_t file_id, uint16_t rec_key);
ret_code_t fds_update_value(uint32_t* value, uint16_t file_id, uint16_t rec_key);
ret_code_t fds_read_value (uint32_t* data, uint16_t file_id, uint16_t rec_key);
ret_code_t fds_clear(void);


//void fds_get_init_data(void);


#endif
