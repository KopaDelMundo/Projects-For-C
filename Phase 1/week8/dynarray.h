#include "entity.h"
#ifndef DYNARRAY_H
#define DYNARRAY_H


//File dynarray.h
typedef struct {
    Entity *items;
    int count; //amount of items 
    int capacity; //max number of items
} DynArray;

void da_init(DynArray *a);                 //start empty (capacity at 0 or small default)
void da_push(DynArray *a, Entity *e);      //append; grow (double capacity via realloc) when full
Entity *da_get(DynArray *a, int i);        //bounds-checked pointer to element i (or NULL)
void da_remove_swap(DynArray *a, int num); //O(1) removal wwhen order doesn't matter (games don't care) overwrite slot i with the last element, decrement count. Edge case: removing the last element.                                    
void da_free(DynArray *a);
void da_clear(DynArray *a);                 //free and zero it out
void print_DynArray(DynArray *a);

#endif