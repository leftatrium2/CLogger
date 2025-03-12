#ifndef _CLOGGER_UTILS_H_
#define _CLOGGER_UTILS_H_

//#define LOGTYPE_UNKNOWN 0
//#define LOGTYPE_APACHE 1
//#define LOGTYPE_BIZ_SIMA 2
//#define LOGTYPE_APM 3
//#define LOGTYPE_LIFECYCLE 4
//#define LOGTYPE_DEBUG 5
//#define LOGTYPE_API 6

// YYYY-MM-DD方式，字符串
int get_date(int length, char *time_str);
// // YYYY-MM-DD方式的秒表示
int get_date_i(unsigned long *ts);
int get_datetime(int length, char *time_str);
long long get_ts(void);
long long get_current_time_ms(void);
long long get_current_time_s(void);
int get_faketime(int length,char *time_str);
char get_level(int level);
int get_type_flag(const char *type);
int delete_expired_file(const unsigned long date_time, const char *path);

#endif
