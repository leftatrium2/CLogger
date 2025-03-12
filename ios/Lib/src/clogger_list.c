
#include "clogger_list.h"
#include "clogger_print.h"

static void __list_add(struct list_head *newly,
					   struct list_head *prev,
					   struct list_head *next)
{
	if (prev != NULL)
	{
		next->prev = newly;
		newly->next = next;
		newly->prev = prev;
		prev->next = newly;
	}
}

static void __list_del(struct list_head *prev, struct list_head *next)
{
	next->prev = prev;
	prev->next = next;
}

void clogger_list_add(struct list_head *newly, struct list_head *head)
{
	__list_add(newly, head, head->next);
}

void clogger_list_add_tail(struct list_head *newly, struct list_head *head)
{
	__list_add(newly, head->prev, head);
}

void clogger_list_del(struct list_head *entry)
{
	__list_del(entry->prev, entry->next);
}

long clogger_list_empty(const struct list_head *head)
{
	return (head->next == head);
}

void clogger_list_init(struct list_head *list)
{
	list->next = list;
	list->prev = list;
}

////////////////////////////////////// q API ///////////////////////////////////////

void q_set_property(struct q_head *q_head, q_node_property_e property, void *parm1, void *parm2)
{
	clogger_mutex_lock(q_head->mutex);
	switch (property)
	{
	case clogger_q_node_max_nr:
	{
		q_head->max_node_nr = (long)parm1;
		break;
	}
	case clogger_q_node_empty_func:
	{
		q_head->empty_func = (clogger_q_empty_cb_t)parm1;
		q_head->empty_parm = parm2;
		break;
	}
	case clogger_q_node_full_func:
	{
		q_head->full_func = (clogger_q_full_cb_t)parm1;
		q_head->full_parm = parm2;
		break;
	}
	case clogger_q_node_push_func:
	{
		q_head->push_func = (clogger_q_push_cb_t)parm1;
		break;
	}
	case clogger_q_node_pop_func:
	{
		q_head->pop_func = (clogger_q_pop_cb_t)parm1;
		break;
	}
	case clogger_q_node_priv_data:
	{
		q_head->priv = parm1;
		break;
	}
	default:
		break;
	}
	clogger_mutex_unlock(q_head->mutex);
	return;
}

static long clogger_q_default_is_full_func(void *param)
{
	struct q_head *q_head = (struct q_head *)(param);
	return (q_head->node_nr >= q_head->max_node_nr);
}

static long clogger_q_default_is_empty_func(void *param)
{
	struct q_head *q_head = (struct q_head *)(param);
	return (!q_head->node_nr);
}

long q_init(struct q_head *q_head, q_node_mode_e mode)
{
	//	memset(q_head,0,sizeof(struct q_head));
	clogger_list_init(&q_head->lst_head);
	q_head->node_nr = 0;
	q_head->mutex = clogger_mutex_init();
	if (!q_head->mutex)
	{
		clogger_internal_e("cant init mutex on q_init func\n");
		return -1;
	}

	q_head->mode = mode;

	if (mode & clogger_q_mode_block_empty)
	{
		pthread_cond_init(&q_head->has_node, (const pthread_condattr_t *)NULL);
	}

	if (mode & clogger_q_mode_block_full)
	{
		pthread_cond_init(&q_head->has_space, (const pthread_condattr_t *)NULL);
	}

	q_head->max_node_nr = 0xFFFF; // default value
	q_head->is_full_func = clogger_q_default_is_full_func;
	q_head->is_empty_func = clogger_q_default_is_empty_func;

	return 0;
}

void q_destroy(struct q_head *q_head)
{
	if (q_head->mode & clogger_q_mode_block_empty)
	{
		pthread_cond_destroy(&q_head->has_node);
	}

	if (q_head->mode & clogger_q_mode_block_full)
	{
		pthread_cond_destroy(&q_head->has_space);
	}

	clogger_mutex_destroy(q_head->mutex);
}

