#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "events.h"

//TODO:
/*
    currently:
    ticks increasing functionality needs to be set up

    basic onEvent printing is complete. Need to figure out how to get heal pulse
    to schedule multiple events based on the arg

    after:
    run program to look for bugs / other problems

*/


typedef struct {
    EventQueue *q; 
    int tick;
} EventsCtx;



//static void on_event(EventKind kind, int arg, void *ctx);
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
    int tokens = 0;
    char cmd_line[33]       = {0};
    char cmd_inputs[4][5]   = {0};
    int num_inputs[3]       = {0}; //t N //s delay eventkind arg
    
    
    while(1)
    {
        do //get input within length of the char array, reject until input fits
        {
            printf("Enter command: \n");
            char* input_p = fgets(cmd_line, sizeof(cmd_line), stdin);
            if(input_p != NULL)
            {
                if(strchr(cmd_line, '\n') == NULL)
                {
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF) {};
                    printf("Your cmd was too long.\n");
                }
            }
            else
            {
                printf("Input Ended.\n");
                return 0;
            }
        } while (strchr(cmd_line, '\n') == NULL);

        cmd_line[strcspn(cmd_line, "\n")] = '\0';

        //input is within length parameters, now cmd must be parsed
        tokens = parse_cmd(cmd_line, cmd_inputs, num_inputs); //use this to verify input later

        switch (cmd_inputs[0][0])
        {
            case 't':
                if(tokens < 2)
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
                    event_tick(&events, handler, &context);
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
                break;
            default:
                break;
        }    
        
    }
    
    //free queue at end
    event_queue_free(&events);
  

}

int parse_cmd(const char* line, char inputs[4][5], int nums[3])
{
    int token_flag      = 0;
    int letter_len      = 0;
    int num_len1        = 0;
    int num_len2        = 0;
    int num_len3        = 0;
    int max_letter_len  = 1;
    int max_num_length  = 4;

    char* letter    = inputs[0];
    char* firstNum  = inputs[1];
    char* secondNum = inputs[2];
    char* thirdNum  = inputs[3];

    int tokens = 0;

    if(!is_NotEmpty(line)) return tokens;

    while(*line != '\0')
    {
        if(!isspace(*line))
        {
            if(token_flag == 0)
            {
                token_flag = 1;
            }

            if(token_flag == 1 && letter_len < max_letter_len)
            {
                letter_len++;
                *letter = *line;
            } 
            else if(token_flag == 2 && num_len1 < max_num_length)
            {
                num_len1++;
                *firstNum = *line;
                firstNum++;
            }
            else if(token_flag == 3 && num_len2 < max_num_length)
            {
                num_len2++;
                *secondNum = *line;
                secondNum++;
            }
            else if(token_flag == 4 && num_len3 < max_num_length)
            {
                num_len3++;
                *thirdNum = *line;
                thirdNum++;
            }
        }
        else if(isspace(*line) && token_flag > 0)
        {
            token_flag++;
        }

        line++;
    }

    *letter     = '\0';
    *firstNum   = '\0';
    *secondNum  = '\0';
    *thirdNum   = '\0';

    if(*letter != '\0') tokens++;
    if(*firstNum != '\0') tokens++;
    if(*secondNum != '\0') tokens++;
    if(*thirdNum != '\0') tokens++;

    nums[0] = atoi(firstNum);
    nums[1] = atoi(secondNum);
    nums[2] = atoi(thirdNum);

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