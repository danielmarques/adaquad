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
int aq_static_administrator_pthread(int num_tasks, double left_limit, double right_limit, void *function)
{

	//divide em tantos subintervalos quanto for o numero de threads (num_tasks)

	//repassa cada subintervalo para uma thread (cada thread vai ter um fila dela internamente)

	//recupera o resultado final e consolida (fila de resultados igual a da outra versão)
	return 0;
}

int aq_static_worker_pthread()
{
	//calcula a diferenca entre a area maior e as duas menores
	//se estiver abaixo da tolerancia manda para fila de resultados
	//se não divide em subtarefas e manda para sua propria fila de tarefas
	return 0;
}

//openmp implementation
int aq_static_administrator_openmp(int num_tasks, double left_limit, double right_limit, void *function)
{
	return 0;
}

int aq_static_worker_openmp()
{
	return 0;
}
