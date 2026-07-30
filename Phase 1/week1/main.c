//current status//
//All functions implemented, now to work everything into gameloop that stops after 5 turns or 0 hp
//completing the turn taking for damage

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int roll_base_damage(int attack, int defense);
int apply_variance(int damgage);
int is_critical(int crit_chance_percent);
float elemental_multiplier();
void assign_element();

int main()
{
    srand(time(NULL));

    
      ////names////
    char* person1 = "Hero";
    char* person2 = "Villian";

      ////stats////
    //health
    int p1hp = 700;
    int p2hp = 400;
        
    //attack//
    int p1atk = 550;
    int p2atk = 505;
    
    //defense
    int p1def = 350;
    int p2def = 320;
    //crit_chance
    int p1crit = 10;
    int p2crit = 15;

        printf("//-----------THE BATTLE BEGINS-----------//\n");

    for (int i = 1; i < 6; i++)
    {

        if(p1hp <= 0 || p2hp <= 0) break;

        printf("-------------------------------------------\n");
        printf("------------------TURN %i------------------\n",i);
        printf("-------------------------------------------\n");
        printf("     Hero HP: %i    |    Villian HP: %i   \n",p1hp,p2hp);
        printf("-------------------------------------------\n");
        

        int base_dmg;
        int var_damage;
        float element_dmg;
        int attacker_crit;
        char* attacker;
        char* defender;


        if (i % 2 != 0)
        {
            base_dmg = roll_base_damage(p1atk, p2def);
            attacker_crit = p1crit;
            attacker = person1;
            defender = person2;
            printf("Hero gets ready to attack!\n");
        }
        else
        {
            base_dmg = roll_base_damage(p2atk, p1def);
            attacker_crit = p2crit;
            attacker = person2;
            defender = person1;
            printf("Villian gets ready to attack!\n");
        }
                   
        var_damage = apply_variance(base_dmg);
        element_dmg = elemental_multiplier();

        if (element_dmg == 2.0)
        {
            var_damage = var_damage + 100;
            printf("Elemental advantage! Damage increased.\n");
        }
        else if (element_dmg == 0.5)
        {
            var_damage =var_damage -100;
            printf("Elemental disadvantage! Damage reduced.\n");
        }

        if (is_critical(attacker_crit))
        {
            var_damage = var_damage * 2;
            printf("It was a critical attack!\n");
        }
            


        if(var_damage <= 0) var_damage = 1;

        if (i % 2 != 0)
        {
            p2hp -= var_damage;
        }
        else
        {
            p1hp -= var_damage;
        }

        printf("%s attacks %s for %i\n",attacker, defender, var_damage);
        
        if(p1hp <= 0)
        {
            printf("The Hero is defeated!\n");
        }
        else if (p2hp <= 0)
        {
            printf("The Villian is defeated!\n");
        }
        
    } 



    printf("-------------------------------------------\n");

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

float elemental_multiplier()
{
    float didItHit = 1.0;
    int atk_el = (rand() % 4) + 1;
    int def_el = (rand() % 4) + 1;

    if ((atk_el % 4) +1 == def_el) didItHit = 2.0;
    else if ((def_el % 4) + 1 == atk_el) didItHit = 0.5;

    return didItHit;
    
}