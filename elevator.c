#include <stdio.h>
#include <stdlib.h>

#include "elevator.h"
#include "person.h"

Elevator *create_elevator(int capacity, int currentFloor, PersonList *persons){
    Elevator *e = (Elevator*)malloc(sizeof(Elevator));
    e->capacity=capacity;
    e->currentFloor=currentFloor;
    e->persons=persons;
    return e;
}

Building *create_building(int nbFloor, Elevator *elevator, PersonList **waitingLists){
    Building *b = (Building*)malloc(sizeof(Building));
    b->nbFloor=nbFloor;
    b->elevator=elevator;
    b->waitingLists=waitingLists;
    return b;
}

PersonList* exitElevator(Elevator *e){
    PersonList *test = e->persons;
    PersonList *sortie = (PersonList*)malloc(sizeof(PersonList));
    PersonList *newOccupants=(PersonList*)malloc(sizeof(PersonList));
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
    PersonList *test = waitinglist;
    PersonList *entree = (PersonList*)malloc(sizeof(PersonList));
    if (test != NULL){
        PersonList *newWaiting = (PersonList*)malloc(sizeof(PersonList));
        int places =e->capacity;
        PersonList *testCapa = e->persons;
        if (e->persons!=NULL){
            places += -1;
        }
        while (testCapa != NULL){
            places += -1;
            testCapa = testCapa->next;
        }
        if (test->person!=NULL && test->person->src==e->currentFloor && places>0){
            places += -1;
            entree = insert(test->person, entree);
        }
        else {
            newWaiting=insert(test->person, newWaiting);
        }
        while (test->next!=NULL){
            test = test->next;
            if (test->person->src==e->currentFloor && places > 0){
                places += -1;
                entree = insert(test->person, entree);
            }
            else {
                newWaiting=insert(test->person, newWaiting);
            }
        }
    	waitinglist =newWaiting;
	}
    return entree;
}

void stepElevator(Building *b){
    if (b->elevator->currentFloor==b->elevator->targetFloor){
        PersonList *sortant = exitElevator(b->elevator);
        if (sortant != NULL){
            b->waitingLists[b->elevator->currentFloor] = insert(sortant->person, b->waitingLists[b->elevator->currentFloor]);
            while (sortant->next != NULL){
                sortant = sortant->next;
                b->waitingLists[b->elevator->currentFloor] = insert(sortant->person, b->waitingLists[b->elevator->currentFloor]);
            }
        }
        PersonList *entrant = enterElevator(b->elevator, b->waitingLists[b->elevator->currentFloor]);
        if (entrant != NULL){
            b->elevator->persons = insert(entrant->person, b->elevator->persons);
            while (entrant->next != NULL){
                entrant = entrant->next;
                b->elevator->persons = insert(entrant->person, b->elevator->persons);
            }
        }
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