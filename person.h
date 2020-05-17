#ifndef PERSON_H
#define PERSON_H

#include "item.h"
#include "room.h"
#include "backpack.h"
#include <stdlib.h>
#include <string.h>

#define DIALOG_SIZE 4

struct person {
    char* name;          
    char* description;        
    char* replic[4];
    struct item *item;
    struct event *event;
    struct room *location;
};

struct person *create_person(char *name, char *description, char *replic1, char *replic2, char *replic3, char *replic4, struct item *item, struct room *room);

struct person *kill_person(struct person *person);

struct person *interact(struct person *person, struct backpack *backpack);

#endif