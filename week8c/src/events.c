#include <stdlib.h>
#include <stdio.h>
#include "events.h"

void event_queue_init(EventQueue *q) //initialize linked list
{
    q->head = NULL;
    q->count = 0;
}

int event_schedule(EventQueue *q, int delay, EventKind kind, int arg)
{
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
    return 1;

} 

void event_count(const EventQueue *q)
{
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
}

int event_tick(EventQueue *q, EventHandler handler, void *ctx)
{
    Event *prev_event = NULL;
    Event *ptr = q->head;
    while(ptr != NULL)
    {

        if(ptr->ticks_remaining == 0)
        {
            //fire event here

            //free event node//
            //set the pointer to the previous event to point to one after ptr
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

const char *event_kind_name(EventKind k);