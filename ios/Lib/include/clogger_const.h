#ifndef _CLOGGER_CONST_H_
#define _CLOGGER_CONST_H_

// Minimum SD card capacity
#define MIN_SDCARD 52428800L
// The maximum number of queues
#define MAX_QUEUE 500L
// The number of days it is kept
#define MAX_DAY 604800000L
// Maximum file size
#define MAX_FILE 10485760L

// Level section
#define CLOGGER_LEVEL_DEBUG 1
#define CLOGGER_LEVEL_INFO 2
#define CLOGGER_LEVEL_VERBOSE 3
#define CLOGGER_LEVEL_WARNING 4
#define CLOGGER_LEVEL_ERROR 5
#define CLOGGER_LEVEL_WTF 6

// type section
#define CLOGGER_TYPE "CLOGGER"

#define CLOGGER_FLAG_UNKNOWN 0
#define CLOGGER_FLAG_API 1

#endif //_CLOGGER_CONST_H_
