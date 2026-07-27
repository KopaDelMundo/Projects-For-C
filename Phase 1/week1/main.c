//current status//
//implemented functions working, need to implement element multiplier and print hit

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define earth 1
#define air 2
#define water 3
#define fire 4


int roll_base_damage(int attack, int defense);
int apply_variance(int damgage);
int is_critical(int crit_chance_percent);
float elemental_multiplier(int atk_element, int def_element);
void assign_element();

int main()
{
    srand(time(NULL));

    
    //names
    //char* person1 = "Aaron";
    //char* person2 = "Danny";

    //health
    //int p1hp = 700;
    //int p2hp = 700;
    //stats//
    //attack
    int p1atk = 550;

    //int p2atk = 105;
    //defense
    //int p1def = 65;
    int p2def = 336;
    //crit_chance
    int p1crit = 10;

    for (int i = 0; i < 5; i++)
    {
        int base_dmg = roll_base_damage(p1atk, p2def);
        int var_damage = apply_variance(base_dmg);
        if (is_critical(p1crit))
        {
            var_damage = var_damage * 2;
        }
        printf("attack is %d \n",var_damage);
        printf("/////------//////");
    } 

}

int roll_base_damage(int attack, int defense)
{
    int result = attack - defense;

    if (attack - defense < 1) result = 1;

    return result;
}

int apply_variance(int damage)
{
    printf("Base damage is %d\n", damage);
    int percent;
    do
    {
        percent = rand() % 100;
    } while (percent > 15 || percent < 1);

    printf("Percent modifier is %d\n", percent);
    
    float percent_of_damage = (damage * percent) / 100;
    printf("%d percent of %i is %f\n", percent, damage, percent_of_damage);

    int flip_num = rand() % 100;

    int result = 0;
    if (flip_num % 2 == 0)
    {
        result = damage + percent_of_damage;
        printf("damage percent is positive\n");
    }
    else{
        result = damage - percent_of_damage;
        printf("damage percent is negative\n");
    }
    
    if(result < 1) result = 1;
    printf("The resulting attack damage is  %d\n", result);

    return result;
}

int is_critical(int crit_chance_percent)
{
    int crit;
    int check = (rand() % 100) + 1;
    if(check <= crit_chance_percent)
    {
        crit = 1;
        printf("A critical hit!\n");
    }
    else
    {
        crit = 0;
    }

    return crit;
}

int assign_element(char* person,int element_stat)
{
    
}

float elemental_multiplier(int atk_element, int def_element)
{
    char* element[] = {"earth","air","water","fire"};
    int atk_el = (rand() % 4) + 1;
    int def_el = (rand() % 4) + 1;

    if



    
}