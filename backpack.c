#include "backpack.h"
#include <stdlib.h>
#include <string.h>

struct backpack* create_backpack(const int capacity){
    struct backpack *new = calloc(1, sizeof(struct backpack));
    new->capacity = capacity;
    new->size = 0;
    new->items = NULL;
    return new;
}

struct backpack* destroy_backpack(struct backpack* backpack){
    if(backpack == NULL) return NULL;
    backpack->items = destroy_containers(backpack->items);
    free(backpack);
    return NULL;
}

bool add_item_to_backpack(struct backpack* backpack, struct item* item){
    if(backpack == NULL || item == NULL) return false;
    if(backpack->size >= backpack->capacity || MOVABLE != (item->properties & MOVABLE)){
        return false;
    } else {
        backpack->items = create_container(backpack->items, ITEM, item);
        backpack->size += 1;
    }
    return true;
}

void delete_item_from_backpack(struct backpack* backpack, struct item* item){
    if(backpack == NULL || item == NULL || backpack->size == 0) return;
    backpack->items = remove_container(backpack->items, item);
    backpack->size -= 1;
}

struct item* get_item_from_backpack(const struct backpack* backpack, char* name){
    if(backpack == NULL || name == NULL || strlen(name) == 0 || backpack->size == 0) return NULL;
    return get_from_container_by_name(backpack->items, name);
}