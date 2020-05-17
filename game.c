#include "game.h"
#include "world.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct game* create_game(){
    struct game *newGame = calloc(1, sizeof(struct game));
    newGame->backpack = create_backpack(10);
    newGame->parser = create_parser();
    newGame->world = create_world();
    newGame->current_room = newGame->world->room;
    newGame->state = PLAYING;
    return newGame;
}

struct game* destroy_game(struct game* game){
    if(game == NULL) return NULL;
    game->backpack = destroy_backpack(game->backpack);
    game->world = destroy_world(game->world);
    game->parser = destroy_parser(game->parser);
    free(game);
    return NULL;
}

void execute_command(struct game* game, struct command* command, struct container *event){
    if(command == get_from_container_by_name(game->parser->commands, "NORTH")){
        if(game->current_room->north != NULL){
            game->current_room = game->current_room->north;
            create_container(event, EVENT, create_event(game, LOCATION, NULL));
            show_room(game->current_room);
            return;
        } else printf("You can't go this way! 1\n");
        return;
    }
    else if(command == get_from_container_by_name(game->parser->commands, "SOUTH")){
        if(game->current_room->south != NULL){
            game->current_room = game->current_room->south;
            create_container(event, EVENT, create_event(game, LOCATION, NULL));
            show_room(game->current_room);
            return;
        } else printf("You can't go this way! 2\n");
        return;
    }
    else if(command == get_from_container_by_name(game->parser->commands, "EAST")){
        if(game->current_room->east != NULL){
            game->current_room = game->current_room->east;
            create_container(event, EVENT, create_event(game, LOCATION, NULL));
            show_room(game->current_room);
            return;
        } else printf("You can't go this way! 3\n");
        return;
    }
    else if(command == get_from_container_by_name(game->parser->commands, "WEST")){
        if(game->current_room->west != NULL){
            game->current_room = game->current_room->west;
            create_container(event, EVENT, create_event(game, LOCATION, NULL));
            show_room(game->current_room);
            return;
        } else printf("You can't go this way! 4\n");
        return;
    }
    else if(command == get_from_container_by_name(game->parser->commands, "UP")){
        if(game->current_room->up != NULL){
            game->current_room = game->current_room->up;
            create_container(event, EVENT, create_event(game, LOCATION, NULL));
            show_room(game->current_room);
            return;
        } else printf("You can't go this way! 5\n");
        return;
    }
    else if(command == get_from_container_by_name(game->parser->commands, "DOWN")){
        if(game->current_room->down != NULL){
            game->current_room = game->current_room->down;
            create_container(event, EVENT, create_event(game, LOCATION, NULL));
            show_room(game->current_room);
            return;
        } else printf("You can't go this way! 6\n");
        return;
    }
    else if(command == get_from_container_by_name(game->parser->commands, "COMMANDS")){
        struct container *cmd = game->parser->commands;
        while(cmd != NULL){
            printf("%s ~ %s\n", cmd->command->name, cmd->command->description);
            cmd = cmd->next;
        }
        return;
    }
    else if(command == get_from_container_by_name(game->parser->commands, "INVENTORY")){
        struct container *ptr = game->backpack->items;
        printf("You have:\n");
        while(ptr != NULL){
            printf("%s\t: %s\n", ptr->item->name, ptr->item->description);
            ptr = ptr->next;
        }
        return;
    }
    else if(command == get_from_container_by_name(game->parser->commands, "VERSION")){
        printf("+-------- ADVENTURE --------+\n");
        printf("| Version: V.1.0            |\n");
        printf("| Author: Alex Korotetskyi  |\n");
        printf("+---------------------------+\n");
        return;
    }
    else if(command == get_from_container_by_name(game->parser->commands, "ABOUT")){
        printf("#==================  A D V E N T U R E  =================#\n");
        printf("|I've  started  my journey in the  Rock Castle, which is |\n");
        printf("|situated  on the other side  of Tight Canyon. The whole |\n");
        printf("|my  family is there. I received a letter  from somebody |\n");
        printf("|named Eadgar. He claims  that a great danger is pending |\n");
        printf("|on my village and family. A man who delivered the letter|\n");
        printf("|disappeared. A little bit later, strange things started |\n");
        printf("|to happen around me. The letter came from the far lands.|\n");
        printf("|Nobody from  my settlement was in the  River Valley for |\n");
        printf("|over a hundred years. I feel I have to find out what is |\n");
        printf("|going on to save my family. So, I ...                   |\n");
        printf("#========================================================#\n");
        return;
    }
    else if(command == get_from_container_by_name(game->parser->commands, "END")){
        game->state = GAMEOVER;
        return;
    }
    else if(command == get_from_container_by_name(game->parser->commands, "RESTART")){
        game->state = RESTART;
    }
    else if(command == get_from_container_by_name(game->parser->commands, "TAKE")){
        struct item* item = get_from_container_by_name(game->current_room->items, command->groups[1]);
        if(add_item_to_backpack(game->backpack, item))
            delete_item_from_room(game->current_room, item);
        create_container(event, EVENT, create_event(game, NITEM, item->name));
        return;
    }
    else if(command == get_from_container_by_name(game->parser->commands, "DROP")){
        add_item_to_room(game->current_room, get_item_from_backpack(game->backpack, command->groups[1]));
        delete_item_from_backpack(game->backpack, get_item_from_backpack(game->backpack, command->groups[1]));
        return;
    }
    else if(command == get_from_container_by_name(game->parser->commands, "INTERACT")){
        if(game->current_room->person == NULL){
            printf("You can't speak to the empty space!\n");
            return;
        }
        puts(game->current_room->person->replic[0]);
        return;
    }
    else if(command == get_from_container_by_name(game->parser->commands, "EXPLORE AREA")){
        printf("%s\n", game->current_room->description);
        if(game->current_room->items != NULL){
            printf("There are some things:\n");
            struct container *ptr = game->current_room->items;
            while(ptr != NULL){
                printf("%s\n", ptr->item->name);
                ptr = ptr->next;
            }
        }
        return;
    }
    else if(command == get_from_container_by_name(game->parser->commands, "USE")){
        delete_item_from_backpack(game->backpack, get_item_from_backpack(game->backpack, command->groups[1]));
        return;
    }
    else if(command == get_from_container_by_name(game->parser->commands, "DESCRY")){
        struct item* item = get_from_container_by_name(game->backpack->items, command->groups[1]);
        if(item==NULL)
            item = get_from_container_by_name(game->current_room->items, command->groups[1]);
        if(item==NULL) return;
        if((item->properties & EXAMINABLE) == EXAMINABLE)
            printf("%s\n", item->description);
        return;
    }
    else printf("Invalid command!\n");
}

char* create_text(char* input){
    char* text = (char*)calloc(strlen(input)+1, sizeof(char));
    strcpy(text, input);
    return text;
}

void play_game(struct game* game){
    char input[INPUT_BUFFER_SIZE+1];
    struct command* command;
    struct container *event = create_container(NULL, EVENT, create_event(game, SPECIAL, "START"));
    struct container *firstEvent = event;
    execute_command(game, get_from_container_by_name(game->parser->commands, "ABOUT"), firstEvent);
    show_room(game->current_room);
    while(game->state!=GAMEOVER && game->state!=RESTART){
        command=NULL;
        do {
            printf(">");
            fgets(input, INPUT_BUFFER_SIZE, stdin);
            input[strlen(input)-1]='\0';
            command = parse_input(game->parser, input);
        } while(command == NULL);
        game->parser->history = create_container(game->parser->history, TEXT, create_text(input));
        execute_command(game, command, firstEvent);
    }
}