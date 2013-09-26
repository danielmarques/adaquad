#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "mon_adaquad.h"
#include "sem_adaquad.h"
#include "omp_adaquad.h"
#include "adaquad.h"

#define NELEMS(x)  (sizeof(x) / sizeof(x[0]))
#define NUM_TASKS 10
#define LEFT_LIMIT 0
#define RIGHT_LIMIT 0.1

int main(int argc, char **argv)
{
    long double ret = 0.0L, left_limit = (long double) LEFT_LIMIT, right_limit = (long double) RIGHT_LIMIT;
    clock_t begin, end;
    double time_spent = 0.0, mean_time_spent = 0.0;
    int static_variant = 0, dynamic_variant = 0, semafores_imp = 0, monitors_imp = 0, openmp_imp = 0, i = 0, ft =0, nt = 0, to = 0, c;
    char *function_name[] = {"Quadratic", "Cubic"};
    long double (*calc_function[]) (long double) = {&quadratic_function, &cubic_function};
    long double tolerance[] = {(long double) 1e-10, (long double) 1e-15, (long double) 1e-20};
    int num_threads[] = {2, 4, 8};

    opterr = 0;
    while ((c = getopt (argc, argv, "smotd")) != -1)
    {
        switch (c)
        {
            case 's':
                semafores_imp = 1;
             break;
            case 'm':
                monitors_imp = 1;
             break;
            case 'o':
                openmp_imp = 1;
             break;
            case 't':
                static_variant = 1;
             break;
            case 'd':
                dynamic_variant = 1;
             break;
            case '?':
             if (isprint (optopt))
               fprintf (stderr, "Unknown option `-%c'.\n", optopt);
             else
               fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
             return 1;
           default:
             abort();
        }
    }

    for (i = optind; i < argc; i++)
     printf ("Non-option argument %s\n", argv[i]);

    printf("\n");

    if (semafores_imp && static_variant) //Pthreads with semafores
    {
        printf("Variant Tolerance Num_Threads Function Result Mean_Time_Spent\n");

        for (to = 0; to < NELEMS(tolerance); ++to)
        {
            for (ft = 0; ft < NELEMS(calc_function); ++ft)
            {
                for (nt = 0; nt < NELEMS(num_threads); ++nt)
                {
                    time_spent = 0.0;
                    mean_time_spent = 0.0;
                    for (i = 0; i < 10; ++i)
                    {
                        begin = clock();
                        ret = aq_static_administrator_sem_pthread(num_threads[nt], left_limit, right_limit, tolerance[to], calc_function[ft]);
                        end = clock();
                        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
                        mean_time_spent = mean_time_spent + time_spent / 10.0;
                    }    
                    printf("SEM_STA %Le %i %s %Le %f\n", tolerance[to], num_threads[nt], function_name[ft], ret, mean_time_spent);
                }
            }
        }
    }
    else if (semafores_imp && dynamic_variant) //Pthreads with semafores
    {
        printf("Variant Tolerance Num_Threads Function Result Mean_Time_Spent\n");

        for (to = 0; to < NELEMS(tolerance); ++to)
        {
            for (ft = 0; ft < NELEMS(calc_function); ++ft)
            {
                for (nt = 0; nt < NELEMS(num_threads); ++nt)
                {
                    time_spent = 0.0;
                    mean_time_spent = 0.0;
                    for (i = 0; i < 10; ++i)
                    {
                        begin = clock();
                        ret = aq_dynamic_administrator_sem_pthread(NUM_TASKS, num_threads[nt], left_limit, right_limit, tolerance[to], calc_function[ft]);
                        end = clock();
                        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
                        mean_time_spent = mean_time_spent + time_spent / 10.0;
                    }    
                    printf("SEM_DYN %Le %i %s %Le %f\n", tolerance[to], num_threads[nt], function_name[ft], ret, mean_time_spent);
                }
            }
        }
    }
    else if (monitors_imp && static_variant) // Pthreads with monitors
    {
        printf("Variant Tolerance Num_Threads Function Result Mean_Time_Spent\n");

        for (to = 0; to < NELEMS(tolerance); ++to)
        {
            for (ft = 0; ft < NELEMS(calc_function); ++ft)
            {
                for (nt = 0; nt < NELEMS(num_threads); ++nt)
                {
                    time_spent = 0.0;
                    mean_time_spent = 0.0;
                    for (i = 0; i < 10; ++i)
                    {
                        begin = clock();
                        ret = aq_static_administrator_mon_pthread(num_threads[nt], left_limit, right_limit, tolerance[to], calc_function[ft]);
                        end = clock();
                        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
                        mean_time_spent = mean_time_spent + time_spent / 10.0;
                    }    
                    printf("MON_STA %Le %i %s %Le %f\n", tolerance[to], num_threads[nt], function_name[ft], ret, mean_time_spent);
                }
            }
        }
    }
    else if (monitors_imp && dynamic_variant) // Pthreads with monitors
    {
        printf("Variant Tolerance Num_Threads Function Result Mean_Time_Spent\n");

        for (to = 0; to < NELEMS(tolerance); ++to)
        {
            for (ft = 0; ft < NELEMS(calc_function); ++ft)
            {
                for (nt = 0; nt < NELEMS(num_threads); ++nt)
                {
                   time_spent = 0.0;
                    mean_time_spent = 0.0;
                    for (i = 0; i < 10; ++i)
                    {
                        begin = clock();
                        ret = aq_dynamic_administrator_mon_pthread(NUM_TASKS, num_threads[nt], left_limit, right_limit, tolerance[to], calc_function[ft]);
                        end = clock();
                        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
                        mean_time_spent = mean_time_spent + time_spent / 10.0;
                    }    
                    printf("MON_DYN %Le %i %s %Le %f\n", tolerance[to], num_threads[nt], function_name[ft], ret, mean_time_spent);
                }
            }
        }
    }
    else if (openmp_imp && static_variant) //Openmp
    {
        printf("Variant Tolerance Num_Threads Function Result Mean_Time_Spent\n");

        for (to = 0; to < NELEMS(tolerance); ++to)
        {
            for (ft = 0; ft < NELEMS(calc_function); ++ft)
            {
                for (nt = 0; nt < NELEMS(num_threads); ++nt)
                {
                    time_spent = 0.0;
                    mean_time_spent = 0.0;
                    for (i = 0; i < 10; ++i)
                    {
                        begin = clock();
                        ret = aq_static_administrator_omp(num_threads[nt], left_limit, right_limit, tolerance[to], calc_function[ft]);
                        end = clock();
                        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
                        mean_time_spent = mean_time_spent + time_spent / 10.0;
                    }    
                    printf("OMP_STA %Le %i %s %Le %f\n", tolerance[to], num_threads[nt], function_name[ft], ret, mean_time_spent);
                }
            }
        }

    }
    else if (openmp_imp && dynamic_variant) //Openmp
    {
        printf("Variant Tolerance Num_Threads Function Result Mean_Time_Spent\n");

        for (to = 0; to < NELEMS(tolerance); ++to)
        {
            for (ft = 0; ft < NELEMS(calc_function); ++ft)
            {
                for (nt = 0; nt < NELEMS(num_threads); ++nt)
                {
                    time_spent = 0.0;
                    mean_time_spent = 0.0;
                    for (i = 0; i < 10; ++i)
                    {
                        begin = clock();
                        ret = aq_dynamic_administrator_omp(NUM_TASKS, num_threads[nt], left_limit, right_limit, tolerance[to], calc_function[ft]);
                        end = clock();
                        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
                        mean_time_spent = mean_time_spent + time_spent / 10.0;
                    }    
                    printf("OMP_DYN %Le %i %s %Le %f\n", tolerance[to], num_threads[nt], function_name[ft], ret, mean_time_spent);
                }
            }
        }

    } else {

        printf("\nChoose one type of parallel implementation: -s for pthreads with semafores, -m for pthreads with monitors or -o for openmp.\nThen choose one variant of the adaptative quadrature: -t for static or -d for dynamic.\n");
    }

    printf("\n");
    return 0;
}