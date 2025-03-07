#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include "clogger.h"
#include "clogger_print.h"
#include "clogger_savefile.h"
#include "clogger_message_queue.h"
#include "clogger_utils.h"
#include "clogger_platform.h"

#define _MAX_FILE_PATH_LEN 100
#define _MAX_FILE_LINE_LEN (CLOGGER_SIZE + 100)

static pthread_t _p_savefile_id;
static FILE *_log_file_p;
static int _is_inited;
static int _enable;

static void *_thread_savefile_running(void *args)
{
    long ret = 0;
    clogger_ref *ref;
    int is_main = 0;
    int level = -1;
    unsigned int msg = -1;
    while (1)
    {
        ret = clogger_q_wait(&q_log_queue, clogger_q_savefile, &msg, &is_main, &ref, &level);
        if (ret < 0)
        {
            clogger_internal_e("wait tea_ipc_wait error: %ld", ret);
            continue;
        }
        if (msg == CLOGGER_Q_EVENT_CLOSE)
        {
            if (_log_file_p != NULL)
            {
                clogger_internal_e("clogger_savefile_destroy fclose");
                fclose(_log_file_p);
            }
            clogger_q_destroy(&q_log_queue);
            break;
        }
        else if (msg == CLOGGER_Q_EVENT_ENABLE_FALSE)
        {
            clogger_internal_e("clogger_savefile_write enable false");
            _enable = 0;
        }
        else if (msg == CLOGGER_Q_EVENT_ENABLE_TRUE)
        {
            clogger_internal_e("clogger_savefile_write enable true");
            _enable = 1;
        }
        else if (msg == CLOGGER_Q_EVENT_POST)
        {
            if (!_enable)
            {
                clogger_internal_e("savefile switch to close!");
                continue;
            }
            if (_log_file_p == NULL)
            {
                clogger_internal_e("the log file not init!");
                continue;
            }
            char content[_MAX_FILE_LINE_LEN];
            memset(&content, 0, _MAX_FILE_LINE_LEN);
            char datetime[30];
            memset(&datetime, 0, 30);
            get_datetime(30, datetime);
            snprintf(content, _MAX_FILE_LINE_LEN - 1, "%s %c/%s %s", datetime, get_level(level), ref->tag, ref->log);
            clogger_internal_e("the savefile log content is %s", content);
            unsigned long ret = fwrite(content, strlen(content), 1, _log_file_p);
            if (ret <= 0)
            {
                clogger_internal_e("cant save savefile log!");
            }
            fflush(_log_file_p);
            clogger_ref_dec(ref);
        }
    }

    return NULL;
}

static void _init_file_path(const char *dir_path)
{
    if (dir_path == NULL)
    {
        clogger_internal_e("dir path is NULL!\n");
        return;
    }
    char full_path[_MAX_FILE_PATH_LEN];
    memset(&full_path, 0, _MAX_FILE_PATH_LEN);

    char curr_time_str[12];
    memset(curr_time_str, 0, 12);
    int ret = get_datetime(12, curr_time_str);
    if (!ret)
    {
        snprintf(full_path, _MAX_FILE_PATH_LEN, "%s/log_%s.log", dir_path, curr_time_str);
    }
    _log_file_p = fopen(full_path, "at+,ccs=UTF-8");
    if (_log_file_p == NULL)
    {
        clogger_internal_e("cant open file: %s\n", full_path);
        return;
    }
}

void clogger_savefile_init(const char *path)
{
    _is_inited = 0;
    _enable = 0;
    callback_list[SAVEFILE_INDEX].verbose_callback = clogger_savefile_logv;
    callback_list[SAVEFILE_INDEX].debug_callback = clogger_savefile_logd;
    callback_list[SAVEFILE_INDEX].info_callback = clogger_savefile_logi;
    callback_list[SAVEFILE_INDEX].warning_callback = clogger_savefile_logw;
    callback_list[SAVEFILE_INDEX].error_callback = clogger_savefile_loge;
    callback_list_num++;
    _init_file_path(path);
    pthread_create(&_p_savefile_id, NULL, _thread_savefile_running, NULL);
    _is_inited = 1;
    _enable = 1;
}

void clogger_savefile_destroy(void)
{
    clogger_internal_e("clogger_savefile_destroy");
    if (_is_inited)
    {
        clogger_q_post(&q_log_queue, clogger_q_savefile, CLOGGER_Q_EVENT_CLOSE, is_main_thread(), NULL, 0);
    }
}

void clogger_savefile_enable(int enable)
{
    if (_is_inited)
    {
        clogger_q_event_e event = CLOGGER_Q_EVENT_ENABLE_TRUE;
        if (enable)
        {
            clogger_internal_e("clogger_savefile_enable set enable true");
            event = CLOGGER_Q_EVENT_ENABLE_TRUE;
        }
        else
        {
            clogger_internal_e("clogger_savefile_enable set enable false");
            event = CLOGGER_Q_EVENT_ENABLE_FALSE;
        }
        clogger_q_post(&q_log_queue, clogger_q_savefile, event, is_main_thread(), NULL, 0);
    }
    else
    {
        clogger_internal_e("savefile module is not inited!cant set enable");
    }
}

void clogger_savefile_write(int level, const clogger_ref *ref)
{

    if (ref != NULL)
    {
        clogger_q_post(&q_log_queue, clogger_q_savefile, CLOGGER_Q_EVENT_POST, is_main_thread(), (clogger_ref *)ref, level);
        clogger_ref_inc((clogger_ref *)ref);
    }
}

void clogger_savefile_logv(const clogger_ref *ref)
{
    if (ref != NULL)
    {
        clogger_internal_e("clogger_savefile_logv tag:%s , buf:%s", ref->tag, ref->log);
        clogger_savefile_write(CLOGGER_LEVEL_VERBOSE, ref);
    }
}
void clogger_savefile_logd(const clogger_ref *ref)
{
    if (ref != NULL)
    {
        clogger_internal_e("clogger_savefile_logd tag:%s , buf:%s", ref->tag, ref->log);
        clogger_savefile_write(CLOGGER_LEVEL_DEBUG, ref);
    }
}
void clogger_savefile_logi(const clogger_ref *ref)
{
    if (ref != NULL)
    {
        clogger_internal_e("clogger_savefile_logi tag:%s , buf:%s", ref->tag, ref->log);
        clogger_savefile_write(CLOGGER_LEVEL_INFO, ref);
    }
}
void clogger_savefile_logw(const clogger_ref *ref)
{
    if (ref != NULL)
    {
        clogger_internal_e("clogger_savefile_logw tag:%s , buf:%s", ref->tag, ref->log);
        clogger_savefile_write(CLOGGER_LEVEL_WARNING, ref);
    }
}
void clogger_savefile_loge(const clogger_ref *ref)
{
    if (ref != NULL)
    {
        clogger_internal_e("clogger_savefile_loge tag:%s , buf:%s", ref->tag, ref->log);
        clogger_savefile_write(CLOGGER_LEVEL_ERROR, ref);
    }
}
