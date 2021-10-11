/* Implentation of the player module */

#include <stdio.h>
#include <stdlib.h> // For malloc
#include "player.h"  /* Enforce that the header file matches the declarations */


/** Player implementation */
struct player {
    char symbol;
    int ai_type; // = 0 if it's a human player, the number corresponding to the ai type otherwise
    int x_init;
    int y_init;
    int cell_owned;
};

/** Create a player whose symbol is taken in parameter*/
player_t* add_player(char symbol, int ai_type, int x_init, int y_init){
    player_t* res = malloc(sizeof(player_t));
    res -> symbol = symbol;
    res -> ai_type = ai_type;
    res -> x_init = x_init;
    res -> y_init = y_init;
    res -> cell_owned = 1;
    return res;
}

/** Getters and setters for player*/
char get_player_symbol(player_t* player)
{
    return player->symbol;
}
int get_player_cell_owned(player_t* player)
{
    return player->cell_owned;
}
int get_player_ai_type(player_t* player)
{
    return player -> ai_type;
}
int get_player_init_x(player_t* player) {
    return player -> x_init;
}
int get_player_init_y(player_t* player) {
    return player -> y_init;
}
void set_player_cell_owned(player_t* player,  int cell_number)
{
    player -> cell_owned = cell_number;
}
