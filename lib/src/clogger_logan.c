#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include "clogan_core.h"
#include "clogan_status.h"
#include "clogger.h"
#include "clogger_print.h"
#include "clogger_logan.h"
#include "clogger_utils.h"
#include "clogger_message_queue.h"
#include "clogger_platform.h"

#define LOG_SEPARATOR "&&&"
#define LOG_SEGMENT_SEPARATOR "|||"
#define LOG_SEGMENT_DEFAULT "__d__"
#define ENCRYPT_KEY16 "0123456789012345"
#define ENCRYPT_IV16 "0123456789012345"
#define LOGAN_THREAD_NAME "logan_thread"

#define _MAX_LOGAN_FILE_LINE_LEN (CLOGGER_SIZE + 300)

static pthread_t _p_logan_id;
static long long _current_day;   // 比对LoganThread.java里面的mCurrentDay
static long long _last_time;     // 比对LoganThread.java里面的mLastTime
static int _is_sdcard_can_write; // sd卡是否有可用空间，默认剩余50M
static int _is_clogan_open;
static clogger_logan_config _logan_config;
static int _enable;
static int _is_inited;

/**
 * @brief 删除超过时间限制的文件，照搬LoganThread类中的deleteExpiredFile方法
 *
 * @param date_time 有效时间，单位：秒
 */
static void _delete_expired_file(const unsigned long date_time)
{
    DIR *dir = NULL;
    if (access(_logan_config.path, F_OK))
    {
        // 文件夹不存在
        clogger_internal_e("delete_expired_file path is not exists!");
        return;
    }
    dir = opendir(_logan_config.path);
    if (dir == NULL)
    {
        return;
    }
    struct dirent *ptr;
    char delim[] = ".";
    char full_file_path[_MAX_FILE_PATH_SIZE];
    while ((ptr = readdir(dir)) != NULL)
    {
        char *file_name = ptr->d_name;
        if (file_name == NULL || strlen(file_name) == 0)
        {
            continue;
        }

        const char *pre_str = strtok(file_name, delim);
        if (pre_str == NULL || strlen(pre_str) == 0)
        {
            continue;
        }
        long long long_item = atoll(pre_str);
        if (long_item <= date_time)
        {
            memset(full_file_path, 0, _MAX_FILE_PATH_SIZE);
            snprintf(full_file_path, _MAX_FILE_PATH_SIZE - 1, "%s/%s", _logan_config.path, file_name);
            unlink(full_file_path);
        }
    }

DELETE_EXPIRED_ERROR:
    if (dir != NULL)
    {
        closedir(dir);
    }
}

/**
 * @brief 1day = 86400000L毫秒，也就是说，判断当前时间是否在一天之内
 * 如果是，就不重新open clogan
 * 如果不是，就open一个新的clogan日志文件
 *
 * @return int
 */
static int is_day()
{
    long long current_time = get_ts();
    clogger_internal_e("_current_day:%lld,current_time:%lld", _current_day, current_time);
    return (_current_day < current_time) && (_current_day + 86400000L > current_time);
}

/**
 * @brief 基本照抄LoganThread类中的doWriteLog2File方法
 *
 */
