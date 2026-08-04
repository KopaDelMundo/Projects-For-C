# Week 2 -- Turn Based Battle Loop
    A small terminal program to simulate a turnbased RPG battle.
    Using slighly updated battle logic from the previous project,
    the player can fight an enemy by attacking, defending, or healing
    with an item. 

## Build
    clang -Wall -Wextra -g -Wstrict-prototypes -o main main.c

## Run
    ./main

###sample output
    --- HERO: 1000 HP | Slime: 1000 HP ---
    Your Move: [1] Attack [2] Defend [3] Item
    1
    Hero attacks for 201 damage!
    The enemy attacks for 336!
    --- HERO: 664 HP | Slime: 799 HP ---
    Your Move: [1] Attack [2] Defend [3] Item
    2
    Hero defends!
    The enemy attacks for 84!
    --- HERO: 580 HP | Slime: 799 HP ---
    Your Move: [1] Attack [2] Defend [3] Item
    3
    Hero uses an item to heal!
    The enemy attacks for 135!
    --- HERO: 745 HP | Slime: 799 HP ---
    Your Move: [1] Attack [2] Defend [3] Item