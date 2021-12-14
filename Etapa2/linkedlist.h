#ifndef __LINKEDLIST_H_
#define __LINKEDLIST_H_

typedef struct __data data;
typedef struct __node_t node_t;
typedef struct __list_t list_t;

struct __data
{
	char
		pid[15],
		name[32],
		state[80],
		line[512],
		temp[512],
		vmSize[512],
		vmData[512],
		vmStk[512],
		vmExe[512],
		v_ctx_swt[512],
		nv_ctx_swt[512];
};

struct __node_t
{
	data datos;
	node_t *next;
};

struct __list_t
{
	node_t *head;
};

void list_init(list_t *l);
int list_nondup_end_insert(list_t *l, data ele);
int get_index(list_t *l, data ele);
int get_size(list_t *l);
void display(list_t *l);
#endif
