#include "CLoggerIOSUtils.h"
#include "clogger_print.h"

void free_ios_log_ref(clogger_ref *ref)
{
    clogger_internal_e("free now, tag: %s, log: %s", ref->tag, ref->log);
    ref->type = NULL;
    ref->tag = NULL;
    ref->log = NULL;
    clogger_mutex_destroy(ref->mutex);
    ref->mutex = NULL;
    free(ref);
    ref = NULL;
}

clogger_ref *create_ios_ref(const char *type,unsigned int level,const char *tag, const char* message)
{
    return clogger_ref_create(type, level, tag, message, free_ios_log_ref);
}
