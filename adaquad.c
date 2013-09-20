#include <stdio.h>
#include "adaquad.h"


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

double calc_trapezoid_area(double base1, double base2, double height)
{
	return ((base1 + base2)*height) / 2;
}