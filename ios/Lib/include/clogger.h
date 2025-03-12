#ifndef _CLOGGER_H_
#define _CLOGGER_H_

#ifdef _cplusplus
extern "C"
{
#endif

#include "clogger_message_queue.h"
#include "clogger_ref.h"
#include "clogger_const.h"

#define CLOGGER_SIZE (10 * 1024)

#define LOG_CALLBACK_NUM 10
#define PRINT_INDEX 0
#define LOGAN_INDEX 1
#define SAVEFILE_INDEX 2
#define LOGTYPE_DEBUG "DEBUG"

typedef void (*ON_VERBOSE_LOG_CALLBACK)(const clogger_ref *ref);
typedef void (*ON_DEBUG_LOG_CALLBACK)(const clogger_ref *ref);
typedef void (*ON_INFO_LOG_CALLBACK)(const clogger_ref *ref);
typedef void (*ON_WARNING_LOG_CALLBACK)(const clogger_ref *ref);
typedef void (*ON_ERROR_LOG_CALLBACK)(const clogger_ref *ref);
typedef void (*ON_WTF_LOG_CALLBACK)(const clogger_ref *ref);

typedef struct _clogger_callback
{
    ON_VERBOSE_LOG_CALLBACK verbose_callback;
    ON_DEBUG_LOG_CALLBACK debug_callback;
    ON_INFO_LOG_CALLBACK info_callback;
    ON_WARNING_LOG_CALLBACK warning_callback;
    ON_ERROR_LOG_CALLBACK error_callback;
    ON_WTF_LOG_CALLBACK wtf_callback;
} clogger_callback;

extern clogger_callback callback_list[LOG_CALLBACK_NUM];
extern int callback_list_num;
extern clogger_queue q_log_queue;

void free_log_ref(clogger_ref *ref);
void clogger_init(void);
void clogger_log(const char *src_type, int level, const char *src_tag, const char *fmt, ...);

#ifdef _cplusplus
}
#endif

#endif
