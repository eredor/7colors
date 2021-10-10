/* Template of the 7 wonders of the world of the 7 colors assigment */
#include "chained_lists.h"

/* Header file of the board module */

#ifndef BOARD_H
#define BOARD_H

/* Note: feel free to modify this API if you need it to clean your code */

typedef struct cell cell_t;

/** Create a player whose symbol is taken in parameter*/
cell_t* create_cell(char symbol);

/** Retrieves the color of a given board cell */
char get_cell_color(int x, int y);
int get_cell_flag(int x, int y);
void set_cell_color(int x, int y, char color);
void set_cell_flag(int x, int y, char flag);

/** Player implementation */
typedef struct player player_t;

/** Create a player whose symbol is taken in parameter*/
player_t* add_player(char symbol, int ai_type, int x_init, int y_init);

/** Getters and setters for player*/
char get_player_symbol(player_t* player);
int get_player_cell_owned(player_t* player);
int get_player_ai_type(player_t* player);
int get_player_init_x(player_t* player);
int get_player_init_y(player_t* player);
void set_player_cell_owned(player_t* player, int cell_number);

/** Getter and setter for the list*/
player_t* get_player(int i);
void set_player(int i, player_t* player);


/** Prints the current state of the board on screen
 *
 * It would be nicer to do this with ncurse or even SFML or SDL,
 * but this is not required in this assignment. See the extensions.
 */
void print_board(void);
void print_board_flag(void);
void clean_board();

/** Alea chooses a random letter to play */
char alea_strategy(player_t* player);
char glouton_strategy(player_t* player);
char hegemonique_strategy(player_t* player);
int neighbours_counter(int i);

/** Returns the move of an ai player */
char ai_move(player_t* player);


/** Initialize the game
 * Ask each player for a symbol
 * Initialize the board
*/
void init_game();

/** Initialize the board */
void init_board();

int simulate_propagate(char color_covering, int x, int y, char color_covered);

/** Propagates recursively a color over another */
int propagate(char color_covering, int x, int y, char color_covered);

/** Update the board */
void update_board(char letter, player_t* player);

/** Main loop */
void game_turn(player_t* player);

/** Check if the game should end*/
int  end_game();

#endif
