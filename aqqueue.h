#ifndef AQQ_H_GUARD
#define AQQ_H_GUARD

//Structs

//Elements of the queue
typedef struct _interval interval ;
struct _interval {
	double initial_point;
	double final_point;
	double area;
	interval *next;
};

//Control of the queue
typedef struct _queue {
	interval *first;
	interval *last;
} queue;

//Functions to manipulate the queue
void emqueue(queue* q, interval* new_interval);

interval* dequeue(queue* q);

queue* queue_initialize();

interval* interval_initialize(double initial_point, double final_point, double area);

#endif