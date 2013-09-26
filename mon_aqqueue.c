#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "aqqueue.h"
#include "mon_aqqueue.h"

//Functions to manipulate the queue

//Initialize the queue
mon_queue* mon_queue_initialize()
{
    mon_queue *q = (mon_queue*) malloc(sizeof(mon_queue));
    q->first = NULL;
    q->last = NULL;

    if(pthread_mutex_init(&(q->mutex), NULL) != 0) {

    	perror("pthread_mutex_init");
    	exit(1);
   	}
    if(pthread_cond_init(&(q->condition), NULL) != 0) {

		perror("pthread_cond_init");
		exit(1);
    }

    return q;
}

void mon_queue_finalize(mon_queue* q)
{
	interval *ret = NULL;

	if (q != NULL)
	{
		pthread_mutex_destroy(&(q->mutex));
		pthread_cond_destroy(&(q->condition));

		while (q->first != NULL)
		{
			ret = q->first;
			q->first = q->first->next;			

			if (q->first == NULL)
			{
				q->last = NULL;
			}

			free(ret);
		}

		free(q);
	}
}

//Put a new elemento into the queue
void mon_emqueue(mon_queue* q, interval* new_interval)
{	
	//Begin of mutual exclusion region
	pthread_mutex_lock(&(q->mutex));

	//If the queue is empty
	if (q->first == NULL) {

		q->first = new_interval;
		q->last = new_interval;
		q->last->next = NULL;

	} else {

		q->last->next = new_interval;
		q->last = new_interval;
		q->last->next = NULL;
	}

	pthread_cond_signal(&(q->condition));
	pthread_mutex_unlock(&(q->mutex));
}

//Get the next element of the queue
interval* mon_dequeue(mon_queue* q)
{
	interval *ret = NULL;

	//Begin os monitor region
	pthread_mutex_lock(&(q->mutex));
	//while (q->first == NULL) {pthread_cond_wait(&(q->condition), &(q->mutex));}

	if (q->first != NULL)
	{
		ret = q->first;
		q->first = q->first->next;

		if (q->first == NULL)
		{
			q->last = NULL;
		}
	}
	
	pthread_mutex_unlock(&(q->mutex));

	return ret;
}