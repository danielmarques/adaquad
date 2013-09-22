all : test

test : adaquad.o aqqueue.o tests.c
	gcc -o test adaquad.o aqqueue.o tests.c 

adaquad.o : aqqueue.o adaquad.c
	gcc -c -o adaquad.o adaquad.c

aqqueue.o : aqqueue.c
	gcc -c -o aqqueue.o aqqueue.c

clean:
	rm -rf *.o
mrproper: clean
	rm -rf test