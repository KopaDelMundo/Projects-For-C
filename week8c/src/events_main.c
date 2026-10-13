#include <stdio.h>
#include "events.h"

int main(void)
{
    EventQueue events;
    event_queue_init(&events);
    event_schedule(&events, 3, EVENT_SPAWN_WAVE, 1);
    event_schedule(&events, 4, EVENT_HEAL_PULSE, 1);
    event_schedule(&events, 5, EVENT_MESSAGE, 1);

    event_count(&events);

    event_queue_free(&events);

}