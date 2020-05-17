#include "game.h"
#include "event.h"
#include <string.h>

struct event *create_event(struct game *game, enum event_type type, char *name){
    struct event *event = calloc(1, sizeof(struct event));
    switch(type){
        case LOCATION:
            event->name = game->current_room->name;
            break;
        case NEWPERSON:
            event->name = game->current_room->person->name;
            break;
        case DEATH:
            event->name = strcat("#", game->current_room->person->name);
            break;
        case NITEM:
            event->name = name;
            break;
        case SPECIAL:
            event->name = name;
            break;
    }
    return event;
}

struct event *destroy_event(struct event *event){
    free(event);
    return NULL;
}