#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "adaquad.h"
#include "aqqueue.h"
#include "omp_adaquad.h"
#include "omp_aqqueue.h"

//Openmp implementation

//Global variables

queue *shared_result_queue, *shared_work_queue;

//Functions

//First Variant: each thread computes a subinterval for which will be responsible and calculates the result for this entire subinterval. When all threads have finished, the main thread should show the end result.

long double aq_static_administrator_omp(int num_threads, long double left_limit, long double right_limit, long double tolerance, long double (*calc_function) (long double))
{

	int i = 0;
	long double interval_length = 0, final_area = 0, t_left_limit = 0, t_right_limit = 0;
	interval *finished_interval = NULL;

	//Initialize the queue that will receve the results from the worker threads
	shared_result_queue = queue_initialize();

	//Calculates the length of the interval
	interval_length = (right_limit - left_limit) / num_threads;

	//Setting the number of threads
	omp_set_num_threads(num_threads);

	//Divide in a number of intervals equal to num_threads
	//Passes each interval to a thread (each thread will have an internal queue)
	#pragma omp parallel for private(t_left_limit, t_right_limit)
	for (i = 0; i < num_threads; ++i)
	{
		t_left_limit = left_limit + i*interval_length;
		t_right_limit = t_left_limit + interval_length;
		aq_static_worker_omp(t_left_limit, t_right_limit, tolerance, calc_function);
	}

	//Gets and consolidates the result
	finished_interval = dequeue(shared_result_queue);
	while(finished_interval != NULL) 
	{
		final_area = final_area + finished_interval->area;
		free(finished_interval);
		finished_interval = dequeue(shared_result_queue);
	}

	queue_finalize(shared_result_queue);
	return 	final_area;
}

void aq_static_worker_omp(long double left_limit, long double right_limit, long double tolerance, long double (*calc_function) (long double))
{
	//Auxiliary variables
	queue *work_queue = NULL;
	interval *work_interval = NULL, *temp_interval = NULL;
	long double f_mid_point = 0, f_left_limit = 0, f_right_limit = 0;
	long double big_area = 0 , left_area = 0, right_area = 0, mid_point = 0, areas_dif = 0, result_area = 0;	

	//Calculates the diference between the big area and the sum of the smaller areas
	mid_point = (right_limit + left_limit) / 2;
	f_left_limit = calc_function(left_limit);
	f_right_limit = calc_function(right_limit);
	f_mid_point = calc_function(mid_point);
	big_area = calc_trapezoid_area(f_left_limit, f_right_limit, right_limit - left_limit);	
	left_area = calc_trapezoid_area(f_left_limit, f_mid_point, mid_point - left_limit);	
	right_area = calc_trapezoid_area(f_mid_point, f_right_limit, right_limit - mid_point);
	areas_dif = big_area - (left_area + right_area);

	//If the difference is bellow the tolerance then store the result
	if (areas_dif <= tolerance)
	{	
		result_area = left_area + right_area;

	//Else divide the interval in two and send one to the thread work queue
	} else {

		work_queue = queue_initialize();

		//Put the one interval in the work queue
		temp_interval = interval_initialize(left_limit, mid_point, f_left_limit, f_mid_point, left_area);
        emqueue(work_queue, temp_interval);

        work_interval = interval_initialize(mid_point, right_limit, f_mid_point, f_right_limit, right_area);

        while (work_interval != NULL)
        {
        	//Calculates the diference between the big area and the sum of the smaller areas
			mid_point = (work_interval->right_limit + work_interval->left_limit) / 2;
			f_mid_point = calc_function(mid_point);
			left_area = calc_trapezoid_area(work_interval->f_left_limit, f_mid_point, mid_point - work_interval->left_limit);			
			right_area = calc_trapezoid_area(f_mid_point, work_interval->f_right_limit, work_interval->right_limit - mid_point);
			areas_dif = work_interval->area - (left_area + right_area);

			//If the difference is bellow the tolerance then store the result
			if (areas_dif < tolerance)
			{
				result_area = result_area + left_area + right_area;

			//Else divide the interval in two and send them to the thread work queue
			} else {

				temp_interval = interval_initialize(work_interval->left_limit, mid_point, work_interval->f_left_limit, f_mid_point, left_area);
		        emqueue(work_queue, temp_interval);
		        temp_interval = interval_initialize(mid_point, work_interval->right_limit, f_mid_point, work_interval->f_right_limit, right_area);
		        emqueue(work_queue, temp_interval);
			}

			free(work_interval);
			work_interval = dequeue(work_queue);
        }

        queue_finalize(work_queue);
	}

	//Send the result to the results queue (to be retreved by the administrator thread)
	temp_interval = interval_initialize(0, 0, 0, 0, result_area);
	omp_emqueue(shared_result_queue, temp_interval);
}

