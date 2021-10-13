/* Header file of the chained_lists module */

#ifndef PLAYER_H
#define PLAYER_H


/** Player implementation */
typedef struct player player_t;

/** Create a player whose symbol is taken in parameter */
player_t* add_player(char symbol, int ai_type, int x_init, int y_init);

void delete_player(player_t* player);


/** Getters and setters for player */
char get_player_symbol(player_t* player);
int get_player_cell_owned(player_t* player);
int get_player_ai_type(player_t* player);
int get_player_init_x(player_t* player);
int get_player_init_y(player_t* player);
void set_player_cell_owned(player_t* player, int cell_number);

#endif
