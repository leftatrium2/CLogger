#ifndef _CLOGGER_LOGAN_H_
#define _CLOGGER_LOGAN_H_

#include "clogger_ref.h"

#define _MAX_FILE_PATH_SIZE 200
#define _MAX_64_BIT_SIZE 20

typedef struct _clogger_logan_config
{
    char cache_path[_MAX_FILE_PATH_SIZE]; // logan cache路径，android默认：getFilesDir().getAbsoluteFile()
    char path[_MAX_FILE_PATH_SIZE];       // logan file路径，android默认：/sdcard/Android/[app]
    int max_file;                         // 一天中最大保存的文件大小，比如：11M
    int max_day;                          // 最大保留的天数，单位：毫秒
    int debug;                            // 是否是debug
    int faketime;                         // 是否使用faketime
    int thread_id;                        // 线程id
} clogger_logan_config;

void clogger_logan_init(const char *cache_path, const char *dir_path, int max_file, int max_day, int debug, int use_faketime);
void clogger_logan_destroy();
void clogger_logan_flush();

void clogger_logan_enable(int enable);

void clogger_logan_logv(const clogger_ref *ref);
void clogger_logan_logd(const clogger_ref *ref);
void clogger_logan_logi(const clogger_ref *ref);
void clogger_logan_logw(const clogger_ref *ref);
void clogger_logan_loge(const clogger_ref *ref);

#endif
