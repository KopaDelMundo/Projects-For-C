//ENEMY AI DISPATCH TABLE


#include <stdio.h>
#define ENEMY_COUNT 4

typedef struct Enemy {
    const char* name;
    int type; 
    int hp;
} Enemy;

typedef void (*AIBehavior)(Enemy*);

void ai_aggressive(Enemy *self); //prints a lunge
void ai_coward(Enemy *self); //flees if hp low
void ai_healer(Enemy *self); //ai_healer
void ai_locator(Enemy *self);

int main(void)
{
    AIBehavior behaviors[] = { ai_aggressive, ai_coward, ai_healer , ai_locator}; //void (*behaviors[])(Enemy*)

    struct Enemy badguys[] = {
        {"Blimpo", 0 ,20 },
        {"Climpo", 1, 20 },
        {"Bort", 2, 10 },
        {"Comp Sci Student", 3, 100}
    };

    for(int i = 0; i < ENEMY_COUNT; i++)
    {
        behaviors[badguys[i].type](&badguys[i]);
    }

    

}


void ai_aggressive(Enemy *self)
{
    printf("%s (hp %d) lunges forward!\n", self->name, self->hp);
}

void ai_coward(Enemy *self)
{
    if (self->hp < 30) printf("The enemy %s has fled!\n", self->name);
}

void ai_healer(Enemy *self)
{
    if(self->hp < 50)
    {
        printf("%s (hp %d) is going to heal!\n", self->name, self->hp);
        self->hp += 50;
        printf("%s now has %d hp!\n", self->name, self->hp);
    }
}

void ai_locator(Enemy *self)
{
    printf("%s managed to find its own memory address! It's %p.\n", self->name, (void*)self);
}