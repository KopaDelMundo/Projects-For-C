#include <stdio.h>
#include <string.h>

size_t my_strlen(const char* s);
void my_strcpy(char* dest, const char* b);
int my_strcmp(const char *a, const char *b);

int main(void)
{
    //my functions and results
    
    char* test = "Testing!"; // 8
    char copyDestTest[9];

    size_t stringLength = my_strlen(test);
    my_strcpy(copyDestTest, test);
    int cmp_dif = my_strcmp("cat", "dog");

    printf("The string length is %zu\n", stringLength);
    printf("copyDestTest is now: %s\n", copyDestTest);
    printf("The difference between the strings is: %d\n", cmp_dif);

    //c's functions and results

    char* test2 = "Testing!"; // 8
    char copyDestTest2[9];

    //my functions and results
    size_t stringLength2 = strlen(test2);
    strcpy(copyDestTest2, test2);
    int cmp_dif2= strcmp(test2, "Test");

    printf("The string length is %zu\n", stringLength2);
    printf("copyDestTest is now: %s\n", copyDestTest2);
    printf("The difference between the strings is: %d\n", cmp_dif2);

}

size_t my_strlen(const char* s)
{
    size_t length = 0;

    while(*s != '\0')
    {
        length++;
        s++;
    }

    return length;
}

void my_strcpy(char* dest, const char* b)
{
    while(*b != '\0')
    {
        *dest = *b;
        dest++;
        b++;
    }
    *dest = '\0';
}

int my_strcmp(const char* a, const char* b)
{
    while(*a == *b && *a != '\0')
    {
        a++;
        b++;
    }
    return *a - *b;
}
