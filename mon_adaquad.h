#ifndef MAQL_H_GUARD
#define MAQL_H_GUARD

//Ptheads with monitors

//First Variant: each thread computes a subinterval for which will be responsible and calculates the result for this entire subinterval. When all threads have finished, the main thread should show the end result.
long double aq_static_administrator_mon_pthread(int num_threads, long double left_limit, long double right_limit, long double tolerance, long double (*calc_function) (long double));

void* aq_static_worker_mon_pthread(void *arguments);

//Second Variant: the threads get the intervals form a shared work queue. When new tasks are generated the threads put thme in this shared work queue.
long double aq_dynamic_administrator_mon_pthread(int num_init_tasks, int num_threads, long double left_limit, long double right_limit, long double tolerance, long double (*calc_function) (long double));

void* aq_dynamic_worker_mon_pthread(void *arguments);

#endif