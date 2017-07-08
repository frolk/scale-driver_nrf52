#ifndef FLASH_STORAGE_H__
#define FLASH_STORAGE_H__


#include "fds.h"
#include "fstorage.h"
#include "SEGGER_RTT.h"

extern uint16_t file_id;

extern uint16_t fds_rk_cor1;
extern uint16_t fds_rk_cor2;
extern uint16_t fds_rk_cor3;
extern uint32_t fds_is_values_init;
extern uint16_t fds_rk_is_init;




extern volatile uint8_t write_flag;
extern uint32_t my_data;

void fds_init_flash(uint32_t* value, uint16_t file_id, uint16_t rec_key);
uint32_t fds_get_data(uint16_t file_id, uint16_t rec_key);

void fds_init_values(void);
ret_code_t fds_read(void);
ret_code_t fds_test_write(void);
ret_code_t fds_test_init (void);
ret_code_t fds_test_find_and_delete (void);
ret_code_t fds_write_value(uint32_t* value, uint16_t file_id, uint16_t rec_key);
ret_code_t fds_update_value(uint32_t* value, uint16_t file_id, uint16_t rec_key);
ret_code_t fds_read_value (uint32_t* data, uint16_t file_id, uint16_t rec_key);



#endif