//Second Variant: the threads get the intervals form a shared work queue. When new tasks are generated the threads put thme in this shared work queue.

long double aq_dynamic_administrator_omp(int num_init_tasks, int num_threads, long double left_limit, long double right_limit, long double tolerance, long double (*calc_function) (long double))
{
	//Auxiliary variables
	int i = 0;
	long double interval_length = 0L, f_left_limit = 0L, f_right_limit = 0L, i_left_limit = 0L, i_right_limit = 0L, interval_area = 0L, final_area = 0L;
	interval *finished_interval = NULL, *temp_interval = NULL;

	//Calculates the length of the initial intervals
	interval_length = (right_limit - left_limit) / num_init_tasks;

	//Divide in a number of initial intervals equal to num_tasks and initiate the work queue with them
	shared_work_queue = queue_initialize();
	for (i = 0; i < num_init_tasks; ++i)
	{
		i_left_limit = left_limit + i*interval_length;
		i_right_limit = i_left_limit + interval_length;
		f_left_limit = calc_function(i_left_limit);
		f_right_limit = calc_function(i_right_limit);
		interval_area = calc_trapezoid_area(f_left_limit, f_right_limit, interval_length);
		temp_interval = interval_initialize(i_left_limit, i_right_limit, f_left_limit, f_right_limit, interval_area);
        emqueue(shared_work_queue, temp_interval);        
	}

	//Initialize the queue that will receve the results from the worker threads
	shared_result_queue = queue_initialize();

	//Setting the number of threads
	omp_set_num_threads(num_threads);

	//Start the work threads
	#pragma omp parallel for
	for (i = 0; i < num_threads; ++i)
	{
		aq_dynamic_worker_omp(tolerance, calc_function);
	}

	//Gets and consolidates the result
	finished_interval = dequeue(shared_result_queue);
	while(finished_interval != NULL)
	{
		final_area = final_area + finished_interval->area;
		free(finished_interval);
		finished_interval = dequeue(shared_result_queue);
	}

	queue_finalize(shared_work_queue);
	queue_finalize(shared_result_queue);
	return final_area;
}

void aq_dynamic_worker_omp(long double tolerance, long double (*calc_function) (long double))
{
	//Auxiliary variables
	interval *work_interval = NULL, *temp_interval = NULL;
	long double left_area = 0L, right_area = 0L, areas_dif = 0L, mid_point = 0L, f_mid_point = 0L;	

	work_interval = omp_dequeue(shared_work_queue);
    while (work_interval != NULL)
    {
    	//Calculates the diference between the big area and the sum of the smaller areas
		mid_point = (work_interval->right_limit + work_interval->left_limit) / 2;
		f_mid_point = calc_function(mid_point);
		left_area = calc_trapezoid_area(work_interval->f_left_limit, f_mid_point, mid_point - work_interval->left_limit);			
		right_area = calc_trapezoid_area(f_mid_point, work_interval->f_right_limit, work_interval->right_limit - mid_point);
		areas_dif = work_interval->area - (left_area + right_area);

		//If the difference is bellow the tolerance then store the result
		if (areas_dif <= tolerance)
		{
			//Send the result to the results queue (to be retreved by the administrator thread)
			temp_interval = interval_initialize(work_interval->left_limit, work_interval->right_limit, 0, 0, left_area + right_area);
			omp_emqueue(shared_result_queue, temp_interval);

		//Else divide the interval in two and send them to the thread work queue
		} else {

			temp_interval = interval_initialize(work_interval->left_limit, mid_point, work_interval->f_left_limit, f_mid_point, left_area);
	        omp_emqueue(shared_work_queue, temp_interval);
	        temp_interval = interval_initialize(mid_point, work_interval->right_limit, f_mid_point, work_interval->f_right_limit, right_area);
	        omp_emqueue(shared_work_queue, temp_interval);
		}

		free(work_interval);
		//Try to get a new work interval
		work_interval = omp_dequeue(shared_work_queue);
    }
}

