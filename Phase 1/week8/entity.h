#ifndef ENTITY_H
#define ENTITY_H

typedef struct {
    int itemNum;
} Entity;

typedef struct {
    Entity *items;
    int count; //amount of items 
    int capacity; //max number of items
} DynArray;

#endif