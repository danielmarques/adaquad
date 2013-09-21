all : test

test : adaquad.o tests.c 
	gcc -o test adaquad.o tests.c

adaquad.o : adaquad.c
	gcc -c -o adaquad.o adaquad.c

clean:
	rm -rf *.o
mrproper: clean
	rm -rf test