all: main.o parse.o
	gcc -o runthis main.o parse.o
main.o: main.c
	gcc -c main.c
parse.o: parse.c
	gcc -c parse.c
clean:
	rm *.o
run:
	./runthis