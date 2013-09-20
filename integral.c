#include <stdio.h>
#include "adaquad.h"

int main()
{
	double (*targetFunction) (double);

    printf( "Begin: Functions test.\n" );

    double ret;

    targetFunction = &linearFunction;
    printf("%s%f\n", "Result for linear: ", targetFunction(10.1));

    targetFunction = &quadraticFunction;
    printf("%s%f\n", "Result for quadratic: ", targetFunction(10.1));

    targetFunction = &cubicFunction;
    printf("%s%f\n", "result for cubic: ", targetFunction(10.1));

    printf( "End: Functions test.\n" );

    return 0;
}