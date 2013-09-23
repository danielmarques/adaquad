#include <stdio.h>
#include "adaquad.h"

#define NUMTHREADS 10;

int main()
{
	double (*target_function) (double);
	target_function = &linear_function;

    return 0;
}