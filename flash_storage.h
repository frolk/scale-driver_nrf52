#ifndef FLASH_STORAGE_H__
#define FLASH_STORAGE_H__


#include "fds.h"
#include "fstorage.h"
#include "SEGGER_RTT.h"


extern volatile uint8_t write_flag;



ret_code_t fds_read(void);
ret_code_t fds_test_write(void);
ret_code_t fds_test_init (void);
ret_code_t fds_test_find_and_delete (void);







#endif
