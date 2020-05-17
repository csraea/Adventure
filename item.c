#include "item.h"
#include <stdlib.h>
#include <string.h>

struct item* create_item(char* name, char* description, unsigned int properties){
    if(name == NULL || description == NULL || strlen(name) == 0 || strlen(description) == 0) return NULL;
    struct item *new = calloc(1, sizeof(struct item));
    new->name = name;
    new->description = description;
    new->properties = properties;
    return new;
}

struct item* destroy_item(struct item* item){
    if(item == NULL) return NULL;
    free(item);
    return NULL;
}