static void _do_write_logan_file(const char *type, const char *content, long long local_time, long thread_id, int is_main)
{
    long long current_time = 0;
    int ret = 0;
    if (!is_day())
    {
        current_time = get_current_time_ms();
        _current_day = current_time;
        long delete_time = current_time - _logan_config.max_day;
        _delete_expired_file(delete_time);
        char new_file_path[_MAX_64_BIT_SIZE];
        memset(&new_file_path, 0, _MAX_64_BIT_SIZE);
        snprintf(new_file_path, _MAX_64_BIT_SIZE, "%lld", current_time);
        clogger_internal_e("logan file:%s", new_file_path);
        ret = clogan_open(new_file_path);
        if (ret != CLOGAN_OPEN_SUCCESS)
        {
            clogger_internal_e("cant open logan file!,code :%d", ret);
        }
        else
        {
            _is_clogan_open = 1;
        }
    }
    current_time = get_ts();
    if ((current_time - _last_time) > 60000L)
    {
        // 每60秒没有写入数据，获取一下sdcard的剩余容量
        _is_sdcard_can_write = is_can_write_sdcard(_logan_config.path);
    }
    if ((current_time - _last_time) > 10000L)
    {
        // 每60秒没有写入数据，刷新一次
        int ret = clogan_flush();
        if (ret != CLOGAN_FLUSH_SUCCESS)
        {
            clogger_internal_e("cant flush logan, code: %d", ret);
        }
    }
    _last_time = get_ts();
    int flag = get_type_flag(type);
    clogger_internal_e("is_sdcard_can_write:%d", _is_sdcard_can_write);
    if (_is_sdcard_can_write)
    {
        clogger_internal_e("_do_write_logan_file, type:%s,content:%s,local_time:%ld,thread_id:%d,is_main:%d", type, content, local_time, thread_id, is_main);
        ret = clogan_write(flag, (char *)content, local_time, LOGAN_THREAD_NAME, thread_id, is_main);
        if (ret != CLOGAN_WRITE_SUCCESS)
        {
            clogger_internal_e("cant write logan, code:%d", ret);
        }
    }
}

static void *_thread_logan_running(void *args)
{
    int ret = 0;
    clogger_ref *ref;
    int is_main = 0;
    int level = -1;
    int msg = -1;
    while (1)
    {
        ret = clogger_q_wait(&q_log_queue, clogger_q_logan, &msg, &is_main, &ref, &level);
        if (ret < 0)
        {
            clogger_internal_e("wait tea_ipc_wait error: %ld", ret);
            continue;
        }
        if (msg == CLOGGER_Q_EVENT_CLOSE)
        {
            // 收到close信号，关闭线程，并且处理一些资源问题
            clogger_logan_flush();
            _is_clogan_open = 0;
            clogger_q_destroy(&q_log_queue);
            break;
        }
        else if (msg == CLOGGER_Q_EVENT_ENABLE_TRUE)
        {
            clogger_internal_e("logan switch to enable");
            _enable = 1;
        }
        else if (msg == CLOGGER_Q_EVENT_ENABLE_FALSE)
        {
            clogger_internal_e("logan switch to disable");
            _enable = 0;
        }
        else if (msg == CLOGGER_Q_EVENT_POST)
        {
            if (!_enable)
            {
                clogger_internal_e("write logan log is closed!");
                continue;
            }
            char content[_MAX_LOGAN_FILE_LINE_LEN];
            memset(&content, 0, _MAX_LOGAN_FILE_LINE_LEN);
            char datetime[30];
            memset(&datetime, 0, 30);
            if (_logan_config.faketime)
            {
                get_faketime(30, datetime);
            }
            else
            {
                get_datetime(30, datetime);
            }
            snprintf(content, _MAX_LOGAN_FILE_LINE_LEN - 1, "%s%s%c%s%s%s%s%s%s",
                     datetime, LOG_SEPARATOR,
                     get_level(level), LOG_SEPARATOR,
                     ref->type, LOG_SEPARATOR,
                     ref->tag, LOG_SEPARATOR,
                     ref->log);
            long long curr_ts = get_ts();
            clogger_internal_e("_thread_logan_running content:%s", content);
            clogger_internal_e("_thread_logan_running curr_ts:%ld", curr_ts);

            _do_write_logan_file(ref->type, content, curr_ts, (long)pthread_self, is_main);
            clogger_ref_dec(ref);
        }
    }
    return NULL;
}

void clogger_logan_write(int level, const clogger_ref *ref)
{

    if (ref != NULL)
    {
        clogger_q_post(&q_log_queue, clogger_q_logan, CLOGGER_Q_EVENT_POST, is_main_thread(), (clogger_ref *)ref, level);
        clogger_ref_inc((clogger_ref *)ref);
    }
}

