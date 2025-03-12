#ifndef _CLOGGER_REF_H_
#define _CLOGGER_REF_H_

#include "clogger_lock.h"

typedef struct _clogger_ref
{
    const char *type;
    int level;
    const char *tag;
    const char *log;
    int count;
    void (*free)(struct _clogger_ref *ref);
    void *mutex;
} clogger_ref;

typedef void (*FREE_FUNC)(struct _clogger_ref *ref);

clogger_ref *clogger_ref_create(const char *type, int level, const char *tag, const char *log, FREE_FUNC func);
void clogger_ref_inc(clogger_ref *ref);
void clogger_ref_dec(clogger_ref *ref);

#endif