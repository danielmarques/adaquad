all : test

test : adaquad.o aqqueue.o tests.c
	gcc -Wall -o test adaquad.o aqqueue.o tests.c -lpthread

aqinteg : adaquad.o aqqueue.o integral.c
	gcc -Wall -o aqinteg adaquad.o aqqueue.o aqinteg.c -lpthread

adaquad.o : aqqueue.o adaquad.c
	gcc -Wall -c -o adaquad.o adaquad.c

aqqueue.o : aqqueue.c
	gcc -Wall -c -o aqqueue.o aqqueue.c

clean:
	rm -rf *.o
mrproper: clean
	rm -rf test