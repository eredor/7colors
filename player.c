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


/** 
 * @param symbol : the color of the player
 * @param ai_type : 0 if it's a human player, else the number of corresponding ai
 * @param x_init : strating position x of the player
 * @param y_init : strating position y of the player
 * 
 * @return : a player
 */
player_t* add_player(char symbol, int ai_type, int x_init, int y_init){
    player_t* res = malloc(sizeof(player_t));
    res -> symbol = symbol;
    res -> ai_type = ai_type;
    res -> x_init = x_init;
    res -> y_init = y_init;
    res -> cell_owned = 1;
    return res;
}

/**
 * @param player : a player
 * 
 * Free the memory of the player
 */ 
void delete_player(player_t* player){
    free(player);
}

/** 
 * @param player : a player
 * 
 * @return : the player's symbol
 */
char get_player_symbol(player_t* player)
{
    return player->symbol;
}

/** 
 * @param player : a player
 * 
 * @return : the player's number of cells owned
 */
int get_player_cell_owned(player_t* player)
{
    return player->cell_owned;
}

/** 
 * @param player : a player
 * 
 * @return : the player's ai type
 */
int get_player_ai_type(player_t* player)
{
    return player -> ai_type;
}

/** 
 * @param player : a player
 * 
 * @return : the player's strating position x
 */
int get_player_init_x(player_t* player) {
    return player -> x_init;
}

/** 
 * @param player : a player
 * 
 * @return : the player's strating position y
 */
int get_player_init_y(player_t* player) {
    return player -> y_init;
}

/** 
 * @param player : a player
 * @param cell_number : the new number of cells owned
 * 
 * Change the player's number of cells owned by the one taken in parameter
 */
void set_player_cell_owned(player_t* player,  int cell_number)
{
    player -> cell_owned = cell_number;
}
