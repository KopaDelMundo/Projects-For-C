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

int event_tick(EventQueue *q, EventHandler handler, void *ctx); 

const char *event_kind_name(EventKind k);

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