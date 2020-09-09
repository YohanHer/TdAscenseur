#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "person.h"

typedef struct _Elevator {
    int capacity; //capacité max de la cabine
    int currentFloor; //étage courant
    int targetFloor; //destination
    PersonList *persons; //personnes dans la cabine
} Elevator;

typedef struct _Building {
    int nbFloor; //nombre d'étages de l'immeuble
    Elevator *elevator;
    PersonList **waitingLists; //array of waiting list (on per floor)
}Building;

Elevator *create_elevator(int capacity, int currentFloor, PersonList *persons);
Building *create_building(int nbFloor, Elevator *elevator, PersonList **waitingLists);

PersonList* exitElevator(Elevator *e);
PersonList* enterElevator(Elevator *e, PersonList *list);
void stepElevator(Building *b);

#endif