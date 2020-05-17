#ifndef EVENT_H
#define EVENT_H

//#include "game.h"
#include "person.h"
#include "item.h"
#include "room.h"

enum event_type{
    LOCATION, NITEM, NEWPERSON, DEATH, SPECIAL
};

struct event{
    enum event_type type;
    char    *name;
    /*union{
        struct room *enteredLocation;
        struct item *itemFound;
        struct person *personFound;
        struct person *personKilled;
        unsigned special;
    };*/
};

struct event *create_event(struct game *game, enum event_type type, char *name);

struct event *destroy_event(struct event *event);

#endif