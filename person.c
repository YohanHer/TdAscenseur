#include <stdio.h>
#include <stdlib.h>

#include "person.h"

Person* createPerson(int src, int dest){
    Person *p = (Person*)malloc(sizeof(Person));
    p->dest=dest;
    p->src=src;
    return p;
}

PersonList* insert(Person *p, PersonList *list){
    PersonList *listnew = (PersonList*)malloc(sizeof(PersonList));
    listnew->next=list;
    listnew->person=p;
    return listnew;
}