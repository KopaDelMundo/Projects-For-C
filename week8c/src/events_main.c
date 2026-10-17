#include <stdio.h>
#include <string.h>
#include "events.h"

//TODO:
//program must now schedule based off of manual input from user

typedef struct {
    EventQueue *q; 
    int tick;
} EventsCtx;

typedef struct {
    int ticks;
} tick_cmd;

typedef struct {
    
}

typedef struct {
    char first_cmd;
    union {

    } data;

} command;

static void on_event(EventKind kind, int arg, void *ctx);

int main(void)
{
    //create event queue and context for ticks/events
    EventQueue events;
    event_queue_init(&events);
    EventsCtx context = { &events, 0 };

    //variables for set up
    char cmd_raw[33];
    
    //scheduling/handling
    
    
    while(1)
    {
        printf("Enter command argument: \n");
        fgets(cmd_raw, sizeof(cmd_raw), stdin);
        if(strchr(cmd_raw, '\n' == NULL))
        {
            int c;
            while((c = getchar()) != '\n' && c != EOF) {};
            printf("Your cmd was too long. Get it together >:(\n");
        }
        cmd_raw[strcspn(cmd_raw, "\n")] = '\0';
    }

    event_schedule(&events, 3, EVENT_SPAWN_WAVE, 1);
    event_schedule(&events, 4, EVENT_HEAL_PULSE, 1);
    event_schedule(&events, 5, EVENT_MESSAGE, 1);

    
    //free queue at end
    event_queue_free(&events);
  
}

int parse_input(const char* line)
{
    char cmd_char[] = {'t', 's,', 'l', 'q'};

}
