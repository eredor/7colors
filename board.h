/* Template of the 7 wonders of the world of the 7 colors assigment */
#include "player.h"
#include "coordinates.h"

/* Header file of the board module */

#ifndef BOARD_H
#define BOARD_H

/* Note: feel free to modify this API if you need it to clean your code */

typedef struct cell cell_t;

/** Create a player whose symbol is taken in parameter*/
cell_t* create_cell(char symbol);

/** Retrieves the color of a given board cell */
char get_cell_color(int x, int y);
int get_cell_visited(int x, int y);
int get_cell_turn_visited(int x, int y);
void set_cell_color(int x, int y, char color);
void set_cell_visited(int x, int y, int visited);
void set_cell_turn_visited(int x, int y, int turn);

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
void clean_board(int x, int y);
void clean_board_turn_visited(int x, int y, int turn);
void print_board_visi(void);

/** Alea chooses a random letter to play */
char alea_strategy(player_t* player);
char glouton_strategy(player_t* player);
char hegemonique_strategy(player_t* player);
int neighbours_counter(int i);
int is_landlocked(int x, int y, char color);
char glouton_prevoyant_strategy(player_t* player);

/** Returns the move of an ai player */
char ai_move(player_t* player);


/** Initialize the game
 * Ask each player for a symbol
 * Initialize the board
*/
void init_game();

/** Initialize the board */
void init_board();

int simulate_propagate(char color_covering, int x, int y, char color_covered, int ai, int turn);
int simulate_alea(char color_covering, int x, int y, char color_covered, int ai, int turn);
int simulate_hegemonique(char color_covering, int x, int y, char color_covered, int ai, int turn);
int simulate_glouton(char color_covering, int x, int y, char color_covered, int ai, int turn);

/** Propagates recursively a color over another */
int propagate(char color_covering, int x, int y, char color_covered);

/** Update the board */
void update_board(char letter, player_t* player);

/** Main loop */
void game_turn(player_t* player);

/** Check if the game should end*/
int  end_game();

#endif
