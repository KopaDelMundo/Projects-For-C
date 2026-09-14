#include <stdio.h>
#include <stdlib.h>

#define BASE_CAP 10;

//TODO: 

typedef struct {
    int itemNum;
} Entity;

typedef struct {
    Entity *items;
    int count; //amount of items 
    int capacity; //max number of items
} DynArray;

//function prototypes
void da_init(DynArray *a);                 //start empty (capacity at 0 or small default)
void da_push(DynArray *a, Entity *e);      //append; grow (double capacity via realloc) when full
Entity *da_get(DynArray *a, int i);        //bounds-checked pointer to element i (or NULL)
void da_remove_swap(DynArray *a, int num); //O(1) removal wwhen order doesn't matter (games don't care) overwrite slot i with the last element, decrement count. Edge case: removing the last element.                                    
void da_free(DynArray *a);                 //free and zero it out
void print_DynArray(DynArray *a);

int main(void)
{
    DynArray dy1;
    da_init(&dy1);
    Entity e1 = { 1 };
    Entity e2 = { 2 };
    Entity e3 = { 3 };
    Entity e4 = { 4 };
    Entity e5 = { 5 };
    da_push(&dy1, &e1);
    da_push(&dy1, &e2);
    da_push(&dy1, &e3);
    da_push(&dy1, &e4);
    da_push(&dy1, &e5);

    

    //Entity *p = da_get(&dy1, 0);

    print_DynArray(&dy1);

    da_remove_swap(&dy1, 0);
    printf("----------------------------------------\n");
    printf("----------------------------------------\n");
    
    print_DynArray(&dy1);

    free(dy1.items);
    
}

void da_init(DynArray *a)
{
    a->capacity = 10;
    a->count = 0;
    a->items = malloc(sizeof(Entity) * 10);
    printf("|DEBUG| Dynamic array initialized.\n");
}

void da_push(DynArray *a, Entity *e)
{
    if(a->count + 1 >= a->capacity)
    {
        a->capacity *= 2;
        a->items = realloc(a->items, sizeof(Entity) * a->capacity);
    }

    a->items[a->count] = *e;
    a->count++;

}

Entity *da_get(DynArray *a, int i)
{
    Entity *p = NULL;
    if(i > a->capacity - 1)
    {
        printf("Selection was out of bounds.");
    }
    else
    {
        p = &a->items[i];
    }

    return p;
}

void da_remove_swap(DynArray *a, int num)
{

    if(num < 0 || num > (a->count - 1))
    {
        printf("Not a valid selection.\n");
    }
    else
    {
        a->items[num] = a->items[a->count - 1];
        if(a->count < a->capacity / 2 && a->capacity % 10 == 0)
        {
            if(a->capacity < 10)
            {
                a->capacity = 10;
            }
            else
            {
                a->capacity /= 2;
            }
            
            a->items = realloc(a->items, sizeof(Entity) * a->capacity);
        }
        a->count -= 1;
    }
}

void print_DynArray(DynArray *a)
{
    for(int i = 0; i < a->count; i++)
    {
         
        printf("----------------------------------------\n");
        printf("Entity: %d \n", a->items[i].itemNum);
        printf("----------------------------------------\n");
    }
}

void da_free(DynArray *a)
{
    a->items[0].itemNum = 0;
    a->capacity = BASE_CAP;
}