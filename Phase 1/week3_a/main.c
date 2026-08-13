//TODO: Wrap all functions into a loop that takes inputß

#include <stdio.h> 
#include <string.h>

void inv_add(char names[][32], int *count, const char *name); //appends(adds) if room
void inv_remove(char names[][32], int *count, int index); //removes at index by shifting later items down
void inv_list(char names[][32], int count); //prints item list
int read_menu_choice(void);
void handle_input(int choice);
char* handle_string(void);

int main(void)
{
    int count = 2;
    char inventory[10][32] = {
        {'P','o','t','i','o','n'},
        {'E','l','i','x','i','r'}
    };
    
    int choice = 0;
    

    do
    {
        inv_list(inventory, count);
        choice = read_menu_choice();
        void handle_input(choice);

    } while (choice != 3);
    

}

char* handle_string(void)
{
    char item[32] = "";
    int input = scanf("%s", item);
    
    return item;
}

void handle_input(int choice)
{
    switch (choice)
    {
        case 1:


    }
}

int read_menu_choice(void)
{
    int input = 0;
    int choice = 0;
    do
    {
        printf("Enter 1 to add an item, 2 to remove an item, or 3 to quit.\n");
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
    int amount = *count - 1;
    for (int i = index; i < amount; i++)
    {
        if(i != amount)
        {
            strcpy(names[i], names[i+1]);
        }
    }

    *count -= 1;
}