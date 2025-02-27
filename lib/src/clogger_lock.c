
#include <pthread.h>
#include <stdlib.h>

// On sucess, returns 0.
void *clogger_mutex_init(void)
{
	pthread_mutex_t *hmutex = malloc(sizeof(pthread_mutex_t));
	if (!hmutex)
	{
		return NULL;
	}
	if (pthread_mutex_init(hmutex, NULL))
	{
		free(hmutex);
		return NULL;
	}
	return (void *)hmutex;
}

// On sucess, returns 0.
long clogger_mutex_lock(void *hmutex)
{
	return pthread_mutex_lock((pthread_mutex_t *)hmutex);
}

// On sucess, returns 0.
long clogger_mutex_unlock(void *hmutex)
{
	return pthread_mutex_unlock((pthread_mutex_t *)hmutex);
}

void clogger_mutex_destroy(void *hmutex)
{
	if (hmutex)
	{
		pthread_mutex_destroy((pthread_mutex_t *)hmutex);
		free(hmutex);
	}
}
