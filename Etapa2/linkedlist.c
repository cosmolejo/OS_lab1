#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

void list_init(list_t *l)
{
	l->head = NULL;
}

/*
This function realize the insert of an element on a list of type list_t
list_t is a list of elements of type node_t
A node consist of an atirbute char* and a pointer to another node_t element

If you try to insert an element already present in the list, so the element is nos inserted and the function return -1
When an element is inserted the function return the number of elements of the list
*/
int list_nondup_end_insert(list_t *list, data ele)
{
	
	node_t *tmp, *tmp1, *tmp2;
	tmp = list->head;
	int count = 0;
	if (tmp == NULL)
	{
		tmp1 = (node_t *)malloc(sizeof(node_t));
		tmp1->datos = ele;
		tmp1->next = NULL;
		list->head = tmp1;
		count++;
		return count;
	}
	else
	{
		do
		{
			tmp2 = tmp;
			if (strcmp(tmp->datos.pid, ele.pid) == 0)
			{
				return -1;
			}
			count++;
			tmp = tmp->next;
		} while (tmp != NULL);
		tmp1 = (node_t *)malloc(sizeof(node_t));
		tmp1->datos = ele;
		tmp1->next = NULL;
		tmp2->next = tmp1;
		count++;
	}
	return count;
}

/*
This function return the index of the element ele in the list
If the element is nos present the function return -1
*/
int get_index(list_t *list, data ele)
{
	node_t *tmp, *tmp1;
	tmp = list->head;
	int index = 0;
	do
	{
		if (strcmp(tmp->datos.pid, ele.pid) == 0)
		{
			return index;
		}
		index++;
		tmp = tmp->next;
	} while (tmp != NULL);
	return -1;
}

/*
This function return the size of list
*/
int get_size(list_t *list)
{
	node_t *tmp;
	tmp = list->head;
	int size = 0;
	while (tmp != NULL)
	{
		size++;
		tmp = tmp->next;
	}
	return size;
}

/*
This function simply print the elements of the list
*/
void display(list_t *list)
{
	node_t *tmp;
	tmp = list->head;
	while (tmp != NULL)
	{
		printf("PID: %s\n", tmp->datos.pid);
        printf("Nombre del proceso: %s\n", tmp->datos.name); // Finalmente se imprime la información extraída del archivo
        printf("Estado: %s\n", tmp->datos.state);
        printf("Tamaño total de la imagen de memoria: %s\n", tmp->datos.vmSize);
        printf("\tTamaño de la memoria de la región TEXT:  %s\n", tmp->datos.vmData);
        printf("\tTamaño de la memoria de la región DATA: %s\n", tmp->datos.vmStk);
        printf("\tTamaño de la memoria de la región STACK: %s\n", tmp->datos.vmExe);
        printf("Número de cambios de contexto realizados (voluntarios - no voluntarios): %s - %s\n",
               tmp->datos.v_ctx_swt, tmp->datos.nv_ctx_swt);
		tmp = tmp->next;
	}
}
