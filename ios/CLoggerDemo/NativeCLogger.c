#include "NativeCLogger.h"
#include "clogger_const.h"

#define TAG "MyJNI"

void testPrint(void)
{
    const char* str = "hello debug log!";
    clogger_log(CLOGGER_TYPE_DEBUG, CLOGGER_LEVEL_DEBUG, TAG, str);
}
