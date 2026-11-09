#include <stdlib.h>
#include <stdio.h>
#include "events.h"

void event_queue_init(EventQueue *q) //initialize linked list
{
    printf("||DEBUG: EVENT_QUEUE_INIT BEGINNING||\n");
    q->head = NULL;
    q->count = 0;
    printf("||DEBUG: EVENT_QUEUE_INIT DONE||\n");
}

int event_schedule(EventQueue *q, int delay, EventKind kind, int arg)
{
    printf("||DEBUG: EVENT_SCHEDULE BEGINNING||\n");
    Event *temp = malloc(sizeof(Event));
    if(temp == NULL)
    {
        printf("Allocation failed\n");
        return 0;
    }
    temp->ticks_remaining = delay;
    temp->kind = kind;
    temp->arg = arg;
    temp->next = NULL;

    temp->next = q->head;
    q->head = temp;
    q->count += 1;
    printf("||DEBUG: EVENT_SCHEDULE DONE||\n");
    return 1;

} 

void event_count(const EventQueue *q)
{
    printf("||DEBUG: EVENT_COUNT BEGINNING||\n");
    Event *temp = q->head;
    if(temp == NULL)
    {
        printf("Allocation failed\n");
        return;
    }
    printf("There are %d events pending:\n", q->count);
    while(temp != NULL)
    {
        printf("Event Kind: %d | Ticks Remaining: %d | Argument: %i |\n", temp->kind, temp->ticks_remaining, temp->arg);
        temp = temp->next;
    }
    printf("||DEBUG: EVENT_COUNT DONE||\n");
}

int event_tick(EventQueue *q, EventHandler handler, void *ctx)
{
    printf("||DEBUG: EVENT_TICK BEGINNING||\n");
    int amount_of_events_fired = 0;
    Event *prev_event = NULL;
    Event *ptr = q->head;
    while(ptr != NULL)
    {
        if(ptr->ticks_remaining == 0)
        {
            //fire event here and 
            handler(ptr->kind, ptr->arg, ctx);
            amount_of_events_fired++;
            //free event node//
            //set the pointer to the previous event to point to one after ptr//
            prev_event->next = ptr->next;  
            free(ptr);
            ptr = prev_event->next;
        }
        else
        {
            prev_event = ptr;
            ptr = ptr->next;
        } 
    }
    printf("||DEBUG: EVENT_TICK DONE||\n");
    return amount_of_events_fired;
} 

void event_queue_free(EventQueue *q)
{
    Event *ptr = q->head;
    while(ptr != NULL)
    {
        Event *next = ptr->next;
        free(ptr);
        ptr = next;
    }
    printf("Linked list has been cleared\n");
} 

const char *event_kind_name(EventKind k)
{
    const char* stringToReturn;
    switch(k) {
        case EVENT_SPAWN_WAVE:
            stringToReturn = "SPAWN_WAVE";
            break;
        case EVENT_HEAL_PULSE:
            stringToReturn = "SPAWN_WAVE";
            break;
        case EVENT_MESSAGE:
            stringToReturn = "SPAWN_WAVE";
            break;
        case EVENT_COUNT:
            stringToReturn = "SPAWN_WAVE";
            break;
        default:
            stringToReturn = "Invalid, fix it now!!!";
            break;
    }

    return stringToReturn;
}