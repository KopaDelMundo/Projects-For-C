#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int hp;
} Entity;

typedef struct {
    Entity *items;
    int count;
    int capacity;
} DynArray;

//function prototypes
void da_init(DynArray *a);              //start empty (capacity at 0 or small default)
void da_push(DynArray *a, Entity *e);   //append; grow (double capacity via realloc) when full
Entity *da_get(DynArray *a, int i);     //bounds-checked pointer to element i (or NULL)
void da_remove_swap(DynArray *a, int i); /*O(1) removal wwhen order doesn't matter (games don't care)
overwrite slot i with the last element, decrement count. Edge case: removing the last element.*/
void da_free(DynArray *a);              //free and zero it out


int main(void)
{
    Entity e1 = { 400 };
}