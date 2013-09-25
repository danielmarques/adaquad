#ifndef SAQQ_H_GUARD
#define SAQQ_H_GUARD

//Structs

//Control of the queue
typedef struct _sem_queue {
	interval *first;
	interval *last;
	sem_t semafore;
} sem_queue;

//Functions to manipulate the queue
void sem_emqueue(sem_queue* q, interval* new_interval);

interval* sem_dequeue(sem_queue* q);

sem_queue* sem_queue_initialize();

#endif