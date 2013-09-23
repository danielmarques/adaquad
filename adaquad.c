#include <stdlib.h>
#include <pthread.h>
#include "adaquad.h"

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

//ptheads implementation
void aq_static_administrator_sem_pthread(int num_threads, double left_limit, double right_limit, void *function)
{

	int i = 0;
	double interval_length = 0;
	static_worker_sem_thread_arg *arguments = NULL;
	pthread_t threads[num_threads];

	//Calculates the length of the interval
	interval_length = (right_limit - left_limit) / num_threads;

	//Divide in a number of intervals equal to num_threads
	for (i = 0; i < num_threads; ++i)
	{
		arguments = (static_worker_sem_thread_arg*) malloc(sizeof(static_worker_sem_thread_arg));
		arguments->left_limit = left_limit + i*interval_length;
		arguments->right_limit = arguments->left_limit + interval_length;
		arguments->function = function;

		pthread_create(&threads[i], NULL, aq_static_worker_sem_pthread, (void*) arguments);

	}

	//Repassa cada subintervalo para uma thread (cada thread vai ter um fila dela internamente)

	//recupera o resultado final e consolida (fila de resultados igual a da outra versão)
}

void* aq_static_worker_sem_pthread(void *arguments)
{
	//calcula a diferenca entre a area maior e as duas menores
	//se estiver abaixo da tolerancia manda para fila de resultados
	//se não divide em subtarefas e manda para sua propria fila de tarefas
	return NULL;
}

//openmp implementation
void aq_static_administrator_sem_openmp(int num_tasks, double left_limit, double right_limit, void *function)
{

}

void* aq_static_worker_sem_openmp(void *arguments)
{
	return NULL;
}
