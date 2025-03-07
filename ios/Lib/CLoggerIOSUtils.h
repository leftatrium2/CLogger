#ifndef CLoggerIOSUtils_h
#define CLoggerIOSUtils_h

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "clogger_ref.h"
#include "clogger.h"

void free_ios_log_ref(clogger_ref *ref);

clogger_ref *create_ios_ref(const char *type,unsigned int level,const char *tag, const char* message);

#endif 
