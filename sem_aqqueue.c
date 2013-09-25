#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "aqqueue.h"
#include "sem_aqqueue.h"

//Functions to manipulate the queue

//Initialize the queue
sem_queue* sem_queue_initialize()
{
    sem_queue *q = (sem_queue*) malloc(sizeof(sem_queue));
    q->first = NULL;
    q->last = NULL;

    //Initialize the semafore that controls the queue's mutual exclusion
	sem_init(&q->semafore, 0, 1);

    return q;
}

//Put a new elemento into the queue
void sem_emqueue(sem_queue* q, interval* new_interval)
{	
	//Begin of mutual exclusion region
	sem_wait(&q->semafore);

	//If the queue is empty
	if (q->first == NULL) {

		q->first = new_interval;
		q->last = new_interval;

	} else {

		q->last->next = new_interval;
		q->last = new_interval;
		q->last->next = NULL;
	}

	sem_post(&q->semafore);
}

//Get the next element of the queue
interval* sem_dequeue(sem_queue* q)
{
	interval *ret = NULL;

	//Begin of mutual exclusion region
	sem_wait(&q->semafore);

	if (q->first != NULL)
	{
		ret = q->first;
		q->first = q->first->next;
	}

	sem_post(&q->semafore);

	return ret;
}