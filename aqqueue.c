#include <stdlib.h>
#include "aqqueue.h"

//Functions to manipulate the queue

//Initializa the queue
queue* queue_initialize()
{
    queue *q = (queue*) malloc(sizeof(queue));
    q->first = NULL;
    q->last = NULL;

    return q;
}

interval* interval_initialize(double left_limit, double right_limit, double f_left_limit, double f_right_limit, double area)
{
	interval *i = (interval*) malloc(sizeof(interval));
    i->left_limit = left_limit;
    i->right_limit = right_limit;
    i->f_left_limit = f_left_limit;
    i->f_right_limit = f_right_limit;
    i->area = area;
    i->next = NULL;

    return i;
}

//Put a new elemento into the queue
void emqueue(queue* q, interval* new_interval)
{
	//If the queue is empty
	if (q->first == NULL) {

		q->first = new_interval;
		q->last = new_interval;

	} else {

		q->last->next = new_interval;
		q->last = new_interval;
		q->last->next = NULL;
	}
}

//Get the next element of the queue
interval* dequeue(queue* q)
{
	interval *ret = NULL;

	//If the queue is NOT empty 
	if (q->first != NULL) {

		ret = q->first;
		q->first = q->first->next;
	}

	return ret;
}