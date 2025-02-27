#ifndef _CLOGGER_PRINT_H_
#define _CLOGGER_PRINT_H_

#include "clogger_ref.h"

void clogger_print_init(void);

void clogger_print_logv(const clogger_ref *ref);
void clogger_print_logd(const clogger_ref *ref);
void clogger_print_logi(const clogger_ref *ref);
void clogger_print_logw(const clogger_ref *ref);
void clogger_print_loge(const clogger_ref *ref);
void clogger_print_logwtf(const clogger_ref *ref);

// clogger_log内部用的日志部分，只打印屏幕
void clogger_internal_e(const char *fmt, ...);

#endif
