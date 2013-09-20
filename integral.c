#include <stdio.h>
#include "adaquad.h"

int main()
{
	double (*target_function) (double);
	target_function = &linear_function;

    return 0;
}