//
// @ return value:
// 0 : item is pushed
// -1:  q full , item is not pushed
//
long q_push(struct list_head *newly, struct q_head *q_head)
{
	// clogger_mutex_lock(q_head->mutex);
	if (q_head->mode & clogger_q_mode_block_full)
	{
		// while(q_head->node_nr >= q_head->max_node_nr)
		while (q_head->is_full_func(q_head))
		{
			// block until newly node added
			if (q_head->full_func)
			{
				// clogger_mutex_unlock(q_head->mutex);
				q_head->full_func(q_head->priv, q_head->full_parm);
			}

			clogger_mutex_lock(q_head->mutex);
			pthread_cond_wait(&q_head->has_space, (pthread_mutex_t *)q_head->mutex);
			clogger_mutex_unlock(q_head->mutex);

			if (q_head->stop_blocking_full)
			{
				clogger_internal_e("stop blocking full...\n");
				break;
			}
		}
	}
	else
	{
		// if(q_head->node_nr >= q_head->max_node_nr)
		if (q_head->is_full_func)
		{
			if (q_head->is_full_func(q_head))
			{
				if (q_head->full_func)
				{
					q_head->full_func(q_head->priv, q_head->full_parm);
				}
			}
		}
	}

	clogger_mutex_lock(q_head->mutex);
	clogger_list_add_tail(newly, &q_head->lst_head);
	q_head->node_nr++;
	clogger_mutex_unlock(q_head->mutex);
	if (q_head->mode & clogger_q_mode_block_empty)
	{
		pthread_cond_signal(&q_head->has_node);
	}
	if (q_head->push_func)
	{
		q_head->push_func(q_head->priv, q_head, newly);
	}
	return 0;
}

long q_is_empty(struct q_head *q_head)
{
	return (!q_head->node_nr);
}

long q_get_node_nr(struct q_head *q_head)
{
	return q_head->node_nr;
}

long q_get_max_node_nr(struct q_head *q_head)
{
	return q_head->max_node_nr;
}

// if already empty, would block if mode is block, otherwise returns NULL
struct list_head *q_pop(struct q_head *q_head)
{
	struct list_head *poped_item;
	if (NULL == q_head)
	{
		clogger_internal_e("q_head is NULL!\n");
		return (struct list_head *)NULL;
	}
	clogger_mutex_lock(q_head->mutex);

	if (q_head->mode & clogger_q_mode_block_empty)
	{
		// block mode
		// while(list_empty(&q_head->lst_head))
		while (q_head->is_empty_func(q_head))
		{
			// block until newly code added
			if (q_head->empty_func)
			{
				clogger_internal_e("pop empty wait, calling empty func\n");
				clogger_mutex_unlock(q_head->mutex);
				q_head->empty_func(q_head->priv, q_head->empty_parm);
				clogger_mutex_lock(q_head->mutex);
			}
			pthread_cond_wait(&q_head->has_node, (pthread_mutex_t *)q_head->mutex);
			if (q_head->stop_blocking_empty)
			{
				clogger_internal_e("stop blocking empty...\n");
				break;
			}
		}
	}
	else
	{
		// unblock mode
		// if(list_empty(&q_head->lst_head))
		if (q_head->is_empty_func(q_head))
		{
			// unblock mode
			clogger_mutex_unlock(q_head->mutex);
			if (q_head->empty_func)
			{
				q_head->empty_func(q_head->priv, q_head->empty_parm);
			}
			return (struct list_head *)NULL;
		}
	}

	poped_item = q_head->lst_head.next;
	clogger_list_del(poped_item);
	q_head->node_nr--;
	clogger_mutex_unlock(q_head->mutex);
	if (q_head->mode & clogger_q_mode_block_full)
	{
		pthread_cond_signal(&q_head->has_space);
	}
	if (q_head->pop_func)
	{
		q_head->pop_func(q_head->priv, q_head, poped_item);
	}
	return poped_item;
}

// if already empty, returns NULL
// get first element
struct list_head *q_get_first(struct q_head *q_head)
{
	struct list_head *got_item;
	if (NULL == q_head)
	{
		return (struct list_head *)NULL;
	}
	clogger_mutex_lock(q_head->mutex);
	if (clogger_list_empty(&q_head->lst_head))
	{
		clogger_mutex_unlock(q_head->mutex);
		return (struct list_head *)NULL;
	}
	got_item = q_head->lst_head.next;
	clogger_mutex_unlock(q_head->mutex);
	return got_item;
}
