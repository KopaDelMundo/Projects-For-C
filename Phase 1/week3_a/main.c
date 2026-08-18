//complete

#include <stdio.h> 
#include <string.h>

int inv_add(char names[][32], int *count, const char *name); //appends(adds) if room
int inv_remove(char names[][32], int *count, int index); //removes at index by shifting later items down
void inv_list(char names[][32], int count); //prints item list
int read_menu_choice(void);


int main(void)
{
    int count = 2;
    char inventory[10][32] = {
        {'P','o','t','i','o','n'},
        {'E','l','i','x','i','r'}
    };
    
    int add_check;
    int rmv_check;
    int choice = 0;
    char item[32];
    int getitout;
    int scancheck;
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
                add_check = inv_add(inventory, &count, item);
                if(add_check == 0) printf("Looks like your inventory is full!\n");
                break;
            case 2:
                printf("Enter index to remove (0-9 index): \n");
                scancheck = scanf("%d", &getitout); 
                if(scancheck != 1)
                {
                    printf("Index input wasn't valid\n");
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF) { }
                }
                else
                {
                    rmv_check = inv_remove(inventory, &count, getitout);
                    if(rmv_check == 0) printf("Not a valid removal index.\n");
                }
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

int inv_add(char names[][32], int *count, const char *name)
{
    int isitfull = 1;
    int length = strlen(name);

    int spot = *count;
    if(spot == 10)
    {
        isitfull = 0;
    }
    else
    {
        for(int i = 0; i < length; i++)
        {
            names[spot][i] = name[i];
        }
        names[spot][length] = '\0';
        *count += 1;
    }
    return isitfull;
}   

int inv_remove(char names[][32], int *count, int index)
{
    int validIndex = 1;
    int spot = *count;

    if(index > (spot - 1) || index < 0)
    {
        validIndex = 0;
    }
    else
    {
        int amount = *count - 1;
        for (int i = index; i < amount; i++)
        {
            strcpy(names[i], names[i+1]);
        }

        *count -= 1;
    }

    return validIndex;
}