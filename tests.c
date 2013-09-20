#include <stdio.h>
#include "adaquad.h"

int main()
{
	double (*target_function) (double);

    printf( "\n" );
    printf( "Begin: Functions test.\n" );

    double ret;

    target_function = &linear_function;
    printf("%s%f\n", "Result for linear: ", target_function(10.1));

    target_function = &quadratic_function;
    printf("%s%f\n", "Result for quadratic: ", target_function(10.1));

    target_function = &cubic_function;
    printf("%s%f\n", "result for cubic: ", target_function(10.1));

    printf( "End: Functions test.\n" );
    printf( "\n" );
    printf( "Begin: Functions test.\n" );

    printf("%s%f\n", "Area: ", calc_trapezoid_area(1, 1, 1));

    printf( "End: Functions test.\n" );    

    printf( "\n" );
    return 0;
}