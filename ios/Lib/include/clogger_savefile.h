#ifndef _CLOGGER_SAVEFILE_H_
#define _CLOGGER_SAVEFILE_H_

#include "clogger_ref.h"

void clogger_savefile_init(const char *path);
void clogger_savefile_destroy(void);

void clogger_savefile_enable(int enable);

void clogger_savefile_logv(const clogger_ref *ref);
void clogger_savefile_logd(const clogger_ref *ref);
void clogger_savefile_logi(const clogger_ref *ref);
void clogger_savefile_logw(const clogger_ref *ref);
void clogger_savefile_loge(const clogger_ref *ref);

#endif
