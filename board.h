/* Template of the 7 wonders of the world of the 7 colors assigment */
/* Header file of the board module */

#ifndef BOARD_H
#define BOARD_H

/* Note: feel free to modify this API if you need it to clean your code */

/** Initializes the board randomly */
void init_board2(void);

/** Player implementation */
typedef struct player player_t;

/** Create a player whose symbol is taken in parameter*/
player_t* add_player(char symbol, int ai_type);

/** Getters and setters for player*/
char get_player_symbol(player_t* player);
char get_player_square_owned(player_t* player);
int get_player_ai_type(player_t* player);
void set_player_square_owned(player_t* player, int square_number);

/** Getter and setter for the list*/
player_t* get_player(int i);
void set_player(int i, player_t* player);

/** Retrieves the color of a given board cell */
char get_cell(int x, int y);

/** Changes the color of a given board cell */
void set_cell(int x, int y, char color);

/** Prints the current state of the board on screen
 *
 * It would be nicer to do this with ncurse or even SFML or SDL,
 * but this is not required in this assignment. See the extensions.
 */
void print_board(void);

/** Alea chooses a random letter to play */
char alea_strategy(void);

/** Returns the move of an ai player */
char ai_move(player_t* player);


/** Initialize the game
 * Ask each player for a symbol
 * Initialize the board
*/
void init_game();

/** Initialize the board */
void init_board();

/** Update the board */
void update_board(char letter, player_t* player);

/** Return 1 if the given cell has a neighbouring cell owned by the given player*/
int is_player_neighbour(int x, int y, char player);

/** Main loop */
void game_turn(player_t* player);

/** Check if the game should end*/
int  end_game();

#endif