static void _clogger_clogan_init()
{
    if (get_is_init_ok())
    {
        return;
    }
    int ret = clogan_init(_logan_config.cache_path, _logan_config.path, _logan_config.max_file, ENCRYPT_KEY16, ENCRYPT_IV16);
    if (ret != CLOGAN_INIT_SUCCESS_MMAP && ret != CLOGAN_INIT_SUCCESS_MEMORY)
    {
        goto err;
    }
    clogan_debug(_logan_config.debug);
    return;
err:
    clogger_internal_e("cant init clogan,code :%d", ret);
    return;
}

void clogger_logan_init(const char *cache_path, const char *dir_path, int max_file, int max_day, int debug, int use_faketime)
{
    _is_inited = 0;
    _enable = 0;
    _is_clogan_open = 0;
    clogger_internal_e("clogger_logan_init, cache path:%s, dir path:%s, max file:%d, max day:%d, debug:%d, faketime:%d", cache_path, dir_path, max_file, max_day, debug, use_faketime);
    callback_list[LOGAN_INDEX].verbose_callback = clogger_logan_logv;
    callback_list[LOGAN_INDEX].debug_callback = clogger_logan_logd;
    callback_list[LOGAN_INDEX].info_callback = clogger_logan_logi;
    callback_list[LOGAN_INDEX].warning_callback = clogger_logan_logw;
    callback_list[LOGAN_INDEX].error_callback = clogger_logan_loge;
    callback_list_num++;
    memset(&_logan_config, 0, sizeof(clogger_logan_config));
    snprintf(_logan_config.cache_path, _MAX_FILE_PATH_SIZE, "%s", cache_path);
    snprintf(_logan_config.path, _MAX_FILE_PATH_SIZE, "%s", dir_path);
    _logan_config.max_file = max_file;
    _logan_config.max_day = max_day * 86400000L;
    _logan_config.debug = debug;
    _logan_config.faketime = use_faketime;
    _current_day = 0;
    _last_time = 0;
    _is_sdcard_can_write = 0;
    _logan_config.thread_id = pthread_self();
    _clogger_clogan_init();
    pthread_create(&_p_logan_id, NULL, _thread_logan_running, NULL);
    _is_inited = 1;
    _enable = 1;
}

void clogger_logan_destroy()
{
    clogger_internal_e("clogger_logan_destroy");
    clogger_q_post(&q_log_queue, clogger_q_logan, CLOGGER_Q_EVENT_CLOSE, is_main_thread(), NULL, 0);
}

void clogger_logan_flush()
{
    clogger_internal_e("flush logan now!");
    if (_is_clogan_open)
    {
        int ret = clogan_flush();
        if (ret != CLOGAN_FLUSH_SUCCESS)
        {
            clogger_internal_e("cant flush logan, code: %d", ret);
        }
    }
}

void clogger_logan_enable(int enable)
{
    if (_is_inited)
    {
        clogger_q_event_e event;
        if (enable)
        {
            event = CLOGGER_Q_EVENT_ENABLE_TRUE;
        }
        else
        {
            event = CLOGGER_Q_EVENT_ENABLE_FALSE;
        }
        clogger_q_post(&q_log_queue, clogger_q_logan, event, is_main_thread(), NULL, 0);
    }
}

void clogger_logan_logv(const clogger_ref *ref)
{
    clogger_logan_write(CLOGGER_LEVEL_VERBOSE, ref);
}
void clogger_logan_logd(const clogger_ref *ref)
{
    clogger_logan_write(CLOGGER_LEVEL_DEBUG, ref);
}
void clogger_logan_logi(const clogger_ref *ref)
{
    clogger_logan_write(CLOGGER_LEVEL_INFO, ref);
}
void clogger_logan_logw(const clogger_ref *ref)
{
    clogger_logan_write(CLOGGER_LEVEL_WARNING, ref);
}
void clogger_logan_loge(const clogger_ref *ref)
{
    clogger_logan_write(CLOGGER_LEVEL_ERROR, ref);
}
