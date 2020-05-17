#include "command.h"
#include <stdlib.h>
#include <string.h>

struct command* create_command(char* name, char* description, char* pattern, size_t nmatch){
    if(name == NULL || description == NULL || strlen(name) == 0 || strlen(description) == 0) return NULL;
    struct command *cmd = calloc(1, sizeof(struct command));
    if(cmd == NULL) return NULL;
    cmd->description = description;
    cmd->name = name;
    cmd->nmatch = nmatch;
    if(pattern == NULL || strlen(pattern) == 0) return cmd;
    regex_t preg;
    if(regcomp(&preg, pattern, REG_EXTENDED | REG_ICASE) != 0) return NULL;
    cmd->preg = preg;
    return cmd;
}

struct command* destroy_command(struct command* command){
    if(command == NULL) return NULL;
    if(&(command->preg) != NULL) regfree(&command->preg);
    if(command->groups != NULL){
        for(size_t i = 0; i < command->nmatch; i++){
            free(command->groups[i]);
        }
        free(command->groups);
    }
    free(command);
    return NULL;
}