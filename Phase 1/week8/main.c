#include <stdio.h>
#include <string.h>
#include "entity.h"
#include "dynarray.h"

//TODO: Continue work on load_game()

typedef struct {
    char* playerName;
} Player;

int save_game(const char *path, const DynArray *entities);   //writes a human readable textfile (one entity per lineL state, hp, x, y...) returns success/fail
int load_game(const char *path, DynArray *entities);         //parses it back, rebuilding the array. Round trip must be loseless.
//int read_file(const char* path);                                        //reads file to view contents of save

int main(void)
{
    //Player p1 = {"Xeno Humphrey"};
    DynArray dy1;
    da_init(&dy1);


    
    //int save_status;
    //int read_status;
    load_game("save.txt", &dy1);
    //read_status = read_file("save.txt");
    print_DynArray(&dy1);


}

int save_game(const char *path, const DynArray *entities)
{
    FILE* fp = fopen(path, "w");
    //fprintf(fp, "The items of player %s:\n", p->playerName);

    for(int i = 0; i < entities->count; i++)
    {
        fprintf(fp, "%s %d\n", entities->items[i].itemName,entities->items[i].itemNum);
    }

    fclose(fp);
    return 1;
}

int load_game(const char *path, DynArray *entities)
{
    da_clear(entities);
    FILE* fp;
    char name[64]; 
    int id;
    int count = 0;

    fp = fopen(path, "r");
    while(fscanf(fp,"%s %d", name, &id) != EOF)
    {
        strncpy(entities->items[count].itemName, name, sizeof(entities->items[count].itemName) - 1);
        entities->items[count].itemNum = id;
        entities->count += 1;
        count++;
    }
    return 1;
}