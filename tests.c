#include <stdio.h>
#include <stdlib.h>
#include "adaquad.h"
#include "aqqueue.h"

#define TOLERANCE 1e-20
#define NUM_THREADS 10

int main()
{
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

    aq_static_administrator_sem_pthread(NUM_THREADS, 0, 1, TOLERANCE, &quadratic_function);

    return 0;
}