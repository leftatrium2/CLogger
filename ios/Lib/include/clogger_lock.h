
#ifndef __CLOGGER_LOCK_H__
#define __CLOGGER_LOCK_H__

// On sucess, returns a mutex lock.
void *clogger_mutex_init(void);

// On sucess, returns 0.
long clogger_mutex_lock(void *hmutex);

// On sucess, returns 0.
long clogger_mutex_unlock(void *hmutex);

void clogger_mutex_destroy(void *hmutex);

#endif // __CLOGGER_LOCK_H__
