/* Template of the 7 wonders of the world of the 7 colors assigment */
#include "player.h"
#include "coordinates.h"

/* Header file of the board module */

#ifndef BOARD_H
#define BOARD_H

/** 
 * @param i : the index of a player
 * 
 *@return : the player of index i in player_list */
player_t* get_player(int i);

/** 
 * @param i : the index of a player
 * @param player : a player
 * 
 * Changes the content of index i in player_list by the player  */
void set_player(int i, player_t* player);


/** Represent a cell of the board*/
typedef struct cell cell_t;

/** 
 * @param color : the color of the cell
 * 
 * Create a cell
 */
cell_t* create_cell(char color);

/** 
 * @param x : the coordinate x of the cell
 * @param y : the coordinate y of the cell 
 * 
 * @return : the color of cell(x,y)
 */
char get_cell_color(int x, int y);

/** 
 * @param x : the coordinate x of the cell
 * @param y : the coordinate y of the cell 
 * @param color : a color
 * 
 * Changes the color of the cell by the one entered in parameter
 */
void set_cell_color(int x, int y, char color);

/** 
 * @param x : the coordinate x of the cell
 * @param y : the coordinate y of the cell 
 * 
 * @return : the attribute visited of cell(x,y)
 */
int get_cell_visited(int x, int y);

/** 
 * @param x : the coordinate x of the cell
 * @param y : the coordinate y of the cell 
 * @param visited : 1 if the cell has been visited, if not 0
 * 
 * Changes the value of visited of the cell by the one entered in parameter
 */
void set_cell_visited(int x, int y, int visited);

/** 
 * @param x : the coordinate x of the cell
 * @param y : the coordinate y of the cell 
 * 
 * @return : the attribute turn_visited of cell(x,y)
 */
int get_cell_turn_visited(int x, int y);


/** 
 * @param x : the coordinate x of the cell
 * @param y : the coordinate y of the cell 
 * @param turn : the turn number when the cell was visited for the first time
 * 
 * Changes the value of turn_visited of the cell by the one entered in parameter
 */
void set_cell_turn_visited(int x, int y, int turn);



/** Prints the current state of the board on screen
 *
 * It would be nicer to do this with ncurse or even SFML or SDL,
 * but this is not required in this assignment. See the extensions.
 */
void print_board(void);

/**
 * @param x : the strating position x of a player
 * @param y : th estrating position y of a player
 * 
 * Reset the value of visited and turn_visited
 */
void clean_board(int x, int y);

/**
 * @param x : the strating position x of a player
 * @param y : th estrating position y of a player
 * 
 * Reset the value of visited 
 * Reset the value of turn_visited if it matches turn
 */
void clean_board_turn_visited(int x, int y, int turn);

/**
 * @param player : a player
 * 
 * @return : a random letter that will affect the board
 */
char alea_strategy(player_t* player);

/**
 * @param player : a player
 * 
 * @return : the letter that will make the player earns the most cells
 */
char glouton_strategy(player_t* player);

/**
 * @param player : a player
 * 
 * @return : the letter that will make its perimeter the widest
 */
char hegemonique_strategy(player_t* player);

/**
 * Counter for the hegemonique_strategy
 * 
 * @return : the number of time the function was called since the last reinitialization
 */ 
int neighbours_counter(int i);

/**
 * @param x : the coordinate x of a cell
 * @param y : the coordinate y of a cell
 * @param color : a player color
 * 
 * @return : 1 if the cell(x,y) is surrounded by cells owned by the player
 */ 
int is_landlocked(int x, int y, char color);

/**
 * @param player : a player
 * 
 * @return : the letter that will make the player earns the most cells in 2 turn
 */
char glouton_prevoyant_strategy(player_t* player);

/** 
 * @param player : an AI player
 * 
 * @return : the letter chosen by player 
 */
char ai_move(player_t* player);

/** 
 * Initialize the game
 * Ask each player for a symbol
 * Initialize the board
*/
void init_game();

/** 
 * Initialize the board 
 */
void init_board();

/**
 * @param color : the color of a player
 * @param x : the strating coordinate x of the player 
 * @param y : the strating coordinate y of the player 
 * @param letter : the letter the player played
 * @param ai : the type of ai that is the player
 * @param turn : the turn to simulate
 * 
 * Propagate recursively a color from a cell over another color
 * 
 * @return : the number of cells owned by the player
 * 
 */
int simulate_propagate(char color, int x, int y, char letter, int ai, int turn);

/**
 * @param color : the color of a player
 * @param x : the strating coordinate x of the player 
 * @param y : the strating coordinate y of the player 
 * @param letter : the letter the player played
 * @param ai : the type of ai that is the player
 * @param turn : the turn to simulate
 * 
 * Propagate recursively a color from a cell over another color
 * 
 * @return : the number of cells owned by the player
 * 
 */
int simulate_alea(char color, int x, int y, char letter, int ai, int turn);

/**
 * @param color : the color of a player
 * @param x : the strating coordinate x of the player 
 * @param y : the strating coordinate y of the player 
 * @param letter : the letter the player played
 * @param ai : the type of ai that is the player
 * @param turn : the turn to simulate
 * 
 * Propagate recursively a color from a cell over another color
 * 
 * @return : the number of cells owned by the player
 * 
 */
int simulate_hegemonique(char color, int x, int y, char letter, int ai, int turn);

/**
 * @param color : the color of a player
 * @param x : the strating coordinate x of the player 
 * @param y : the strating coordinate y of the player 
 * @param letter : the letter the player played
 * @param ai : the type of ai that is the player
 * @param turn : the turn to simulate
 * 
 * Propagate recursively a color from a cell over another color
 * 
 * @return : the number of cells owned by the player
 * 
 */
int simulate_glouton(char color, int x, int y, char letter, int ai, int turn);

/**
 * @param color : the color of a player
 * @param x : the strating coordinate x of the player 
 * @param y : the strating coordinate y of the player 
 * @param letter : the letter the player played
 * 
 * Propagate recursively a color from a cell over another color
 * 
 * @return : the number of cells owned by the player
 * 
 */
int propagate(char color, int x, int y, char letter);

/**
 * @param letter : the letter played by the player
 * @param player : the player
 * 
 * Update the board and the player's data 
 */
void update_board(char letter, player_t* player);

/**
 * @param player : the player whose turn it is 
 * 
 * Play a turn of the game
 */
void game_turn(player_t* player);

/** 
 * Check if the game should end 
 * 
 * @return : 1 if the game end
 */
int  end_game();

/** 
 * @param ai_type1 : the ai type of player 1
 * @param ai_type2 : the ai type of player 2 
 * 
 * Fight between AIs implementation 
 */
void init_game_AI(int ai_type1, int ai_type2);

/**
 * @param player : the player whose turn it is 
 * 
 * Play a turn of the game
 */
void game_turn_AI(player_t* player);

/** 
 * @param ai_type1 : the ai type of player 1
 * @param ai_type2 : the ai type of player 2
 * @param nb_games : number of games played
 * 
 * Tournament implementation 
 * 
 * @return : number of victory of player 1
 */
int tournament_AI(int ai_type1, int ai_type2, int nb_games);

#endif
