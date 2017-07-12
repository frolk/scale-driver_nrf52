#ifndef SCALE_SETUP_H__
#define SCALE_SETUP_H__

#include "hx711.h"
#include "flash_storage.h"
#include "remote.h"

void cal_unload(void);
void cal_load(void);
void scale_setup(void);
void define_corr_on(void);



#endif
