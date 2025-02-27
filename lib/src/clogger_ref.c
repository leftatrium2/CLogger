#include <stdlib.h>
#include <string.h>
#include "clogger_ref.h"
#include "clogger_print.h"

clogger_ref *clogger_ref_create(const char *type, int level, const char *tag, const char *log, FREE_FUNC func)
{
    clogger_ref *ref = malloc(sizeof(clogger_ref));
    if (ref == NULL)
    {
        return NULL;
    }
    memset(ref, 0, sizeof(clogger_ref));
    ref->type = type;
    ref->level = level;
    ref->tag = tag;
    ref->log = log;
    ref->count = 0;
    ref->free = func;
    ref->mutex = clogger_mutex_init();
    if (ref->mutex == NULL)
    {
        return NULL;
    }
    return ref;
}
void clogger_ref_inc(clogger_ref *ref)
{
    if (ref != NULL)
    {
        clogger_mutex_lock(ref->mutex);
        ref->count++;
        clogger_mutex_unlock(ref->mutex);
    }
}
void clogger_ref_dec(clogger_ref *ref)
{
    if (ref != NULL)
    {
        clogger_mutex_lock(ref->mutex);
        ref->count--;
        clogger_mutex_unlock(ref->mutex);
        if (ref->count == 0)
        {
            ref->free(ref);
        }
    }
}
