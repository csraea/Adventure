#include "parser.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct parser* create_parser(){
    struct parser *parser = calloc(1, sizeof(struct parser));
    parser->history = NULL;
    parser->commands = create_container(NULL, COMMAND, create_command("NORTH", "Move in the north direction.", "north", 1));
    create_container(parser->commands, COMMAND, create_command("SOUTH", "Move in the south direction.", "south", 1));
    create_container(parser->commands, COMMAND, create_command("EAST", "Move in the east direction.", "east", 1));
    create_container(parser->commands, COMMAND, create_command("SOUTH", "Move in the west direction.", "west", 1));
    create_container(parser->commands, COMMAND, create_command("UP", "Move up.", "up", 1));
    create_container(parser->commands, COMMAND, create_command("DOWN", "Move down.", "down", 1));
    create_container(parser->commands, COMMAND, create_command("INVENTORY", "Display the content of backpack.", "(inventory)|(backpack)", 1));
    create_container(parser->commands, COMMAND, create_command("SAVE", "Save the game progress on disk.", "((save)|(save game)|(save progress))", 3));
    create_container(parser->commands, COMMAND, create_command("LOAD", "Game progress will be loaded from the disk.", "(LOAD)", 1));
    create_container(parser->commands, COMMAND, create_command("END", "Command ends the current game without saving.", "((QUIT)|(EXIT))", 2));
    create_container(parser->commands, COMMAND, create_command("RESTART", "Play the game again from the very beginning.", "(RESTART)", 1));
    create_container(parser->commands, COMMAND, create_command("EXPLORE AREA", "Display actual information about area where player is located now.", "(EXPLORE)", 1));
    create_container(parser->commands, COMMAND, create_command("COMMANDS", "Show all commands the game provided with.", "((HELP)|(COMMANDS))", 2));
    create_container(parser->commands, COMMAND, create_command("VERSION", "Display actual info about the version of the game and author contacts.", "(VERSION)", 1));
    create_container(parser->commands, COMMAND, create_command("ABOUT", "Display short game description and preface.", "(ABOUT)", 1));
    create_container(parser->commands, COMMAND, create_command("INTERACT", "Inetarct (talk) with different characters.", "(interact)|(talk)|(ask)|(speak)", 2));
    create_container(parser->commands, COMMAND, create_command("TAKE", "Pick up something and lay it down to backpack", "(TAKE) *(.*)", 2));
    create_container(parser->commands, COMMAND, create_command("DROP", "Drop something from the backpack.", "(DROP) *(.*)", 2));
    create_container(parser->commands, COMMAND, create_command("USE", "Use something from backpack or area.", "(USE) *(.*)", 2));
    create_container(parser->commands, COMMAND, create_command("DESCRY", "Observe the thing.", "((DESCRY) *(.*))|((OBSERVE) *(.*))|((EXAMINE) *(.*))", 2));

    return parser;
}

struct parser* destroy_parser(struct parser* parser){
    if(parser==NULL) return NULL;
    parser->history = destroy_containers(parser->history);
    parser->commands = destroy_containers(parser->commands);
    free(parser);
    return NULL;  
}

struct command* parse_input(struct parser* parser, char* input){
    if(parser == NULL || input == NULL) return NULL;
    struct container *ptr = parser->commands;
    int flag = 0;
    regmatch_t groups[5];
    while(ptr != NULL){
        if(regexec(&ptr->command->preg, input, ptr->command->nmatch+1, groups, 0) != REG_NOMATCH){
            flag = 1;
            break;
        }
        ptr = ptr->next;
    }
    if(flag == 0){
        printf("Sorry, i din't understand. May you say again?\n");
        return NULL;
    }
    if(ptr->command->nmatch!=2)
        return ptr->command;
    struct command* com = ptr->command;
    com->groups = (char**)calloc(com->nmatch, sizeof(char*));
    for(int i = 1, n=0; i < com->nmatch+1; i++, n++){
        com->groups[n] = (char*)calloc((size_t)(groups[i].rm_eo-groups[i].rm_so)+1, sizeof(char));
        strncpy(com->groups[n], &input[groups[i].rm_so], (size_t)(groups[i].rm_eo-groups[i].rm_so));
        com->groups[n][groups[i].rm_eo-groups[i].rm_so]='\0';
    }
    return ptr->command;
}