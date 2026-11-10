#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "events.h"

#define CMD_MAX 18
#define MAX_TOKENS 4
#define MAX_LEN 5

//TODO:
/*
    currently:
    ticks increasing functionality needs to be set up [Need to test]

    basic onEvent printing is complete. Need to figure out how to get heal pulse
    to schedule multiple events based on the arg

    need to ensure 'q' exits program without issue [DONE]

    after:
    run program to look for bugs / other problems

*/

//context for the event queue
typedef struct {
    EventQueue *q; 
    int tick;
} EventsCtx;

int parse_cmd(const char* line, char inputs[4][5], int nums[3]);
int is_NotEmpty(const char* input);
static void on_event(EventKind kind, int arg, void *ctx);

int main(void)
{
    //create event queue and context for ticks/events
    EventQueue events;
    event_queue_init(&events);
    EventsCtx context = { &events, 0 };
    EventHandler handler = on_event;

    //variables for set up
    int quit_flag                           = 0;
    int tokens                              = 0;
    char cmd_line[CMD_MAX]                  = {0};
    char cmd_tokens[MAX_TOKENS][MAX_LEN]    = {0};
    int num_inputs[3]                       = {0}; 
    //t N //s delay eventkind arg
    
    
    while(quit_flag == 0)
    {
        //get input within length of the char array, reject until input fits
        do 
        {
            printf("Enter command: \n");
            char* input_p = fgets(cmd_line, sizeof(cmd_line), stdin);
            if(input_p != NULL)
            {
                if(strchr(cmd_line, '\n') == NULL)
                {
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF) {};
                    printf("Your cmd was too long, try something shorter.\n");
                }
            }
            else
            {
                printf("Input Ended.\n");
                return 0;
            }
        } while (strchr(cmd_line, '\n') == NULL);

        cmd_line[strcspn(cmd_line, "\n")] = '\0';

        printf("||DEBUG: INPUT IS WITHIN ACCEPTABLE LENGTH\n");
        //input is within length parameters, now cmd must be parsed
        tokens = parse_cmd(cmd_line, cmd_tokens, num_inputs); //use this to verify input later

        //respond to cmd line
        switch (cmd_tokens[0][0])
        {
            case 't':
                if(tokens <= 2)
                {
                    int loop_count = 0;
                    if(tokens == 2)
                    {
                        loop_count = num_inputs[0];
                    }
                    else
                    {
                        loop_count = 1;
                    }
                    for(int i = 0; i < loop_count; i++)
                    {
                        context.tick += 1;
                        event_tick(&events, handler, &context);
                    }  
                }
                else
                {
                    printf("Not a valid cmd, try again.\n");
                }
                break;
            case 's':
                if(tokens == 4)
                {
                    event_schedule(&events, num_inputs[0], num_inputs[1], num_inputs[2]);
                }
                else
                {
                    printf("Not a valid cmd, try again.\n");
                } 
                break;
            case 'l':
                event_count(&events);
                break;
            case 'q':
                printf("Goodbye\n");
                quit_flag = 1;
                break;
            default:
                printf("Looks like something went wrong...\n");
                break;
        }
        
    }
    
    //free queue at end
    event_queue_free(&events);
  

}

int parse_cmd(const char* line, char inputs[4][5], int nums[3])
{
    int tokens = 0;
    if(!is_NotEmpty(line)) return tokens;

   

    return tokens;

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

int is_NotEmpty(const char* input) 
{
    if(input == NULL) return 0;

    while(*input != '\0')
    {
        if(!isspace((unsigned char)*input))
        {
            break;
        }

        input++;
    }

    if(*input == '\0')
    {
        return 0;
    }
  
    return 1;
}