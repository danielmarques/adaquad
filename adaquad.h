#ifndef AQL_H_GUARD
#define AQL_H_GUARD

//Structs
typedef struct _static_worker_thread_arg {

	long double left_limit;
	long double right_limit;
	long double tolerance;
	long double (*calc_function) (long double);

} static_worker_thread_arg;

typedef struct _dynamic_worker_thread_arg {

	long double tolerance;
	long double (*calc_function) (long double);

} dynamic_worker_thread_arg;

//Functions to be the target of the integration operation
long double linear_function(long double x);

long double quadratic_function(long double x);

long double cubic_function(long double x);

//Function to calculate the area of a trapezoid
long double calc_trapezoid_area(long double base1, long double base2, long double height);

#endif