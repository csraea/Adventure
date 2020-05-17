#include "person.h"
#include "world.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct container* create_world(){
    struct container *world = add_room_to_world(NULL, create_room("Road between Fog Mountains", "The old road that connects the River Valley with the neighboring province. The road runs into the ravine between the formidable gray rocks."));
    struct container *start = world;
    world = add_room_to_world(world, create_room("Old rope bridge", "The Old destroyed rope bridge over Tight Canyon. Road continues on the other side of canyon."));
    world = add_room_to_world(world, create_room("Arch of Humility", "Looks like an entry arch for travelers which is located in front of the ravine entry. "));
    world = add_room_to_world(world, create_room("Old cave", "Suspicious looking cave in a mountain."));
    world = add_room_to_world(world, create_room("Swamp", "Huge swamp with a musty smell. "));
    world = add_room_to_world(world, create_room("Semi-ruined castle", "An old castle with three defemsive towers. The left one is ruined, other two are in good condition. There is a ligth in the third floor of the central castle tower, bur the main door is locked."));
    world = add_room_to_world(world, create_room("Foggy Lake", "Enormous lake with mist over it's waters."));
    world = add_room_to_world(world, create_room("Wooden Pier", "Old wooden pier on the Foggy Lake coast. There is a small boat from the right side."));
    world = add_room_to_world(world, create_room("Small island", "A small island in the midlle of the lake. Lake is a very misterious place..."));
    world = add_room_to_world(world, create_room("Big island", "A big island in the midlle of the lake. Lake is a very misterious place..."));
    world = add_room_to_world(world, create_room("Medium island", "An island of medium size in the midlle of the lake. Lake is a very misterious place..."));
    // continue later

    set_exits_from_room(get_room(world, "Road between Fog Mountains"), get_room(start, "Arch of Humility"), get_room(start, "Old rope bridge"), NULL, NULL, NULL, NULL);
    set_exits_from_room(get_room(world, "Old rope bridge"), get_room(start, "Road between Fog Mountains"), NULL, NULL, NULL, NULL, NULL);
    set_exits_from_room(get_room(world, "Arch of Humility"), get_room(start, "Semi-ruined castle"), get_room(start, "Road between Fog Mountains"), NULL, get_room(start, "Old cave"), NULL, NULL);
    set_exits_from_room(get_room(world, "Road between Fog Mountains"), get_room(start, "Arch of Humility"), get_room(start, "Old rope bridge"), NULL, NULL, NULL, NULL);
    add_person_to_room(get_room(world, "Road between Fog Mountains"), create_person("Kate", "My girlfriend", "Oh, I'm glad to see you!", NULL, NULL, NULL, create_item("Book", "Ususal book", MOVABLE), get_room(world, "Road between Fog Mountains")));
    add_item_to_room(get_room(world, "Road between Fog Mountains"), create_item("sword", "Made from steel", MOVABLE & EXAMINABLE));

    return start;
}

struct container* add_room_to_world(struct container* world, struct room* room){
    if(room == NULL) return world;
    struct container *ptr = world;
    while(ptr != NULL){
        if(strcmp(ptr->room->name, room->name) == 0) return world;
        ptr = ptr->next;
    }
    return create_container(world, ROOM, room);

}

struct room* get_room(struct container* world, char* name){
    if(world == NULL || name == NULL) return 0;
    return get_from_container_by_name(world, name);
}

struct container* destroy_world(struct container* world){
    if(world == NULL) return NULL;
    return destroy_containers(world);
}