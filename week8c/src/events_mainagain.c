#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "events.h"

#define TOK_BUFSIZE 64
#define TOK_DELIM " \t\r\n\a"

typedef struct {
    EventQueue *q;
    int tick;
} EventsCtx;

char *builtin_str[] = {
    "t",
    "s",
    "l",
    "q"
};

int num_builtins(void) 
{
  return sizeof(builtin_str) / sizeof(char *);
}

char* get_input_from_user(void);
char **split_line(char *line);
int rum_cmd(char** args);
static void on_event(EventKind kind, int arg, void *ctx);

int main(void)
{
    //create event queue + context that wraps around it to track ticks and event handler assignment
    EventQueue events;
    event_queue_init(&events);
    EventsCtx ctx = { &events, 0 };
    EventHandler handler = on_event;
    char *line = NULL;
    char **args;
    
    while(1)
    {
    
        line = get_input_from_user();
        args = split_line(line);

        //get input
        //tokenize
        //select logic based off of token

        free(line);
        free(args);
    }

    
}

char* get_input_from_user(void)
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



int rum_cmd(char** args)
{
    if(args[0] == NULL)
    {
        printf("emty cmd, try again\n");
    }

    for (int i = 0; i < num_builtins; i++)
    {
        if(strcmp(args[0], builtin_str[i]) == 0)
        {
            return (*builtin_func[i](args));
        }
        
    }

    return 404;
}