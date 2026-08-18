// todo 
#include <stdio.h>
#include <string.h>

int rowz = 7;
int colz = 12;

void draw_map(char map[rowz][colz], int player_row, int player_col);
int try_move(char map[rowz][colz], int *row, int *col, char dir);
char get_dir(void);

int main(void)
{
    int player_row = 1;
    int player_col = 1;
    int wall_in_way = 1;
    char direction;




    char map3[7][12] = 
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
        if(wall_in_way == 1 && direction)
        {
            draw_map(map3, player_row, player_col);
        }
        direction = get_dir();
        wall_in_way = try_move(map3, &player_row, &player_col, direction);

    } while (direction != 'q');
    



}

void draw_map(char map[rowz][colz], int player_row, int player_col)
{
    for(int i = 0; i < rowz; i++)
    {
        for(int j = 0; j < colz; j++)
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

int try_move(char map[rowz][colz], int *row, int *col, char dir)
{
    //int rowpos = *row;
    //int colpos = *col;
    int success = 0;
    switch(dir)
    {
        case 'w':
            if (map[*row-1][*col] == '.')
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
            if (map[*row][*col-1] == '.')
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
            if (map[*row+1][*col] == '.')
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
            if (map[*row][*col+1] == '.')
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
            printf("Looks like this broke somehow\n");
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