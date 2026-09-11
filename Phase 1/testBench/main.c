#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int x;
    int y;
} Point;

int main(void)
{

    int length = 3;
    Point *array;
    array = malloc(sizeof(Point) * length);

    array[0].x = 1;
    array[0].y = 1;

    //free(array);

    length = 4;

    array = realloc(array, sizeof(Point) * length);

    array[3].x = 1;
    array[3].y = 1;

    free(array);
}
