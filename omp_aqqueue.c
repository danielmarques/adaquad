#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "aqqueue.h"
#include "omp_aqqueue.h"

//Functions to manipulate the queue

//Put a new elemento into the queue
void omp_emqueue(queue* q, interval* new_interval)
{	
	//Begin of mutual exclusion region
	#pragma omp critical
	{
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
	}
}

//Get the next element of the queue
interval* omp_dequeue(queue* q)
{
	interval *ret = NULL;

	//Begin of mutual exclusion region
	#pragma omp critical
	{
		if (q->first != NULL)
		{
			ret = q->first;
			q->first = q->first->next;

			if (q->first == NULL)
			{
				q->last = NULL;
			}
		}
	}

	return ret;
}