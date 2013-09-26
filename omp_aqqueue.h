#ifndef OMPAQQ_H_GUARD
#define OMPAQQ_H_GUARD

//Functions to manipulate the queue
void omp_emqueue(queue* q, interval* new_interval);

interval* omp_dequeue(queue* q);

#endif