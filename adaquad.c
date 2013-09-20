#include <stdio.h>
#include "adaquad.h"


double linearFunction(double x)
{
	double parameter1 = 4;
	double parameter0 = 2;

	return parameter1*x + parameter0;	
}

double quadraticFunction(double x)
{
	double parameter2 = 8;
	double parameter1 = 4;
	double parameter0 = 2;

	return parameter2*x*x + parameter1*x + parameter0;
}

double cubicFunction(double x)
{
	double parameter3 = 16;
	double parameter2 = 8;
	double parameter1 = 4;
	double parameter0 = 2;

	return parameter3*x*x*x + parameter2*x*x + parameter1*x + parameter0;
}