#ifndef MAQQ_H_GUARD
#define MAQQ_H_GUARD

//Structs

//Control of the queue
typedef struct _mon_queue {
	interval *first;
	interval *last;
	pthread_mutex_t mutex;
   	pthread_cond_t condition;
} mon_queue;

//Functions to manipulate the queue
void mon_emqueue(mon_queue* q, interval* new_interval);

interval* mon_dequeue(mon_queue* q);

mon_queue* mon_queue_initialize();

#endif