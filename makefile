all: main.o
	gcc -o runthis main.o parse.o
main.o: main.c
	gcc -c main.c
clean:
	rm *.o
run:
	./runthis