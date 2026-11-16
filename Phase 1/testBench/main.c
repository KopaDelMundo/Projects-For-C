#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define TOK_BUFSIZE 64
#define TOK_DELIM " \t\r\n\a"

char* get_input(void)
{
    char* line = NULL;
    size_t bufsize = 0;
    ssize_t nread = 0;

    do
    {
        printf("Enter Command: \n");
        nread = getline(&line, &bufsize, stdin);

        if(nread == -1)
        {
            free(line);
            return NULL;
        }

    } while (nread <= 1); 
    return line;  
}

char **split_line(char *line)
{
    int bufsize = TOK_BUFSIZE;
    int position = 0;
    char **tokens = malloc(sizeof(char) *bufsize);
    char *token;

    if(!tokens) 
    {
        printf("split_line: It's broken (on malloc)!\n");
        return NULL;
    }

    token = strtok(line, TOK_DELIM);
    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        if(position >= bufsize)
        {
            bufsize += TOK_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if(!tokens) 
            {
                printf("split_line: It's broken (on realloc)!\n");
                return NULL;
            }
        }
        token = strtok(NULL, TOK_DELIM);
    }

    tokens[position] = NULL;
    return tokens;

}

int main(void)
{
    char* line = NULL;
    char** args = NULL;

    line = get_input();
    args = split_line(line);

    while(*args != NULL)
    {
        printf("%s\n", *args);
        args++;
    }
    

    return 0;
}
