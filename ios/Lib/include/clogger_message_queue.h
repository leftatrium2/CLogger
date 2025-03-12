#ifndef _CLOGGER_MESSAGE_QUEUE_H_
#define _CLOGGER_MESSAGE_QUEUE_H_

#include "clogger_list.h"
#include "clogger_ref.h"

typedef enum _clogger_q_name_e_
{
    clogger_q_savefile = 0,
    clogger_q_logan,
    clogger_q_max
} clogger_q_name_e_;

typedef enum _clogger_q_event_e_
{
    CLOGGER_Q_EVENT_POST = 0,
    CLOGGER_Q_EVENT_CLOSE,
    CLOGGER_Q_EVENT_ENABLE_TRUE,
    CLOGGER_Q_EVENT_ENABLE_FALSE
} clogger_q_event_e;

typedef struct _clogger_queue
{
    struct q_head msg_q[clogger_q_max];
    pthread_cond_t has_node[clogger_q_max];
} clogger_queue;

typedef struct _clogger_q_node_t_
{
    unsigned int msg;
    int level;
    int is_main;
    const clogger_ref *ref;
    struct list_head list;
} clogger_q_node_t_;

void *clogger_q_get_msg_q(clogger_queue *ipc_msg_q, clogger_q_name_e_ a_msgname);
long clogger_q_create(clogger_queue *msg_q);
long clogger_q_wait(clogger_queue *ipc_msg_q, clogger_q_name_e_ fd, unsigned int *msg, int *is_main, clogger_ref **ref, int *level);
long clogger_q_post(clogger_queue *ipc_msg_q, clogger_q_name_e_ peer_fd, unsigned int msg, int is_main, clogger_ref *ref, int level);
void clogger_q_clear(clogger_queue *ipc_msg_q, clogger_q_name_e_ fd);
void clogger_q_destroy(clogger_queue *ipc_msg_q);
#endif