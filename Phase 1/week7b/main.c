#include <stdio.h>

#define POOL_SIZE 256

typedef enum {
    INACTIVE,
    ACTIVE
} proj_flag;

typedef struct {
    float x, y;
} Vector2;

typedef struct {
    Vector2 pos, vel;
    int lifetime;           //ticks remaining before it expires
    proj_flag active_state; //is this slot in use?
} projectile;

typedef struct {
    projectile items[POOL_SIZE];
} Proj_Pool;

int pool_spawn(Proj_Pool *p, Vector2 pos, Vector2 vel, int lifetime);
void pool_update(Proj_Pool *p);
void init_pool(Proj_Pool *p);
void print_entity(Proj_Pool *p, int index);

int main(void)
{
    Proj_Pool bullet_pool; 
    init_pool(&bullet_pool); //goes through every item and sets active to 0 (inactive)
    int spawnResult1;
    Vector2 testpos = {0,0};
    Vector2 testvel = {1,1};
    int lifetime = 3;

    //spawnResult1

    for(int i = 0; i < POOL_SIZE+ 1; i++)
    {
        spawnResult1 = pool_spawn(&bullet_pool, testpos, testvel, lifetime); 
        if(spawnResult1 == -1)
        {
            printf("Pool is full\n");
        }
    }



}


int pool_spawn(Proj_Pool *p, Vector2 pos, Vector2 vel, int lifetime)
{
    int i;
    for(i = 0; i < POOL_SIZE; i++)
    {
        if(p->items[i].active_state == INACTIVE)
        {
            p->items[i].pos           = pos;
            p->items[i].vel           = vel;
            p->items[i].lifetime      = lifetime;
            p->items[i].active_state  = ACTIVE;
            return 1;
        }
    }
    
    return -1;
}

void pool_update(Proj_Pool *p)
{
    for(int i = 0; i < POOL_SIZE; i++)
    {
        if(p->items[i].active_state == 1)
        {
            p->items[i].pos.x       += p->items[i].vel.x;
            p->items[i].pos.y       += p->items[i].vel.y;
            p->items[i].lifetime    -= 1;
            if(p->items[i].lifetime == 0)
            {
                p->items[i].active_state = INACTIVE;
            }
        }
    }
}

void init_pool(Proj_Pool *p)
{
    for(int i = 0; i < POOL_SIZE; i++)
    {
        p->items[i].active_state = INACTIVE;
    }
}

void print_entity(Proj_Pool *p, int index)
{
    printf("Entity at Index: %d\n", index);
    printf("Active status: %d\n", p->items[index].active_state);
    printf("Lifetime: %d\n", p->items[index].lifetime);
    printf("\n");
    //printf("\n");
}
