#ifndef REMOTE_WORK_H
#define REMOTE_WORK_H

#define COR_AUTO	 1
#define COR_MANUAL 2
#define COR_MODE



#include "remote.h"


extern uint32_t cor_value_auto;
extern uint8_t correct_mode;
extern uint8_t cor_set;

void buttons_handle(void);

void init_corr_values(void);

void cor_auto_handle(void);


#endif //
