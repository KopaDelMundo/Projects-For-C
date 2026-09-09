#include <stdio.h>

//--------------data--------------

typedef enum { TRANS_ILLEGAL, TRANS_OK, TRANS_SAME } TransitionResult;

typedef struct {
    float x, y;
} Vector2;

typedef enum {
    STATE_IDLE,
    STATE_RUN,
    STATE_ATTACK,
    STATE_HURT,
    STATE_DEAD,
    STATE_COUNT //keeps track of number of states in enum
} EntityState;

typedef struct {
    int frame_count;
    float frame_duration;
} AnimationClip;

typedef struct {
    int speed;
} ProjectileData;

typedef struct {
    char itemName[32];
} PickupData;

typedef struct {
    char npcName[20];
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

typedef struct {
    Vector2 pos, vel;
    int hp, max_hp;
    int facing;
    EntityState state;
    EntityExtra type_of_entity;
} Entity;

//--------------function prototypes--------------
TransitionResult can_transition(EntityState from, EntityState to);   //handles rules of transitioning states (eg you can't leave state_dead)
void set_state(Entity *e, EntityState to);              //transitions only if can_transition allows
void entity_take_damage(Entity *e, int dmg);            //subtracts hp, forces state_hurt (or state_dead at 0 hp)
void print_entity(const Entity *e);                     //one line status (const reading only)
const char* state_name(EntityState s);                  //turns enum into string literal

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
        .state=STATE_IDLE,
        .type_of_entity = {
            .kind=KIND_NPC,
            .data = {
                .npc = { .npcName = "Hero"}
            }
        } 
    };

    Entity e2 = {
        .pos={
            .x=200,
            .y=200,
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

       Entity e3 = {
        .pos={
            .x=200,
            .y=200,
        },
        .vel={
            .x=0,
            .y=0
        },
        .hp=1000,
        .max_hp=1000,
        .facing=1,
        .state=STATE_IDLE,
        .type_of_entity = {
            .kind = KIND_PROJECTILE,
            .data = {
                .proj = { .speed = 120 }
            }
        }
    };

    print_entity(&e1);
    set_state(&e1, STATE_RUN);
    print_entity(&e1);
    set_state(&e1, STATE_ATTACK);
    print_entity(&e1);
    set_state(&e1, STATE_HURT);
    print_entity(&e1);
    set_state(&e1, STATE_DEAD);
    print_entity(&e1);
    set_state(&e1, STATE_RUN);
    print_entity(&e1);
    set_state(&e1, STATE_ATTACK);
    print_entity(&e1);
    set_state(&e1, STATE_HURT);
    print_entity(&e1);
    printf("---ENTITY 2 TESTING---\n");
    entity_take_damage(&e2, 500);
    print_entity(&e2);
    entity_take_damage(&e2, 500);
    print_entity(&e2);
    entity_take_damage(&e2, 500);
    print_entity(&e2);

    printf("---ENTITY UNION TESTING---\n");
    print_entity(&e3);
}

void print_entity(const Entity *e)
{
    const char* stateS = state_name(e->state);
    char sideFacing;
    if(e->facing < 0)
    {
        sideFacing = 'L';
    }
    else
    {
        sideFacing = 'R';
    }
    printf("Entity: hp %d/%d | pos(%.f, %.1f) | facing %c | %s\n", e->hp, e->max_hp, e->pos.x, e->pos.y, sideFacing, stateS);
    if(e->type_of_entity.kind == KIND_NPC)
    {
        printf("Name: %s\n", e->type_of_entity.data.npc.npcName);
    }
    else if(e->type_of_entity.kind == KIND_PROJECTILE)
    {
        printf("Projectile speed: %d mph\n", e->type_of_entity.data.proj.speed);
    } 
}

const char* state_name( EntityState s)
{
    const char* stringToReturn;
    switch (s) {
        case STATE_IDLE:
            stringToReturn = "IDLE";
            break;
        case STATE_RUN:
            stringToReturn = "RUN";
            break;
        case STATE_ATTACK:
            stringToReturn = "ATTACK";
            break;
        case STATE_HURT:
            stringToReturn = "HURT";
            break;
        case STATE_DEAD:
            stringToReturn = "DEAD";
            break;
        default:
            stringToReturn = "Invalid";
            break;
    }

    return stringToReturn;
}

TransitionResult can_transition(EntityState from, EntityState to)
{
    //Table answers "can [ROW] transiton to the state at [COL]"
    const TransitionResult legal[STATE_COUNT][STATE_COUNT] = {
                    //IDLE -- RUN -- ATTACK -- HURT -- DEAD
        /*IDLE*/    {TRANS_SAME, TRANS_OK, TRANS_OK, TRANS_OK, TRANS_ILLEGAL}, 
        /*RUN*/     {TRANS_OK, TRANS_SAME, TRANS_OK, TRANS_OK, TRANS_ILLEGAL},
        /*ATTACK*/  {TRANS_OK, TRANS_OK, TRANS_SAME, TRANS_OK, TRANS_ILLEGAL},
        /*HURT*/    {TRANS_OK, TRANS_OK, TRANS_ILLEGAL, TRANS_SAME, TRANS_OK},
        /*DEAD*/    {TRANS_ILLEGAL, TRANS_ILLEGAL, TRANS_ILLEGAL, TRANS_ILLEGAL, TRANS_SAME}
    }; 
    printf("DEBUG: legal[%d][%d] = %d\n", from, to, legal[from][to]);
    return legal[from][to];
}

void set_state(Entity *e, EntityState to)
{
    const char* fromState = state_name(e->state);
    const char* toState = state_name(to);
    int legal_transition = can_transition(e->state, to);
    if(legal_transition == TRANS_OK)
    {
        printf("DEBUG: Legal transtition between states.\n");
        printf("%s -> %s\n", fromState, toState);
        e->state = to;
    }
    else if(legal_transition == TRANS_ILLEGAL)
    {
        printf("DEBUG: Not a legal transition. No change made.\n");
    }
    else if(legal_transition == TRANS_SAME)
    {
        printf("DEBUG: Entity is already in the requested state.\n");
    } 
}

void entity_take_damage(Entity *e, int dmg)
{
    //if hp is more than 0 then you aren't dead
    if(e->hp > 0)
    {
        e->hp -= dmg;
        set_state(e, STATE_HURT);
    }
    if(e->hp <= 0)
    {
        e->hp = 0;
        set_state(e, STATE_DEAD);
    }
}