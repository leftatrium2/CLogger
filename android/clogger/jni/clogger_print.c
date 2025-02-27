#include <stdio.h>
#include <android/log.h>
#include <stdarg.h>
#include <string.h>
#include "clogger.h"
#include "clogger_print.h"
#include "clogger_ref.h"

#define CLOGGER_INTERNAL_TAG "CLOGGER"

void clogger_print_logv(const clogger_ref *ref)
{
    __android_log_print(ANDROID_LOG_VERBOSE, ref->tag, "%s", ref->log);
}
void clogger_print_logd(const clogger_ref *ref)
{
    __android_log_print(ANDROID_LOG_DEBUG, ref->tag, "%s", ref->log);
}
void clogger_print_logi(const clogger_ref *ref)
{
    __android_log_print(ANDROID_LOG_INFO, ref->tag, "%s", ref->log);
}
void clogger_print_logw(const clogger_ref *ref)
{
    __android_log_print(ANDROID_LOG_WARN, ref->tag, "%s", ref->log);
}
void clogger_print_loge(const clogger_ref *ref)
{
    __android_log_print(ANDROID_LOG_ERROR, ref->tag, "%s", ref->log);
}

void clogger_internal_e(const char *fmt, ...)
{
#ifdef DEBUG
    va_list ap;
    va_start(ap, fmt);
    char buf[CLOGGER_SIZE];
    memset(&buf, 0, CLOGGER_SIZE);
    vsnprintf(buf, CLOGGER_SIZE - 1, fmt, ap);
    __android_log_print(ANDROID_LOG_ERROR, CLOGGER_INTERNAL_TAG, "%s", buf);
    va_end(ap);
#endif
}

void clogger_print_init()
{
    callback_list[PRINT_INDEX].verbose_callback = clogger_print_logv;
    callback_list[PRINT_INDEX].debug_callback = clogger_print_logd;
    callback_list[PRINT_INDEX].info_callback = clogger_print_logi;
    callback_list[PRINT_INDEX].warning_callback = clogger_print_logw;
    callback_list[PRINT_INDEX].error_callback = clogger_print_loge;
}