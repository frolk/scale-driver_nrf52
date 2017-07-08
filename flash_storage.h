#ifndef FLASH_STORAGE_H__
#define FLASH_STORAGE_H__


#include "fds.h"
#include "fstorage.h"
#include "SEGGER_RTT.h"

extern uint16_t file_id;

extern uint16_t fds_rk_cor1;
extern uint16_t fds_rk_cor2;
extern uint16_t fds_rk_cor3;

extern fds_record_desc_t   record_desc;
extern fds_record_desc_t   record_desc2;
extern fds_record_desc_t   record_desc3;

extern volatile uint8_t write_flag;
extern uint32_t my_data;


ret_code_t fds_read(void);
ret_code_t fds_test_write(void);
ret_code_t fds_test_init (void);
ret_code_t fds_test_find_and_delete (void);
ret_code_t fds_write_value(uint32_t* value, uint16_t file_id, uint16_t rec_key, fds_record_desc_t record_desc);
ret_code_t fds_update_value(uint32_t* value, uint16_t file_id, uint16_t rec_key, fds_record_desc_t record_desc);
ret_code_t fds_read_value (uint32_t* data, uint16_t file_id_test, uint16_t rec_key_test, fds_record_desc_t record_desc);








#endif
