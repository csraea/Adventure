#include "room.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct room* create_room(char *name, char *description){
    if(name == NULL || description == NULL || strlen(name) == 0 || strlen(description) == 0) return NULL;
    struct room *new = calloc(1, sizeof(struct room));
    new->name = name;
    new->description = description;
    return new;
}

void set_exits_from_room(struct room *room, struct room *north, struct room *south, struct room *east, struct room *west, struct room *up, struct room *down){
    if(room == NULL) return;
    room->north = north;
    room->south = south;
    room->east = east;
    room->west = west;
    room->up = up;
    room->down = down;
}

struct room* destroy_room(struct room* room){
    if(room == NULL) return NULL;
    if(room->north != NULL){
        room->north->south = NULL;
        room->north = NULL;
    }
    if(room->south != NULL){
        room->south->north = NULL;
        room->south = NULL;
    }
    if(room->east != NULL){
        room->east->west = NULL;
        room->east = NULL;
    }
    if(room->west != NULL){
        room->west->east = NULL;
        room->west = NULL;
    }
    if(room->up != NULL){
        room->up->down = NULL;
        room->up = NULL;
    }
    if(room->down != NULL){
        room->down->up = NULL;
        room->down = NULL;
    }
    destroy_containers(room->items);
    free(room);
    return NULL;
}

void show_room(const struct room* room){
    if(room == NULL) return;
    printf("\t-== %s ==-\n", room->name);
    printf("Possible exits from room:\n");
    if(room->north != NULL) printf("\t-> North\n");
    if(room->south != NULL) printf("\t-> South\n");
    if(room->east != NULL)  printf("\t-> East\n");
    if(room->west != NULL)  printf("\t-> West\n");
    if(room->up != NULL) printf("\t-> Up\n");
    if(room->down != NULL) printf("\t-> Down\n");
}

void add_item_to_room(struct room* room, struct item* item){
    if(room == NULL || item == NULL) return;
    room->items = create_container(room->items, ITEM, item);
}

struct item* get_item_from_room(const struct room* room, const char* name){
    if(room == NULL || name == NULL || strlen(name) == 0) return NULL;
    return get_from_container_by_name(room->items, name);
}

void delete_item_from_room(struct room* room, struct item* item){
    if(room == NULL || item == NULL || room->items == NULL) return;
    room->items = remove_container(room->items, item);
}

void add_person_to_room(struct room* room, struct person* person){
    if(room == NULL) return;
    room->person = person;
}