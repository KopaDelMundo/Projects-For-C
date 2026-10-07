#include <stdio.h>

typedef enum {
    DOORCLOSE,
    DOOROPEN
} EventKind;

typedef struct Event{
    int ticks_remaining; 
    EventKind kind;
    Event *next;
} Event;

typedef struct {
    Event *head;
} EventQueue;

void event_schedule(EventQueue *q, int delay, EventKind kind); //inserts a node
void event_tick(EventQueue *q); //decrements all, fires + removes events hitting zero

int main(void)
{
    
}