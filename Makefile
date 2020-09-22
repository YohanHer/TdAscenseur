PROG=main
OBJ= main.o elevator.o person.o
CFLAGS = -g

main : main.o elevator.o person.o
	gcc -o main main.o elevator.o person.o -lncurses

main.o : main.c elevator.h person.h
	gcc $(CFLAGS) -c main.c elevator.h person.h

elevator.o: elevator.c elevator.h person.h 
	gcc $(CFLAGS) -c elevator.c

person.o: person.c person.h 
	gcc $(CFLAGS) -c person.c

clean :
	rm -f *.o main