
//TODO: complete damage and add defend/item mechanics

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

    ////stats////       HP | ATK | DEF | CRIT      
    int hero_stats[]  = {700, 550, 350, 10};
    int enemy_stats[] = {500, 505, 320, 15};

    int item = 3;

void print_status(void);
int is_battle_over(void);
int read_menu_choice(void);
void player_turn(int choice);
void enemy_turn(void);
//------------//
int roll_base_damage(int attack, int defense);
int apply_variance(int damgage);
int is_critical(int crit_chance_percent);
float elemental_multiplier(void);
//-----------//
int calculate_attack(int attacker[], int defender[]);


int main(void)
{
    srand(time(NULL));

    ////names////
    //char* hero = "Hero";
    //char* enemy = "Villian";



    int choice = 0;
    //int turn = 0;

    while(!is_battle_over())
    {


        //int option = 0;

        print_status();

        //Hero's Turn
        choice = read_menu_choice();
        player_turn(choice);

        //Enemy's Turn


        

    }
    
    print_status();

    if(enemy_stats[0] <= 0)
    {
        printf("The enemy won!");
    }
    else
    {
        printf("The Hero won!");
    }
    
}

void print_status(void)
{
    printf("--- HERO: %d HP | Slime: %d HP ---\n", hero_stats[0], enemy_stats[0]);
}

int is_battle_over(void)
{
    int status = 0;
    if (hero_stats[0] <= 0 || enemy_stats[0] <= 0) status = 1;
    return status;
}

int read_menu_choice(void)
{
    int input = 0;
    int choice = 0;
    do
    {
        printf("Your Move: [1] Attack [2] Defend [3] Item\n");
        input = scanf("%i", &choice);

        if(input != 1)
        {
            int c;
            while ((c = getchar()) != '\n' && c != EOF){ }
            choice = 0;
        }
        

    } while (choice < 1 || choice > 3);
    
    return choice;
}

void player_turn(int choice)
{
    int dmg = 0;
    switch (choice)
    {
        case 1:
            dmg = calculate_attack(hero_stats, enemy_stats);
            enemy_stats[0] -= dmg;
            printf("Hero attacks for %d damage!\n", dmg);

            break;
        case 2:
            printf("Hero defends!\n");
            break;
        case 3:
            if (item < 0)
            {
                printf("Hero uses an item to heal!\n");
                hero_stats[0] += 100;
            }
            else if (item <= 0)
            {
                printf("Hero tried to use an item but doesn't have any more!\n");
                item = 0;
            }
            
            break;
        default:
            printf("Well something broke...\n");
            break;
    }
}

void enemy_turn(void)
{
    int dmg = calculate_attack(enemy_stats, hero_stats);
    hero_stats[0] -= dmg;
    printf("The enemy attacks for %d!\n", dmg);
}

///------------------------------------------//

int calculate_attack(int attacker[], int defender[])
{
    int base_dmg = roll_base_damage(attacker[0],defender[0]);
    int attacker_crit = attacker[3];
    int var_dmg = apply_variance(base_dmg);
    float element_dmg = elemental_multiplier();

    if (element_dmg == 2.0)
    {
        var_dmg *= 2;
        //printf("Elemental advantage! Damage increased.\n");
    }
    else if (element_dmg == 0.5)
    {
        var_dmg /= 2;
        //printf("Elemental disadvantage! Damage reduced.\n");
    }

    if (var_dmg <= 0) var_dmg = 1;

    return var_dmg;
}

int roll_base_damage(int attack, int defense)
{
    int result = attack - defense;

    if (attack - defense < 1) result = 1;

    return result;
}

int apply_variance(int damage)
{
    //printf("Base damage is %d\n", damage);
    int percent;
    do
    {
        percent = rand() % 100;
    } while (percent > 15 || percent < 1);

    //printf("Percent modifier is %d\n", percent);
    
    float percent_of_damage = (damage * percent) / 100.0f;
    //printf("%d percent of %i is %f\n", percent, damage, percent_of_damage);

    int flip_num = rand() % 100;

    int result = 0;
    if (flip_num % 2 == 0)
    {
        result = damage + percent_of_damage;
        //printf("damage percent is positive\n");
    }
    else{
        result = damage - percent_of_damage;
        //printf("damage percent is negative\n");
    }
    
    if(result < 1) result = 1;
    //printf("The resulting attack damage is  %d\n", result);

    return result;
}

int is_critical(int crit_chance_percent)
{
    int crit;
    int check = (rand() % 100) + 1;
    if(check <= crit_chance_percent)
    {
        crit = 1;
        //printf("A critical hit!\n");
    }
    else
    {
        crit = 0;
    }

    return crit;
}

float elemental_multiplier(void)
{
    float didItHit = 1.0;
    int atk_el = (rand() % 4) + 1;
    int def_el = (rand() % 4) + 1;

    if ((atk_el % 4) +1 == def_el) didItHit = 2.0;
    else if ((def_el % 4) + 1 == atk_el) didItHit = 0.5;

    return didItHit;
    
}