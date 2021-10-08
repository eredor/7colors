/* Template of the 7 wonders of the world of the 7 colors assigment */
/* Header file of the board module */

#ifndef BOARD_H
#define BOARD_H

/* Note: feel free to modify this API if you need it to clean your code */

/** Initializes the board randomly */
void init_board2(void);

int get_game_statuts();
char get_player_one();
char get_player_two();

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

/** Initialize the board */
void init_board();

/** Update the board */
void update_board(char letter, char player);

/** Return 1 if the given cell has a neighbouring cell owned by the given player*/
int is_player_neighbour(int x, int y, char player);

/** Main loop */
void game_turn(char player);

/** Update game_status*/
void end_game();

#endif
