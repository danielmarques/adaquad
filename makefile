all : test

test : mon_adaquad.o sem_adaquad.o adaquad.o aqqueue.o mon_aqqueue.o sem_aqqueue.o tests.c
	gcc -Wall -o test mon_adaquad.o sem_adaquad.o adaquad.o aqqueue.o mon_aqqueue.o sem_aqqueue.o adaquad.h tests.c -lpthread

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