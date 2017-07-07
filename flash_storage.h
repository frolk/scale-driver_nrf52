#ifndef FLASH_STORAGE_H__
#define FLASH_STORAGE_H__


#include "fds.h"
#include "fstorage.h"
#include "SEGGER_RTT.h"

extern uint16_t file_id;
extern uint16_t rec_key;


extern volatile uint8_t write_flag;
extern uint32_t my_data;


ret_code_t fds_read(void);
ret_code_t fds_test_write(void);
ret_code_t fds_test_init (void);
ret_code_t fds_test_find_and_delete (void);







#endif
