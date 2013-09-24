#include <stdio.h>
#include "adaquad.h"

#define NUMTHREADS 10;

int main()
{
	long double (*target_function) (long double);
	target_function = &linear_function;

    return 0;
}