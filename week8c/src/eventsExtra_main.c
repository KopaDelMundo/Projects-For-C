#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "events.h"

#define RL_BUFSIZE 1024
#define TOK_BUFSIZE 64
#define TOK_DELIM " \t\r\n\a"

//context for event queue
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

//---function prototypes---//
//reading/token functions
char *read_line(void);
char **split_line(char *line);
int run_cmd(char **args);
int lsh_num_builtins() 
{
  return sizeof(builtin_str) / sizeof(char *);
}
//commands
int t(char** args);
int s(char** args);
int l(char** args);
int q(char** args);
//game logic
static void on_event(EventKind kind, int arg, void *ctx);

int (*builtin_func[]) (char **) = {
    &t,
    &s,
    &l,
    &q
};

int main(void)
{
    //create event queue and context for ticks/events
    EventQueue events;
    event_queue_init(&events);
    EventsCtx context = { &events, 0 };
    EventHandler handler = on_event;

    char *line;
    char **args;
    int status;
    

    do {
        printf("> ");
        line = read_line();
        args = split_line(line);
        status = run_cmd(args);

        free(line);
        free(args);
    }while(status);

}

char *read_line(void)
{
    int bufsize = RL_BUFSIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char) * bufsize);
    int c;

    if(!buffer)
    {
        fprintf(stderr, "allocation error\n");
        exit(EXIT_FAILURE);
    }

    while(1)
    {
        //read a character
        c = getchar();

        //if we hit EOF, replace it with a null char and return
        if(c == EOF || c == '\n')
        {
            buffer[position] = '\0';
            return buffer;
        }
        else
        {
            buffer[position] = c;
        }
        position++;

        //if we exceed the buffer...
        if (position >= bufsize)
        {
            bufsize += RL_BUFSIZE;
            buffer = realloc(buffer, bufsize);
            if(!buffer)
            {
                fprintf(stderr, "lsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

char **split_line(char *line)
{
    int bufsize = TOK_BUFSIZE;
    int position = 0;
    char **tokens = malloc(sizeof(char) * bufsize);
    char *token;

    if(!tokens) {
        fprintf (stderr, "allocation error");
        exit(EXIT_FAILURE);
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
            if (!tokens)
            {
                fprintf(stderr, "allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, TOK_BUFSIZE);
    }

    tokens[position] = NULL;
    return tokens;
}

int rum_cmd(char **args)
{
    if (args[0] == NULL)
    {
        //an empty cmd has been entered
        return 1;
    } 

    for(int i = 0; i < )
}