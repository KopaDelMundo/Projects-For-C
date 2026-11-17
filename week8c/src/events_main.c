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

char* get_input_from_user(void);
char **split_line(char *line);
void run_cmd(char** args, EventQueue *q, EventHandler h, EventsCtx *ctx);
static void on_event(EventKind kind, int arg, void *ctx);


int main(void)
{
    //create event queue + context that wraps around it to track ticks and event handler assignment
    EventQueue events;
    event_queue_init(&events);
    EventsCtx ctx = { &events, 0 };
    EventHandler handler = &on_event;
    char *line = NULL;
    char **args;
    //int status;
    
    while(1)
    {
    
        line = get_input_from_user();
        args = split_line(line);
        run_cmd(args, &events, handler, &ctx);



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

void run_cmd(char** args, EventQueue *q, EventHandler h, EventsCtx *ctx)
{

    char *endptr;

    if(args[0] == NULL)
    {
        printf("empty cmd, try again\n");

    }

    switch(args[0][0])
    {
        case 't':;
            int n = 0;
            if (args[1] == NULL)
            {
                n = 0;
            }
            else
            {
                n = (int)strtol(args[1], &endptr, 10);
            }
                for(int i = 0; i < n; i++)
                {
                    ctx->tick += 1;
                    event_tick(q, h, ctx);
                }
            break;
        case 's':
            if (args[1] == NULL || args[2] == NULL || args[3] == NULL)
            {
                printf("Missing arguments\n");
            }
            else
            {
                int delay = (int)strtol(args[1], &endptr, 10);
                int kind = (int)strtol(args[2], &endptr, 10);
                int arg = (int)strtol(args[2], &endptr, 10);
                event_schedule(q, delay, kind, arg);
            }
            break;
        case 'l':
            event_count(q);
            break;
        case 'q':
            printf("Goodbye\n");
            exit(EXIT_SUCCESS);
            break;
        default:
            printf("Error, args[0][0] doesn't match any letters!\n");
    }

}

static void on_event(EventKind kind, int arg, void *ctx)
{
    EventsCtx *c = ctx;

    switch(kind)
    {
        case EVENT_SPAWN_WAVE:
            printf("Tick %d: SPAWN_WAVE(%d)\n", c->tick, arg);
            break;
        case EVENT_HEAL_PULSE:
            printf("Tick %d: HEAL_PULSE(%d)\n", c->tick, arg);
            break;
        case EVENT_MESSAGE:
            printf("Tick %d: MESSAGE(%d)\n", c->tick, arg);
            break;
        default:
            printf("?\n");  
    }
}