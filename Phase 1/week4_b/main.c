//ENEMY AI DISPATCH TABLE
//TODO:

#include <stdio.h>

typedef struct Enemy {
    const char* name;
    int hp;
} Enemy;

typedef void (*AIBehavior)(Enemy*);

void ai_agressive(Enemy *self); //prints a lunge
void ai_coward(Enemy *self); //flees if hp low
void ai_healer(Enemy *self); //ai_healer

int main(void)
{
    AIBehavior behaviors = { ai_agressive, ai_coward, ai_healer }; //void (*behaviors[])(Enemy*)

    struct Enemy BadGuy1 = {"Blimpo", 100 };
    struct Enemy BadGuy1 = {"Climpo", 100 };
    struct Enemy BadGuy1 = {"Bort", 100 };

}

