#include <stdio.h>

typedef enum {
    EVENTONE,
    EVENTTWO
} EventKind;

typedef struct Event {
    EventKind kind;
    int ticks_remaining;
    Event *next;
} Event;

typedef struct {
    Event *list_head; 
} EventQ;

typedef struct testNode {
    int value;
    struct testNode *next;
} testNode;

void event_schedule(EventQ *q, int delay, EventKind kind); //inserts a node
void event_tick(EventQ *q); //decrements all, fires + removes those hitting 0;
void print_event(EventQ *q);
Event *insert_at_event_head(Event)

//THINGS TO DO:
//add node
//remove node (under conditions)

int main(void)
{
    EventQ event_list = { NULL };
    Event *tmp;

    

}

void event_schedule(EventQ *q, int delay, EventKind kind)
{
    Event *result = malloc(sizeof(Event));
    result->kind = kind;
    result->ticks_remaining = delay;
    result->next = NULL;
    return result;
}

void print_event(EventQ *q)
{
    Event *temp = q;
    while (temp != NULL)
    {
        printf("Ticks remaining: %d | EventKind: %d", temp->ticks_remaining, temp->kind);
        temp = temp->next;
    }
}