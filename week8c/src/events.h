#ifndef EVENTS_H
#define EVENTS_H

typedef enum {
    EVENT_SPAWN_WAVE,
    EVENT_HEAL_PULSE,
    EVENT_MESSAGE,
    EVENT_COUNT
} EventKind;

typedef struct Event {
    int ticks_remaining;
    EventKind kind;
    int arg;
    struct Event *next;
} Event;

typedef struct {
    Event *head; //Null when empty; nodes are heap-allocated and owned by the queue
    int count;
} EventQueue;

typedef struct {
    EventQueue *q; 
    int tick;
} EventsCtx;

typedef void (*EventHandler) (EventKind kind, int arg, void *ctx);

void event_queue_init(EventQueue *q); // empty
int event_schedule(EventQueue *q, int delay, EventKind kind, int arg); /*appends a new node at the tail (so list order is scheduling order). 
A delay below 1 is treated as 1. Returns 1, or 0 if allocation fails*/ 
int event_tick(EventQueue *q, EventHandler handler, void *ctx); //every event present at the start of the call is decreased by one 
void event_count(const EventQueue *q); //pending events
const char *event_kind_name(EventKind k); //"SPAWN_WAVE", "HEAL_PULSE", "MESSAGE", OR "?"
void event_queue_free(EventQueue *q); //frees every node back to init state; safe twice

#endif