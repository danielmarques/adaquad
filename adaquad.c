#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "adaquad.h"
#include "aqqueue.h"

//Global variables

queue *shared_result_queue;
double *shared_test = NULL;
int all_threads_ended = 0;

//Functions

//Functions to be the target of the integration operation
double linear_function(double x)
{
	double parameter1 = 4;
	double parameter0 = 2;

	return parameter1*x + parameter0;	
}

double quadratic_function(double x)
{
	double parameter2 = 8;
	double parameter1 = 4;
	double parameter0 = 2;

	return parameter2*x*x + parameter1*x + parameter0;
}

double cubic_function(double x)
{
	double parameter3 = 16;
	double parameter2 = 8;
	double parameter1 = 4;
	double parameter0 = 2;

	return parameter3*x*x*x + parameter2*x*x + parameter1*x + parameter0;
}

//Function to calculate the area of a trapezoid
double calc_trapezoid_area(double base1, double base2, double height)
{
	return ((base1 + base2)*height) / 2;
}

//Functions to parallelize the operations

//First Variant: each thread computes a subinterval for which will be responsible and calculates the result for this entire subinterval. When all threads have finished, the main thread should show the end result.

//Ptheads implementation
void aq_static_administrator_sem_pthread(int num_threads, double left_limit, double right_limit, double tolerance, double (*calc_function) (double))
{

	int i = 0;
	double interval_length = 0;
	static_worker_thread_arg *arguments = NULL;
	pthread_t threads[num_threads];

	//Initialize the queue that will receve the results from the worker threads
	shared_result_queue = queue_initialize();

	//Calculates the length of the interval
	interval_length = (right_limit - left_limit) / num_threads;

	//Divide in a number of intervals equal to num_threads
	//Passes each interval toa a thread (each thread will have an internal queue)
	for (i = 0; i < num_threads; ++i)
	{
		arguments = (static_worker_thread_arg*) malloc(sizeof(static_worker_thread_arg));
		arguments->left_limit = left_limit + i*interval_length;
		arguments->right_limit = arguments->left_limit + interval_length;
		arguments->tolerance = tolerance;
		arguments->calc_function = calc_function;

		pthread_create(&threads[i], NULL, aq_static_worker_sem_pthread, (void*) arguments);
	}

	//Gets and consilidates the result
	while(1) {
		if (all_threads_ended == num_threads) {
			printf("Terminaram.\n");
			return;
		}
	}	
}

void* aq_static_worker_sem_pthread(void *arguments)
{ 
	//shared_test = (double*) malloc(sizeof(double));	
	//Cast the arguments to the correct type
	static_worker_thread_arg *t_arguments = (static_worker_thread_arg*) arguments;

	//Auxiliary variables
	queue *work_queue = NULL;
	interval *work_interval = NULL, *temp_interval = NULL;
	double f_mid_point = 0, f_left_limit = 0, f_right_limit = 0;
	double big_area = 0 , left_area = 0, right_area = 0, mid_point = 0, areas_dif = 0, result_area = 0;	

	//Calculates the diference between the big area and the sum of the smaller areas

	mid_point = (t_arguments->right_limit + t_arguments->left_limit) / 2;
	f_left_limit = t_arguments->calc_function(t_arguments->left_limit);
	f_right_limit = t_arguments->calc_function(t_arguments->right_limit);
	f_mid_point = t_arguments->calc_function(mid_point);

	big_area = calc_trapezoid_area(f_left_limit, f_right_limit, t_arguments->right_limit - t_arguments->left_limit);
	
	left_area = calc_trapezoid_area(f_left_limit, f_mid_point, mid_point - t_arguments->left_limit);
	
	right_area = calc_trapezoid_area(f_mid_point, f_right_limit, t_arguments->right_limit - mid_point);

	areas_dif = big_area - (left_area + right_area);

	//If the difference is bellow the tolerance then store the result
	if (areas_dif < t_arguments->tolerance)
	{	
		result_area = left_area + right_area;

	//Else divide the interval in two and send one to the thread work queue
	} else {

		work_queue = queue_initialize();

		//Put the one interval in the work queue
		temp_interval = interval_initialize(t_arguments->left_limit, mid_point, f_left_limit, f_mid_point, left_area);
        emqueue(work_queue, temp_interval);

        work_interval = interval_initialize(mid_point, t_arguments->right_limit, f_mid_point, f_right_limit, right_area);

        while (work_interval != NULL)
        {
        	//Calculates the diference between the big area and the sum of the smaller areas
			mid_point = (work_interval->right_limit + work_interval->left_limit) / 2;
			f_mid_point = t_arguments->calc_function(mid_point);
			left_area = calc_trapezoid_area(work_interval->f_left_limit, f_mid_point, mid_point - work_interval->left_limit);			
			right_area = calc_trapezoid_area(f_mid_point, work_interval->f_right_limit, work_interval->right_limit - mid_point);
			areas_dif = work_interval->area - (left_area + right_area);

			//If the difference is bellow the tolerance then store the result
			if (areas_dif < t_arguments->tolerance)
			{
				result_area = result_area + left_area + right_area;

			//Else divide the interval in two and send them to the thread work queue
			} else {

				temp_interval = interval_initialize(work_interval->left_limit, mid_point, work_interval->f_left_limit, f_mid_point, left_area);
		        emqueue(work_queue, temp_interval);
		        temp_interval = interval_initialize(mid_point, work_interval->right_limit, f_mid_point, work_interval->f_right_limit, right_area);
		        emqueue(work_queue, temp_interval);
			}

			printf("%f\n", areas_dif);
			work_interval = dequeue(work_queue);
        }
	}
	
	printf("Area: %f", result_area);
	all_threads_ended = all_threads_ended + 1;
	return NULL;
}

//Openmp implementation
void aq_static_administrator_sem_openmp(int num_tasks, double left_limit, double right_limit, double tolerance, double (*calc_function) (double))
{

}

void* aq_static_worker_sem_openmp(void *arguments)
{
	return NULL;
}
