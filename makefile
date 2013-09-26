all : paqi

paqi : mon_adaquad.o sem_adaquad.o omp_adaquad.o adaquad.o aqqueue.o mon_aqqueue.o sem_aqqueue.o omp_aqqueue.o paqi.c
	gcc -Wall -o paqi mon_adaquad.o sem_adaquad.o omp_adaquad.o adaquad.o aqqueue.o mon_aqqueue.o sem_aqqueue.o omp_aqqueue.o adaquad.h paqi.c -lpthread -fopenmp

omp_adaquad.o : aqqueue.o omp_aqqueue.o adaquad.o omp_adaquad.c
	gcc -Wall -c -o omp_adaquad.o aqqueue.o omp_aqqueue.o adaquad.o omp_adaquad.c -fopenmp

omp_aqqueue.o : aqqueue.o omp_aqqueue.c
	gcc -Wall -c -o omp_aqqueue.o aqqueue.o omp_aqqueue.c -fopenmp

sem_adaquad.o : aqqueue.o sem_aqqueue.o adaquad.o sem_adaquad.c
	gcc -Wall -c -o sem_adaquad.o aqqueue.o sem_aqqueue.o adaquad.o sem_adaquad.c

sem_aqqueue.o : aqqueue.o sem_aqqueue.c
	gcc -Wall -c -o sem_aqqueue.o aqqueue.o sem_aqqueue.c

mon_adaquad.o : aqqueue.o mon_aqqueue.o adaquad.o mon_adaquad.c
	gcc -Wall -c -o mon_adaquad.o aqqueue.o mon_aqqueue.o adaquad.o mon_adaquad.c

mon_aqqueue.o : aqqueue.o mon_aqqueue.c
	gcc -Wall -c -o mon_aqqueue.o aqqueue.o mon_aqqueue.c

adaquad.o : adaquad.c
	gcc -Wall -c -o adaquad.o adaquad.c

aqqueue.o : aqqueue.c
	gcc -Wall -c -o aqqueue.o aqqueue.c

clean:
	rm -rf *.o
mrproper: clean
	rm -rf test