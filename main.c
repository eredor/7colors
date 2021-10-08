/* Template of the 7 wonders of the world of the 7 colors assigment. */

#include <stdio.h>     /* Import the system's printf */
#include "board.h"     /* Import our board module */

/** Program entry point */
int main(void)
{
    // Initialiaze the game 
    init_board();
    printf("\n\nWelcome to the 7 wonders of the world of the 7 colors\n"
	   "*****************************************************\n\n"
	   "Current board state:\n");
    print_board();

    int turn = 0;
    while(get_game_statuts() == 0){
       (turn % 2 == 0) ? game_turn(get_player_one()) : game_turn(get_player_two());
       turn++;
    }


    return 0; // Everything went well
}
