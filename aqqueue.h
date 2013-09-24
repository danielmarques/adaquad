#ifndef AQQ_H_GUARD
#define AQQ_H_GUARD

//Structs

//Elements of the queue
typedef struct _interval interval ;
struct _interval {
	double left_limit;
	double right_limit;
	double f_left_limit;
	double f_right_limit;
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

interval* interval_initialize(double left_limit, double right_limit, double f_left_limit, double f_right_limit, double area);

#endif