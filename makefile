all: main.o
	gcc -o runthis main.o
main.o: main.c main.h
	gcc -c main.c
clean:
	rm *.o
run:
	./runthis
