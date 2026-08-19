#include <stdio.h>
#include <string.h>

#define ROWS 7
#define COLS 12


void draw_map(char map[ROWS][COLS], int player_row, int player_col);
int try_move(char map[ROWS][COLS], int *row, int *col, char dir);
char get_dir(void);

int main(void)
{
    int player_row = 1;
    int player_col = 1;
    int move_success = 1;
    char direction;




    char map3[ROWS][COLS] = 
    {
        {'#','#','#','#','#','#','#','#','#','#','#','#'},
        {'#','.','.','.','.','#','.','.','.','.','.','#'},
        {'#','#','#','#','.','#','.','#','#','#','.','#'},
        {'#','.','.','.','.','#','.','#','.','.','.','#'},
        {'#','.','#','#','#','#','.','#','.','#','#','#'},
        {'#','.','.','.','.','.','.','.','.','#','.','#'},
        {'#','#','#','#','#','#','#','#','#','#','#','#'}
    };

    draw_map(map3, player_row, player_col);

    do
    {

        direction = get_dir();
        move_success = try_move(map3, &player_row, &player_col, direction);
        if(move_success == 1)
        {
            draw_map(map3, player_row, player_col);
        }

    } while (direction != 'q');
    



}

void draw_map(char map[ROWS][COLS], int player_row, int player_col)
{
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
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

int try_move(char map[ROWS][COLS], int *row, int *col, char dir) 
{
    int success = 0;
    switch(dir)
    {
        case 'w':
            if ((*row-1) >= 0 && map[*row-1][*col] == '.')
            {
                *row -= 1;
                success = 1;
            }
            else
            {
                printf("WALL IN WAY\n");
            }
            break;
        case 'a':
            if ((*col-1) >= 0 && map[*row][*col-1] == '.')
            {
                *col -= 1;
                success = 1;
            }
            else
            {
                printf("WALL IN WAY\n");
            }
            break;
        case 's':
            if ((*row+1) < ROWS && map[*row+1][*col] == '.' )
            {
                *row += 1;
                success = 1;
            }
            else
            {
                printf("WALL IN WAY\n");
            }
            break;
        case 'd':
            if ((*col+1) < COLS && map[*row][*col+1] == '.')
            {
                *col += 1;
                success = 1;
            }
            else
            {
                printf("WALL IN WAY\n");
            }
            break;
           case 'q':
            break; 
        default:
            printf("Unknown key\n");
    }
    return success;
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