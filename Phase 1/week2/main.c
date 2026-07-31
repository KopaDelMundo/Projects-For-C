#include <stdio.h>

void print_status(int hero_hp, int enemy_hp);
int is_battle_over(int hero_hp, int enemy_hp);
int read_menu_choice(void);

int main(void)
{
    int hero_hp = 100;
    int enemy_hp = 100;

    while(!is_battle_over(hero_hp, enemy_hp))
    {
        print_status(hero_hp, enemy_hp);
        read_menu_choice();

        enemy_hp -= 25;

    }
    
    print_status(hero_hp, enemy_hp);
    
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
    int input;
    do
    {
        printf("Your Move: [1] Attack [2] Defend [3] Item\n");
        scanf("%d", input);
    } while (input != 1 || input != 2 || input != 3);
    

}