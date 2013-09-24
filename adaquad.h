#ifndef AQL_H_GUARD
#define AQL_H_GUARD

//Structs
typedef struct _static_worker_thread_arg {

	double left_limit;
	double right_limit;
	double tolerance;
	double (*calc_function) (double);

} static_worker_thread_arg;

//Functions to be the target of the integration operation
double linear_function(double x);

double quadratic_function(double x);

double cubic_function(double x);

//Function to calculate the area of a trapezoid
double calc_trapezoid_area(double base1, double base2, double height);

//Functions to parallelize the operations

//First Variant: each thread computes a subinterval for which will be responsible and calculates the result for this entire subinterval. When all threads have finished, the main thread should show the end result.

//ptheads implementation
void aq_static_administrator_sem_pthread(int num_threads, double left_limit, double right_limit, double tolerance, double (*calc_function) (double));

void* aq_static_worker_sem_pthread(void *arguments);

//openmp implemantation
void aq_static_administrator_sem_openmp(int num_threads, double left_limit, double right_limit, double tolerance, double (*calc_function) (double));

void* aq_static_worker_sem_openmp(void *arguments);

#endif