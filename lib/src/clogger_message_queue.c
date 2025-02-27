#include <stdlib.h>
#include <stdio.h>
#include "clogger_message_queue.h"
#include "clogger_utils.h"
#include "clogger_print.h"
#include "clogger_ref.h"

void *clogger_q_get_msg_q(clogger_queue *ipc_msg_q, clogger_q_name_e_ a_msgname)
{
    return (void *)&ipc_msg_q->msg_q[a_msgname];
}
long clogger_q_create(clogger_queue *msg_q)
{
    long i;
    for (i = 0; i < clogger_q_max; i++)
    {
        q_init(&msg_q->msg_q[i], clogger_q_mode_block_empty);
    }
    return 0;
}
long clogger_q_wait(clogger_queue *ipc_msg_q, clogger_q_name_e_ fd, unsigned int *msg, int *is_main, clogger_ref **ref, int *level)
{
    struct list_head *ptr;
    clogger_q_node_t_ *msg_node = NULL;

redo:
    ptr = q_pop(&ipc_msg_q->msg_q[fd]);

    if (!ptr)
    {
        clogger_internal_e(" q already empty, fd = %d,do not blocked!\n", fd);
        return -1;
    }
    else
    {
        msg_node = (clogger_q_node_t_ *)list_entry(ptr, clogger_q_node_t_, list);
        if (!msg_node)
        {
            goto redo;
        }
        *msg = msg_node->msg;
        *level = msg_node->level;
        *ref = (clogger_ref *)msg_node->ref;
        *is_main = msg_node->is_main;
        free(msg_node);
        return 0;
    }
}

long clogger_q_post(clogger_queue *ipc_msg_q, clogger_q_name_e_ peer_fd, unsigned int msg, int is_main, clogger_ref *ref, int level)
{
    clogger_q_node_t_ *msg_node;
    msg_node = (clogger_q_node_t_ *)malloc(sizeof(clogger_q_node_t_));
    if (!msg_node)
    {
        clogger_internal_e("ipc: alloc msg_node err!\n");
        return -1;
    }
    msg_node->msg = msg;
    msg_node->level = level;
    msg_node->ref = ref;
    msg_node->is_main = is_main;
    q_push(&msg_node->list, &ipc_msg_q->msg_q[peer_fd]);
    return 0;
}

void clogger_q_clear(clogger_queue *ipc_msg_q, clogger_q_name_e_ fd)
{
    clogger_q_node_t_ *msg_node;
    struct list_head *poped_item;
    struct q_head *q_head = &ipc_msg_q->msg_q[fd];
    clogger_mutex_lock(q_head->mutex);
    clogger_internal_e("clearing fd %d\n", fd);
    while (!clogger_list_empty(&q_head->lst_head))
    {
        poped_item = q_head->lst_head.next;
        clogger_list_del(poped_item);
        q_head->node_nr--;
        msg_node = (clogger_q_node_t_ *)list_entry(poped_item, clogger_q_node_t_, list);
        clogger_internal_e("skipping msg %ld,fd = %d\n", msg_node->msg, fd);
        free(msg_node);
    }
    clogger_mutex_unlock(q_head->mutex);
}

void clogger_q_destroy(clogger_queue *ipc_msg_q)
{
    long i;
    clogger_internal_e("ipc: destroy called...\n");
    for (i = 0; i < clogger_q_max; i++)
    {
        clogger_q_clear(ipc_msg_q, (clogger_q_name_e_)i);
        q_destroy(&ipc_msg_q->msg_q[i]);
    }
}