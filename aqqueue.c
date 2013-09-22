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

interval* interval_initialize(double initial_point, double final_point, double area)
{
	interval *i = (interval*) malloc(sizeof(interval));
    i->initial_point = initial_point;
    i->final_point = final_point;
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
	interval *ret;

	//If the queue is NOT empty 
	if (q->first != NULL) {

		ret = q->first;
		q->first = q->first->next;
		return ret;
	}

	return NULL;
}