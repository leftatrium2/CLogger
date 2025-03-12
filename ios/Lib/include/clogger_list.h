#ifndef __CLOGGER_LIST_H__
#define __CLOGGER_LIST_H__

#include <pthread.h>
#include "clogger_lock.h"

struct list_head
{
	struct list_head *next, *prev;
};

#define list_entry(ptr, type, member) \
	((type *)((char *)(ptr) - (unsigned long)(&((type *)0)->member)))

#define list_for_each_entry(pos, head, member)                 \
	for (pos = list_entry((head)->next, typeof(*pos), member); \
		 &pos->member != (head);                               \
		 pos = list_entry(pos->member.next, typeof(*pos), member))

void clogger_list_del(struct list_head *entry);
long clogger_list_empty(const struct list_head *head);
void clogger_list_add(struct list_head *newly, struct list_head *head);
void clogger_list_add_tail(struct list_head *newly, struct list_head *head);
void clogger_list_init(struct list_head *list);

////////////////////////// q  API ///////////////////////////////////////////

typedef enum _q_node_mode_e_
{
	clogger_q_mode_unblock = 0x0,
	clogger_q_mode_block_empty = 0x1,
	clogger_q_mode_block_full = 0x2,
	clogger_q_mode_max
} q_node_mode_e;

typedef enum _q_node_property_e_
{
	clogger_q_node_max_nr = 0,
	clogger_q_node_empty_func,
	clogger_q_node_full_func,
	clogger_q_node_push_func,
	clogger_q_node_pop_func,
	clogger_q_node_priv_data,
	clogger_q_node_max
} q_node_property_e;

typedef long (*clogger_q_check_full_cb_t)(void *);
typedef long (*clogger_q_check_empty_cb_t)(void *);
typedef void (*clogger_q_full_cb_t)(void *, void *);
typedef void (*clogger_q_empty_cb_t)(void *, void *);
typedef void (*clogger_q_push_cb_t)(void *, void *, struct list_head *newly);
typedef void (*clogger_q_pop_cb_t)(void *, void *, struct list_head *poped);

struct q_head
{
	struct list_head lst_head;
	void *mutex;			  // q mutex lock
	long node_nr;			  // node count
							  //    long acc_node_nr;   // accumulate node count
	long max_node_nr;		  // upper limit node count
	q_node_mode_e mode;		  // once this mode value is set, you should never change it during the q's life
	pthread_cond_t has_node;  // if empty, blocked
	pthread_cond_t has_space; // if full, blocked
	clogger_q_check_full_cb_t is_full_func;
	clogger_q_check_empty_cb_t is_empty_func;
	clogger_q_full_cb_t full_func;
	clogger_q_empty_cb_t empty_func;
	clogger_q_push_cb_t push_func;
	clogger_q_pop_cb_t pop_func;
	void *empty_parm;
	void *full_parm;
	long stop_blocking_empty;
	long stop_blocking_full;
	int64_t data_size;
	void *priv;
};

void q_set_property(struct q_head *q_head, q_node_property_e property, void *parm1, void *parm2);
long q_init(struct q_head *q_head, q_node_mode_e mode);
void q_destroy(struct q_head *q_head);
long q_push(struct list_head *newly, struct q_head *q_head);
long q_is_empty(struct q_head *q_head);
struct list_head *q_get_first(struct q_head *q_head);
struct list_head *q_pop(struct q_head *q_head);
long q_get_max_node_nr(struct q_head *q_head);
long q_get_node_nr(struct q_head *q_head);

#endif //__CLOGGER_LIST_H__
