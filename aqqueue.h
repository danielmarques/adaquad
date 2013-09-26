#ifndef AQQ_H_GUARD
#define AQQ_H_GUARD

//Structs

//Elements of the queue
typedef struct _interval interval ;
struct _interval {
	long double left_limit;
	long double right_limit;
	long double f_left_limit;
	long double f_right_limit;
	long double area;
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

void queue_finalize(queue *q);

interval* interval_initialize(long double left_limit, long double right_limit, long double f_left_limit, long double f_right_limit, long double area);

#endif