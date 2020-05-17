#include "container.h"
#include <stdlib.h>
#include <string.h>

struct container* create_container(struct container* first, enum container_type type, void* entry){
    if(entry == NULL) return NULL;
    struct container *ptr = first;
    struct container *new = calloc(1, sizeof(struct container));
    if(first != NULL){
        while(ptr->next != NULL){
            if(ptr->type == EVENT){
                if(ptr->event->name == ((struct event*)entry)->name) return NULL;
            }
            ptr = ptr->next;
        }
        ptr = ptr->next = new;
    } else {
        ptr = first = new;
    }
    ptr->type = type;
    switch(type){
        case ROOM:
            ptr->room = entry;
            break;
        case COMMAND:
            ptr->command = entry;
            break;
        case ITEM:
            ptr->item = entry;
            break;
        case TEXT:
            ptr->text = entry;
            break;
        case EVENT:
            ptr->event = entry;
            break;
    }
    return first;
}

struct container* destroy_containers(struct container* first){
    if(first == NULL) return NULL;
    struct container *next;
    while(first->next != NULL){
        next = first->next;
        switch(first->type){
            case ITEM:
                destroy_item(first->item);
                break;
            case ROOM:
                destroy_room(first->room);
                break;
            case COMMAND:
                destroy_command(first->command);
                break;
            case TEXT:
                free(first->text);
                break;
            case EVENT:
                destroy_event(first->event);
                break;
        }
        free(first);
        first = next;
    }
    return NULL;
}

void* get_from_container_by_name(struct container *first, const char *name){
    if(first == NULL || name == NULL || strlen(name) == 0) return NULL;
    while(first != NULL){
        switch(first->type){
            case ROOM:
                if(strcasecmp(first->room->name, name) == 0)
                    return first->room;
                break;                
            case ITEM:
                if(strcasecmp(first->item->name, name) == 0)
                    return first->item;
                break;                
            case COMMAND:
                if(strcasecmp(first->command->name, name) == 0)
                    return first->command;
                break;                
            case TEXT:
                if(strcasecmp(first->text, name) == 0)
                    return first->text;
                break;
            case EVENT:
                if(strcasecmp(first->event->name, name) == 0)
                    return first->event;
                break;        
        }
        first = first->next;
    }
    return NULL;
}

struct container* remove_container(struct container *first, void *entry){
    if(first == NULL || entry == NULL) return first;
    struct container *ptr, *ptr_prev;
    if(first->text == entry){
        ptr = first->next;
        free(first);
        return ptr;
    } else {
        ptr = first->next;
        ptr_prev = first;
        while(ptr != NULL){
            if(ptr->text == entry){
                ptr_prev->next = ptr->next;
                free(ptr);
                return first;
            }
            ptr_prev = ptr;
            ptr = ptr->next;
        }
    }
    return first;
}