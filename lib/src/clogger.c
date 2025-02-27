#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clogger.h"
#include "clogger_message_queue.h"
#include "clogger_print.h"

void free_log_ref(clogger_ref *ref)
{
    clogger_internal_e("free now, tag: %s, log: %s", ref->tag, ref->log);
    free((char *)ref->type);
    ref->type = NULL;
    free((char *)ref->tag);
    ref->tag = NULL;
    free((char *)ref->log);
    ref->log = NULL;
    clogger_mutex_destroy(ref->mutex);
    ref->mutex = NULL;
    free(ref);
    ref = NULL;
}

void clogger_init(void)
{
    clogger_q_create(&q_log_queue);
    memset(callback_list, 0, sizeof(clogger_callback) * LOG_CALLBACK_NUM);
    callback_list_num = 0;
}

/**
 * @brief NDK部分的clogger_log函数实现
 *
 * @param type 日志类型，比如：DEBUG,APACHE等等
 * @param level 日志级别，比如：D V I等
 * @param src_tag 日志TAG
 * @param fmt 日志format
 * @param ...
 */
void clogger_log(const char *src_type, int level, const char *src_tag, const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);

    char *buf = malloc(CLOGGER_SIZE);
    memset(buf, 0, CLOGGER_SIZE);
    vsnprintf(buf, CLOGGER_SIZE - 1, fmt, ap);

    int tag_len = strlen(src_tag) + 1;
    char *tag = malloc(tag_len);
    memset(tag, 0, tag_len);
    strcpy(tag, src_tag);

    int type_len = strlen(src_type) + 1;
    char *type = malloc(type_len);
    memset(type, 0, type_len);
    strcpy(type, src_type);

    clogger_ref *ref = clogger_ref_create(type, level, tag, buf, free_log_ref);
    if (ref == NULL)
    {
        return;
    }

    switch (level)
    {
    case CLOGGER_LEVEL_DEBUG:
        for (int i = 0; i < LOG_CALLBACK_NUM; i++)
        {
            if (callback_list[i].debug_callback != NULL)
            {
                (*callback_list[i].debug_callback)(ref);
            }
        }
        break;

    case CLOGGER_LEVEL_INFO:
        for (int i = 0; i < LOG_CALLBACK_NUM; i++)
        {
            if (callback_list[i].info_callback != NULL)
            {
                (*callback_list[i].info_callback)(ref);
            }
        }
        break;

    case CLOGGER_LEVEL_VERBOSE:
        for (int i = 0; i < LOG_CALLBACK_NUM; i++)
        {
            if (callback_list[i].verbose_callback != NULL)
            {
                (*callback_list[i].verbose_callback)(ref);
            }
        }
        break;

    case CLOGGER_LEVEL_WARNING:
        for (int i = 0; i < LOG_CALLBACK_NUM; i++)
        {
            if (callback_list[i].warning_callback != NULL)
            {
                (*callback_list[i].warning_callback)(ref);
            }
        }
        break;

    case CLOGGER_LEVEL_ERROR:
        for (int i = 0; i < LOG_CALLBACK_NUM; i++)
        {
            if (callback_list[i].error_callback != NULL)
            {
                (*callback_list[i].error_callback)(ref);
            }
        }
        break;

    case CLOGGER_LEVEL_WTF:
        for (int i = 0; i < LOG_CALLBACK_NUM; i++)
        {
            if (callback_list[i].wtf_callback != NULL)
            {
                (*callback_list[i].wtf_callback)(ref);
            }
        }
        break;

    default:
        break;
    }

    va_end(ap);
}
