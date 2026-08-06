#include <stdio.h> 

int inv_add(char names[][32], int *count, const char *name); //appends(adds) if room
int inv_remove(char names[][32], int *count, int index); //removes at index by shifting later items down
void inv_list(char *name[], int count); //prints item list
int check_index(char* index); //check if index is empty

int main(void)
{
    char* inventory[10] = {"Potion", "Gold Coin"};
    inv_list(inventory, 10);

    char* input = "";

    do
    {
        inv_list(inventory, 10);
    } while (input != "q" || input != "Q" );
    
    

}

int check_index(char* index)
{
    //returns 1 if empty, return 0 if not
    int isEmpty = 1;
    if (index != NULL) 
    {
        isEmpty = 0;
        //printf("Inventory slot is full\n");
    }
    else
    {
        //printf("Inventory slot is available\n");
    }

    return isEmpty;
}

void inv_list(char *name[], int count)
{
    for(int i = 0; i < count; i++)
    {
        if(name[i] != NULL) printf("%s\n", name[i]);
    }
}