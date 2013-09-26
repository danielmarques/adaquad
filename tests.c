#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mon_adaquad.h"
#include "sem_adaquad.h"
#include "omp_adaquad.h"
#include "adaquad.h"

#define TOLERANCE 1e-20
#define NUM_THREADS 8
#define NUM_TASKS 10

int main()
{
    long double ret = 0.0L;
    clock_t begin, end;
    double time_spent;

 // double (*target_function) (double);

 //    printf( "\n" );
 //    printf( "Begin: Functions test.\n" );

 //    double ret;

 //    target_function = &linear_function;
 //    printf("%s%f\n", "Result for linear: ", target_function(10.1));

 //    target_function = &quadratic_function;
 //    printf("%s%f\n", "Result for quadratic: ", target_function(10.1));

 //    target_function = &cubic_function;
 //    printf("%s%f\n", "result for cubic: ", target_function(10.1));

 //    printf( "End: Functions test.\n" );
 //    printf( "\n" );
 //    printf( "Begin: Functions test.\n" );

 //    printf("%s%f\n", "Area: ", calc_trapezoid_area(1, 1, 1));

 //    printf( "End: Functions test.\n" );    

 //    printf( "\n" );

    // int k = 0;
    // queue *q = NULL;
    // interval *i = NULL;
    
    // printf( "Begin: Queue test.\n" );
    
    // q = queue_initialize();

    // for (k = 1; k <= 10; ++k)
    // {
 
    //     i = interval_initialize(k, k+1, 0);
    //     printf("Intervalo %i: %f-%f\n", k, i->initial_point, i->final_point);

    //     emqueue(q, i);

    //     printf("Fila %i: %f-%f\n", k, q->first->initial_point, q->last->final_point);
    // }

    // printf("#################################\n");

    // for (k = 1; k <= 11; ++k)
    // {
 
    //     i = dequeue(q);

    //     if (i == NULL) {

    //         printf("Fila %i: vazia\n", k);

    //     } else {

    //         printf("Intervalo %i: %f-%f\n", k, i->initial_point, i->final_point);
    //         if (q->first != NULL) {

    //             printf("Fila %i: %f-%f\n", k, q->first->initial_point, q->last->final_point);
    //         } else {

    //             printf("Fila %i: vazia\n", k);
    //         }           
    //     }
    // }

    // printf( "End: Queue test.\n" );
    // printf( "\n" );

    // printf("Static: \n");
    // ret = aq_static_administrator_sem_pthread(NUM_THREADS, -0.1, 0, TOLERANCE, &quadratic_function);
    // printf("Integral: %Le\n", ret);

    // printf("Dynamic: \n");
    // ret = aq_dynamic_administrator_sem_pthread(NUM_TASKS, NUM_THREADS, -0.1, 0, TOLERANCE, &quadratic_function);
    // printf("Integral: %Le\n", ret);


    // printf("Static: \n");
    // ret = aq_static_administrator_mon_pthread(NUM_THREADS, -0.1, 0, TOLERANCE, &quadratic_function);
    // printf("Integral: %Le\n", ret);

    // printf("Dynamic: \n");
    // ret = aq_dynamic_administrator_mon_pthread(NUM_TASKS, NUM_THREADS, -0.1, 0, TOLERANCE, &quadratic_function);
    // printf("Integral: %Le\n", ret);

    printf("Static: \n");
    begin = clock();
    ret = aq_static_administrator_omp(NUM_THREADS, 0, 1, TOLERANCE, &cubic_function);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Integral value: %Le\n", ret);
    printf("Time spent: %f seconds\n", time_spent);

    printf("Dynamic: \n");
    begin = clock();
    ret = aq_dynamic_administrator_omp(NUM_TASKS, NUM_THREADS, 0, 1, TOLERANCE, &cubic_function);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Integral value: %Le\n", ret);
    printf("Time spent: %f\n seconds", time_spent);

    return 0;
}