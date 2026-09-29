#include <stdlib.h>
#define BASE_CAP 10

void da_init(DynArray *a)
{
    a->capacity = 10;
    a->count = 0;
    a->items = malloc(sizeof(Entity) * 10);
    printf("Dynamic array initialized.\n");
}

void da_push(DynArray *a, Entity *e)
{
    Entity *tmp;

    if(a->count + 1 >= a->capacity)
    {
        a->capacity = a->capacity * 2;
        
        tmp = realloc(a->items, sizeof(Entity) * a->capacity);
        if(tmp == NULL)
        {
            printf("ALLOCATION FAILED: ABORTING\n");
            return;
        }
        a->items = tmp;
        
    }
    a->items[a->count] = *e;
    a->count++;
}

Entity *da_get(DynArray *a, int i)
{
    Entity *p = NULL;
    if(i < 0 || i > a->count - 1)
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
    Entity *tmp;
    int new_capacity;

    //printf("The bounds are 0 and %d\n", a->count - 1);
    
    if(num < 0 || num > (a->count - 1))
    {
        printf("%d is not a valid selection.\n", num);
    }
    else
    {
        printf("Removing Entity at index: %d\n", num);

        a->items[num] = a->items[a->count - 1];
        a->count -= 1;
        

        if(a->count <= a->capacity / 4 && a->capacity / 2 >= BASE_CAP)
        {


            new_capacity = a->capacity / 2;

            
            tmp = realloc(a->items, sizeof(Entity) * new_capacity);
            if(tmp == NULL)
            {
                printf("ALLOCATION FAILED: ABORTING\n");
                return;
            }

            a->items = tmp;
            a->capacity = new_capacity;
        }   
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
    printf("Current Count: %d\n", a->count);
    printf("Current Capacity: %d\n", a->capacity);
}

void da_clear(DynArray *a)
{
    printf("Clearing out dynamic array...\n");
    a->items[0].itemNum = 0;
    a->capacity = BASE_CAP;
    a->count = 0;
}

void da_free(DynArray *a)
{
    free(a->items);
    a->items = NULL;
    a->count = 0;
    a->capacity = 0;
}