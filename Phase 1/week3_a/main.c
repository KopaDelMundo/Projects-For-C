//complete

#include <stdio.h> 
#include <string.h>

void inv_add(char names[][32], int *count, const char *name); //appends(adds) if room
void inv_remove(char names[][32], int *count, int index); //removes at index by shifting later items down
void inv_list(char names[][32], int count); //prints item list
int read_menu_choice(void);


int main(void)
{
    int count = 2;
    char inventory[10][32] = {
        {'P','o','t','i','o','n'},
        {'E','l','i','x','i','r'}
    };
    
    int choice = 0;
    char item[32];
    int getitout;
    do
    {
        inv_list(inventory, count);
        choice = read_menu_choice();
        switch(choice)
        {
            case 1:

                printf("Enter item name (32 character limit): \n");
                fgets(item, sizeof(item), stdin);
                item[strcspn(item, "\n")] = '\0';
                inv_add(inventory, &count, item);
                break;
            case 2:
                printf("Enter index to remove: \n");
                scanf("%d", &getitout);
                inv_remove(inventory, &count, getitout);
                break;
            default:
                break;      
        }
    } while (choice != 3);
    

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

    int c;
    while ((c = getchar()) != '\n' && c != EOF); 
    
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