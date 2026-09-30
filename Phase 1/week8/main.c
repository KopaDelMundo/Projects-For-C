#include <stdio.h>
#include "entity.h"
#include "dynarray.h"



typedef struct {
    char* playerName;
} Player;

int save_game(const char *path, const DynArray *entities, Player *p);   //writes a human readable textfile (one entity per lineL state, hp, x, y...) returns success/fail
int load_game(const char *path, DynArray *entities, Player *p);         //parses it back, rebuilding the array. Round trip must be loseless.
//int read_file(const char* path);                                        //reads file to view contents of save

int main(void)
{
    Player p1 = {"Xeno Humphrey"};
    DynArray dy1;
    da_init(&dy1);

    Entity e1 =     { 1 };
    Entity e2 =     { 2 };
    Entity e3 =     { 3 };
    Entity e4 =     { 4 };
    Entity e5 =     { 5 };
    da_push(&dy1, &e1);
    da_push(&dy1, &e2);
    da_push(&dy1, &e3);
    da_push(&dy1, &e4);
    da_push(&dy1, &e5);
    
    //int save_status;
    //int read_status;
    save_game("save.txt", &dy1, &p1);
    //read_status = read_file("save.txt");
}

int save_game(const char *path, const DynArray *entities, Player *p)
{
    FILE* fp = fopen(path, "w");
    fprintf(fp, "The items of player %s:\n", p->playerName);

    for(int i = 0; i < entities->count; i++)
    {
        fprintf(fp, "Item Name: %s ||| Entity ID: %d\n", entities->items[i].itemName,entities->items[i].itemNum);
    }

    fclose(fp);
    return 1;
}

int load_game(const char *path, DynArray *entites, Player *p)
{
    da_clear(entites);
    FILE* fp;
    char name[1024]; 
    int id;

    fp = fopen("save.txt", "r");
    while(fscanf(fp, "%s %d", name, &id) != EOF)
    {
        
    }

}