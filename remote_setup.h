#ifndef REMOTE_SETUP_H
#define REMOTE_SETUP_H


#include "remote.h"

#define CORR_MODE_1_1     1
#define CORR_MODE_1_2			2
#define CORR_MODE_1_3			3	

#define CORR_MODE_2_1			4
#define CORR_MODE_2_2			5
#define CORR_MODE_2_3			6

#define CORR_MODE_3_1			7
#define CORR_MODE_3_2			8
#define CORR_MODE_3_3			9

void buttons_handle_setup(void);
extern uint8_t fast_correct1;


#endif //
