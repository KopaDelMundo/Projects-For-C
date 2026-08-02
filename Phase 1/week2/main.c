//scaffolding for game loop and functions done
//TODO: add combat logic from last project, while adding improvements

#include <stdio.h>

void print_status(int hero_hp, int enemy_hp);
int is_battle_over(int hero_hp, int enemy_hp);
int read_menu_choice(void);
void player_turn(int choice);
void enemy_turn(void);


int main(void)
{
    int hero_hp  = 100;
    int enemy_hp = 100;
    int choice = 0;

    while(!is_battle_over(hero_hp, enemy_hp))
    {
        print_status(hero_hp, enemy_hp);
        choice = read_menu_choice();
        player_turn(choice);

        enemy_hp -= 25;

    }
    
    print_status(hero_hp, enemy_hp);

    if(enemy_hp <= 0)
    {
        printf("The enemy won!");
    }
    else
    {
        printf("The Hero won!");
    }
    
}

void print_status(int hero_hp, int enemy_hp)
{
    printf("--- HERO: %d HP | Slime: %d HP ---\n", hero_hp, enemy_hp);
}

int is_battle_over(int hero_hp, int enemy_hp)
{
    int status = 0;
    if (hero_hp <= 0 || enemy_hp <= 0) status = 1;
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
    switch (choice)
    {
        case 1:
            printf("Hero attacks!\n");
            break;
        case 2:
            printf("Hero defends!\n");
            break;
        case 3:
            printf("Hero uses an item!\n");
            break;
        default:
            printf("Well something broke...\n");
            break;
    }
}

void enemy_turn(void)
{
    printf("The enemy attacks!\n");
}