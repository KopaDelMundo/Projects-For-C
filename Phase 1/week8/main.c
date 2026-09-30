#include <stdio.h>
#include "entity.h"
#include "dynarray.h"

typedef struct {
    char playerName[24];
} Player;

int save_game(const char *path, const DynArray *entities, Player *p); //writes a human readable textfile (one entity per lineL state, hp, x, y...) returns success/fail
int load_game(const char *path, DynArray *entities, Player *p); //parses it back, rebuilding the array. Round trip must be loseless.

int main(void)
{
    
}