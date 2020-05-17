#include "person.h"
#include "world.h"

struct person *create_person(char *name, char *description, char *replic1, char *replic2, char *replic3, char *replic4, struct item *item, struct room *room){
    if(name == NULL || description == NULL || room == NULL) return NULL;
    if(strlen(name) == 0 || strlen(description) == 0) return NULL;
    struct person *person = calloc(1, sizeof(struct person));
    person->name = name;
    person->description = description;
    person->replic[0] = replic1;
    person->replic[1] = replic2;
    person->replic[2] = replic3;
    person->replic[3] = replic4;
    person->item = item;
    person->location = room;
    return person;
}

struct person *kill_person(struct person *person){
    if(person == NULL) return NULL;
    free(person->name);
    free(person->replic);
    free(person->description);
    if(person->item != NULL) person->item = destroy_item(person->item);
    person->location = NULL;
    free(person);
    return NULL;
}

struct person *interact(struct person *person, struct backpack *backpack){
    
    return person;
}