#include <stdio.h>
#include <string.h>

//note, real max is 24, but I need space for \0
#define MAX_COL 26 
#define MAX_ROW 26

int load_level(const char *path, char m[MAX_ROW][MAX_COL], int lengthwidth[2]);
void draw_map(char map[MAX_ROW][MAX_COL], int player_row, int player_col, int lengthwidth[2]);
int try_move(char map[MAX_ROW][MAX_COL], int *row, int *col, char dir, int lengthwidth[2]);
char get_dir(void);


int main(void)
{
    //int player_row = 1;
    //int player_col = 1;
    //int move_success = 1;
    //char direction;

    char map[MAX_ROW][MAX_COL] = {0};
    char* path = "map1.txt";
    int rowcol[] = {0, 0};
    
    load_level(path, map, rowcol);

    for(int i = 0; i < rowcol[0]; i++)
    {
        for(int j = 0; j < rowcol[1]; j++)
        {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
    //draw_map(map, player_row, player_col, rowcol);

}

int load_level(const char *path, char m[MAX_ROW][MAX_COL], int lengthwidth[2])
{
    FILE* fp;
    char line[MAX_COL];
    int target_row = 0;
    int rows = 0;
    int cols = 0;

    fp = fopen(path, "r");

    while(fgets(line, sizeof line, fp) != NULL)
    {
        //printf("%s", line);
        line[strcspn(line, "\n")] = '\0';
        strncpy(m[target_row], line, MAX_COL-1);
        m[target_row][MAX_COL-1] = '\0';
        target_row++;
        rows++;
        cols = strcspn(line, "\n");
    }
    //cols = strcspn(line, "\n");
    printf("Rows:%d Cols:%d \n", rows, cols);
    
    lengthwidth[0] = rows;
    lengthwidth[1] = cols;

    fclose(fp);
    return 1;
  
}

void draw_map(char map[MAX_ROW][MAX_COL], int player_row, int player_col, int lengthwidth[2])
{
    for(int i = 0; i < lengthwidth[0]; i++)
    {
        for(int j = 0; j < lengthwidth[1]; j++)
        {
            if(i == player_row && j == player_col)
            {
                printf("@");
            }
            else
            {
                printf("%c", map[i][j]);
            }
        }
        printf("\n");
    }
}



char get_dir(void)
{
    char dir[4];
    do
    {
        printf("Enter w,a,s, or d and then enter to move in a direction, or q to quit:\n");
        fgets(dir, sizeof(dir), stdin);
        dir[strcspn(dir, "\n")] = '\0';
    } while (dir[0] != 'q' && dir[0] != 'w' && dir[0] != 'a' && dir[0] != 's' && dir[0] != 'd');

    return dir[0]; 
}