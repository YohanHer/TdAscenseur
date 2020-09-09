#include <stdio.h>
#include <stdlib.h>

#include "elevator.h"
#include "person.h"

Elevator *create_elevator(int capacity, int currentFloor, PersonList *persons){
    Elevator *e;
    e->capacity=capacity;
    e->currentFloor=currentFloor;
    e->persons=persons;
    e->targetFloor=currentFloor;
    return e;
}

Building *create_building(int nbFloor, Elevator *elevator, PersonList **waitingLists){
    Building *b;
    b->nbFloor=nbFloor;
    b->elevator=elevator;
    b->waitingLists=waitingLists;
    return b;
}

PersonList* exitElevator(Elevator *e){
    PersonList *test = e->persons;
    PersonList *sortie = NULL;
    PersonList *newOccupants=NULL;
    if (test != NULL){
        if (test->person !=NULL && test->person->dest==e->currentFloor){
            sortie = insert(test->person, sortie);
        }
        else{
            newOccupants = insert(test->person, newOccupants);
        }
        while (test->next != NULL){
            test = test->next;
            if (test->person->dest==e->currentFloor){
                sortie = insert(test->person, sortie);
            }
            else{
                newOccupants = insert(test->person, newOccupants);
            }
        }
        e->persons=newOccupants;
    }
    return sortie;
}
PersonList* enterElevator(Elevator *e, PersonList *waitinglist){
    PersonList *entree = NULL;
    if (waitinglist != NULL){
        PersonList *newWaiting = NULL;
        int places =e->capacity;
        PersonList *testCapa = e->persons;
        if (e->persons->person!=NULL){
            places += -1;
        }
        while (testCapa->next != NULL){
            places += -1;
        }
        if (waitinglist->person!=NULL && waitinglist->person->src==e->currentFloor && places>0){
            places += -1;
            entree = insert(waitinglist->person, entree);
        }
        else {
            newWaiting=insert(waitinglist->person, newWaiting);
        }
        while (waitinglist->next!=NULL){
            waitinglist = waitinglist->next;
            if (waitinglist->person->src==e->currentFloor && places > 0){
                places += -1;
                entree = insert(waitinglist->person, entree);
            }
            else {
                newWaiting=insert(waitinglist->person, newWaiting);
            }
        }
    	waitinglist =newWaiting;
	}
    return entree;
}

void stepElevator(Building *b){
    if (b->elevator->currentFloor==b->elevator->targetFloor){
        PersonList *sortant = exitElevator(b->elevator);
        
    }
    else {
        if (b->elevator->currentFloor<b->elevator->targetFloor){
            b->elevator->currentFloor++;
        }
        else{
            b->elevator->currentFloor += -1;
        }
    }
}