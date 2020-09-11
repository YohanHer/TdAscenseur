PROG=main
OBJ= main.o elevator.o person.o

main : main.o elevator.o person.o
	gcc -o main main.o elevator.o person.o -lncurses

main.o : main.c elevator.h person.h
	gcc -c main.c elevator.h person.h -lncurses

elevator.o: elevator.c elevator.h person.h 
	gcc -c elevator.c elevator.h person.h

person.o: person.c person.h 
	gcc -c person.c person.h

clean :
	rm -f *.o