#include <stdio.h>

//--------------data--------------
typedef struct {
    float x, y;
} Vector2;

typedef enum {
    STATE_IDLE,
    STATE_RUN,
    STATE_ATTACK,
    STATE_HURT,
    STATE_DEAD
} EntityState;

typedef struct {
    int frame_count;
    float frame_duration;
} AnimationClip;

typedef struct {
    Vector2 pos, vel;
    int hp, max_hp;
    int facing;
    EntityState state;
} Entity;

typedef struct {
    int speed;
} ProjectileData;

typedef struct {
    int amount;
    char *itemName;
} PickupData;

typedef struct {
    char *npcName;
} NpcData;

typedef enum {
    KIND_PROJECTILE,
    KIND_PICKUP,
    KIND_NPC
} EntityKind;

typedef struct {
    EntityKind kind;
    union {
        ProjectileData proj;
        PickupData pickup;
        NpcData npc;
    } data;
} EntityExtra;

//--------------function prototypes--------------
int can_transition(EntityState from, EntityState to);   //handles rules of transitioning states (eg you can't leave state_dead)
void set_state(Entity *e, Entity to);                   //transitions only if can_transition allows
void entity_take_damage(Entity *e, int dmg);            //subtracts hp, forces state_hurt (or state_dead at 0 hp)
void print_entity(const Entity *e);                     //one line status (const reading only)
const char* state_name(EntityState s);

int main(void)
{
    Entity e1 = {
        .pos={
            .x=100,
            .y=100,
        },
        .vel={
            .x=0,
            .y=0
        },
        .hp=1000,
        .max_hp=1000,
        .facing=1,
        .state=STATE_IDLE
    };

    print_entity(&e1);
}

void print_entity(const Entity *e)
{
    const char* stateS = state_name(e->state);
    char sideFacing;
    if(e->facing == 0)
    {
        sideFacing = 'L';
    }
    else
    {
        sideFacing = 'R';
    }
    printf("Entity: hp %d/%d | pos(%f, %f) | facing %c |  %s\n", e->hp, e->max_hp, e->pos.x, e->pos.y, sideFacing, stateS);
}

const char* state_name( EntityState s)
{
    char* stringToReturn;
    switch (s) {
        case STATE_IDLE:
            stringToReturn = "STATE_IDLE";
            break;
        case STATE_RUN:
            stringToReturn = "STATE_RUN";
            break;
        case STATE_ATTACK:
            stringToReturn = "STATE_ATTACK";
            break;
        case STATE_HURT:
            stringToReturn = "STATE_HURT";
            break;
        case STATE_DEAD:
            stringToReturn = "STATE_DEAD";
            break;
        default:
            stringToReturn = "Invalid";
            break;
    }

    return stringToReturn;
}

int can_transition(EntityState from, EntityState to)
{
    
}