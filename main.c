#include "game.h"
#include <stdlib.h>

int main(){
    struct game* game = create_game();
    while(game->state!=GAMEOVER){
        play_game(game);
        if(game->state==RESTART){
            destroy_game(game);
            game = create_game();
        }
    }
    destroy_game(game);
    get_item_from_room(NULL, NULL);
    return 0;
}
