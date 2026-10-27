#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "events.h"

//TODO:
//program must now schedule based off of manual input from user
/*
    currently:
    working on parse_cmd to get all nums out of the string and into an array
    -based off tokens returned and cmd letter, assign values to union members

    after:
    need to 
*/
typedef enum {
    TICK_INPUT,
    SCHEDULE_INPUT,
    CMD_TYPE_COUNT,
} cmd_type;

typedef struct {
    EventQueue *q; 
    int tick;
} EventsCtx;

typedef struct {
    int ticks;
} tick_cmd;

typedef struct {
    int delay; //(1-1000)
    EventKind kind; //(0-2)
    int arg;
} schedule_cmd;

typedef struct {
    char first_cmd;
    union {
        tick_cmd tick_input;
        schedule_cmd schedule_input;
    } data;

} command;

//static void on_event(EventKind kind, int arg, void *ctx);
int parse_cmd(const char* line, char numInputs[3][5]);
int is_NotEmpty(const char* input);

int main(void)
{
    //create event queue and context for ticks/events
    EventQueue events;
    event_queue_init(&events);
    EventsCtx context = { &events, 0 };

    //variables for set up
    char cmd_line[33];
    //char cmd_letter;
    char cmd_num_inputs[3][5];
    //int tokens = 0;
    
    //scheduling/handling
    
    
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
            
        switch (cmd_line[0])
        {
            case 't':
                parse_cmd(cmd_line, cmd_num_inputs);
                
                break;
            case 's':
                parse_cmd(cmd_line, cmd_num_inputs);
                break;
            case 'l':
                event_count(&events);
                break;
            case 'q':
                return 0;
                break;
            default:
                printf("?\n");
        }
    }

    event_schedule(&events, 3, EVENT_SPAWN_WAVE, 1);
    event_schedule(&events, 4, EVENT_HEAL_PULSE, 1);
    event_schedule(&events, 5, EVENT_MESSAGE, 1);

    
    //free queue at end
    event_queue_free(&events);
  
}

int parse_cmd(const char* line, char numInputs[3][5])
{
    int token_flag      = 0;
    int letter_len      = 0;
    int num_len1        = 0;
    int num_len2        = 0;
    int num_len3        = 0;
    int max_letter_len  = 1;
    int max_num_length  = 4;

    char letter = '\0';
    char* firstNum = numInputs[0];
    char* secondNum = numInputs[1];
    char* thirdNum = numInputs[2];

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
                letter = *line;
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

    *firstNum = '\0';
    *secondNum = '\0';
    *thirdNum = '\0';

    if(*firstNum != '\0') tokens++;
    if(*secondNum != '\0') tokens++;
    if(*thirdNum != '\0') tokens++;

    return tokens;

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

