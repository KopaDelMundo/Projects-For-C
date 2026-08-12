#include <stdio.h> 
#include <string.h>

void inv_add(char names[][32], int *count, const char *name); //appends(adds) if room
void inv_remove(char names[][32], int *count, int index); //removes at index by shifting later items down
void inv_list(char names[][32], int count); //prints item list


int main(void)
{
    int count = 2;
    char inventory[10][32] = {
        {'P','o','t','i','o','n'},
        {'E','l','i','x','i','r'}
    };
    
    
    inv_list(inventory, count);
    inv_add(inventory, &count, "Poison");
    inv_list(inventory, count);
    inv_remove(inventory, &count, 1);





}



void inv_list(char names[][32], int count)
{
    printf("Item Count: %d\n", count);
    for(int i = 0; i < count; i++)
    {
        if(names[i][0] != '\0') printf("%s\n", names[i]);
        //else printf("Empty Slot\n");
    }
}

void inv_add(char names[][32], int *count, const char *name)
{
    int length = strlen(name);

    int spot = *count;
    for(int i = 0; i < length; i++)
    {
        names[spot][i] = name[i];
    }
        
    *count += 1;
}   

void inv_remove(char names[][32], int *count, int index)
{
    int dif =  
    for(int i = 0; i )
}