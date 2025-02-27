#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <sys/errno.h>
#include <string.h>
#include <dirent.h>
#include "clogger_utils.h"
#include "clogger.h"
#include "clogger_print.h"

/**
 * @brief 获取格式化时间，格式：[yyyy-mm-dd]
 *
 * @param length
 * @param time_str
 * @return int
 */
int get_date(int length, char *time_str)
{
    time_t t;
    struct tm *curr_tm;
    time(&t);
    curr_tm = localtime(&t);
    snprintf(time_str, length - 1, "%d-%02d-%02d", (1900 + curr_tm->tm_year), (curr_tm->tm_mon + 1), curr_tm->tm_mday);
    return 0;
}

/**
 * @brief 获取格式化时间，格式为：[yyyy-mm-dd hh:mm:ss]
 *
 * @param length
 * @param time_str
 * @return int
 */
int get_datetime(int length, char *time_str)
{
    time_t t;
    struct tm *curr_tm;
    t = time(NULL);
    curr_tm = localtime(&t);
    snprintf(time_str, length - 1, "%d-%02d-%02d %02d:%02d:%02d:000",
             (1900 + curr_tm->tm_year),
             (curr_tm->tm_mon + 1),
             curr_tm->tm_mday,
             curr_tm->tm_hour,
             curr_tm->tm_min,
             curr_tm->tm_sec);
    return 0;
}

/**
 * @brief 获取FakeTime，【1970-01-01 00:00:00】
 *
 * @param length
 * @param time_str
 * @return int
 */
int get_faketime(int length, char *time_str)
{
    snprintf(time_str, length - 1, "1970-01-01 08:00:00:000");
    return 0;
}

/**
 * @brief 给定时间戳，获取时间间隔
 *
 * @param ts
 * @return int 间隔的秒数
 */
int get_date_i(unsigned long *ts)
{
    time_t t;
    struct tm *curr_tm;
    time(&t);
    curr_tm = localtime(&t);
    long split = curr_tm->tm_hour * 60 * 60 + curr_tm->tm_min * 60 + curr_tm->tm_sec;
    *ts = (long)t - split;
    return 0;
}

/**
 * @brief 当前时间戳，单位：毫秒
 *
 * @return long 毫秒
 */
long long get_ts()
{
    struct timeval tv;
    int ret = gettimeofday(&tv, NULL);
    long long time = ((long long)tv.tv_sec) * 1000 + ((long long)tv.tv_usec) / 1000;
    clogger_internal_e("get_ts:%lld, tv_sec:%ld, tv_usec:%ld", time, tv.tv_sec, tv.tv_usec);
    return time;
}

/**
 * @brief 计算当天的0点毫秒数
 *
 * @return long long 毫秒
 */
long long get_current_time_ms()
{
    return get_current_time_s() * 1000;
}

/**
 * @brief 计算当天的0点秒
 *
 * @return long long 秒
 */
long long get_current_time_s()
{
    time_t timep;
    struct tm *p;
    time(&timep);
    p = localtime(&timep);
    p->tm_hour = 0;
    p->tm_min = 0;
    p->tm_sec = 0;
    timep = mktime(p);
    return timep;
}

/**
 * @brief 通过给定level，得到字符形式的level
 *
 * @param level 数值
 * @return char 字符
 */
char get_level(int level)
{
    char chr = 'I';
    switch (level)
    {
    case CLOGGER_LEVEL_DEBUG:
        chr = 'D';
        break;
    case CLOGGER_LEVEL_INFO:
        chr = 'I';
        break;
    case CLOGGER_LEVEL_VERBOSE:
        chr = 'V';
        break;
    case CLOGGER_LEVEL_WARNING:
        chr = 'W';
        break;
    case CLOGGER_LEVEL_ERROR:
        chr = 'E';
        break;
    case CLOGGER_LEVEL_WTF:
        chr = 'F';
        break;

    default:
        break;
    }
    return chr;
}

/**
 * @brief 从字符串类型的type，导出logan使用的flag
 *
 * @param type
 * @return int
 */
int get_type_flag(const char *type)
{
    int type_len = strlen(type);
    if (!strncmp(type, CLOGGER_TYPE_APACHE, type_len))
    {
        return CLOGGER_FLAG_APACHE;
    }
    else if (!strncmp(type, CLOGGER_TYPE_API, type_len))
    {
        return CLOGGER_FLAG_API;
    }
    else if (!strncmp(type, CLOGGER_TYPE_APM, type_len))
    {
        return CLOGGER_FLAG_APM;
    }
    else if (!strncmp(type, CLOGGER_TYPE_BIZ_SIMA, type_len))
    {
        return CLOGGER_FLAG_BIZ_SIMA;
    }
    else if (!strncmp(type, CLOGGER_TYPE_DEBUG, type_len))
    {
        return CLOGGER_FLAG_DEBUG;
    }
    else if (!strncmp(type, CLOGGER_TYPE_LIFECYCLE, type_len))
    {
        return CLOGGER_FLAG_LIFECYCLE;
    }
    return CLOGGER_FLAG_UNKNOWN;
}