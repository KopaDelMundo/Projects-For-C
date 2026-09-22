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

void pool_spawn(projectile pool);
void pool_update(projectile pool);

int main(void)
{
    Proj_Pool bullet_pool = { };
}

void pool_spawn(projectile pool)
{
    for(int i = 0; i < POOL_SIZE; i++)
    {

    }
}