#include "adaquad.h"

//Functions

//Functions to be the target of the integration operation
long double linear_function(long double x)
{
	long double parameter1 = 4;
	long double parameter0 = 2;

	return parameter1*x + parameter0;	
}

long double quadratic_function(long double x)
{
	long double parameter2 = 8;
	long double parameter1 = 4;
	long double parameter0 = 2;

	return parameter2*x*x + parameter1*x + parameter0;
}

long double cubic_function(long double x)
{
	long double parameter3 = 16;
	long double parameter2 = 8;
	long double parameter1 = 4;
	long double parameter0 = 2;

	return parameter3*x*x*x + parameter2*x*x + parameter1*x + parameter0;
}

//Function to calculate the area of a trapezoid
long double calc_trapezoid_area(long double base1, long double base2, long double height)
{

	return ((base1 + base2)*height) / 2;
}
