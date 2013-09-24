#ifndef AQL_H_GUARD
#define AQL_H_GUARD

//Structs
typedef struct _static_worker_thread_arg {

	long double left_limit;
	long double right_limit;
	long double tolerance;
	long double (*calc_function) (long double);

} static_worker_thread_arg;

//Functions to be the target of the integration operation
long double linear_function(long double x);

long double quadratic_function(long double x);

long double cubic_function(long double x);

//Function to calculate the area of a trapezoid
long double calc_trapezoid_area(long double base1, long double base2, long double height);

//Functions to parallelize the operations

//First Variant: each thread computes a subinterval for which will be responsible and calculates the result for this entire subinterval. When all threads have finished, the main thread should show the end result.

//ptheads implementation
void aq_static_administrator_sem_pthread(int num_threads, long double left_limit, long double right_limit, long double tolerance, long double (*calc_function) (long double));

void* aq_static_worker_sem_pthread(void *arguments);

//openmp implemantation
void aq_static_administrator_sem_openmp(int num_threads, long double left_limit, long double right_limit, long double tolerance, long double (*calc_function) (long double));

void* aq_static_worker_sem_openmp(void *arguments);

#endif