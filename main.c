/* Template of the 7 wonders of the world of the 7 colors assigment. */

#include <stdio.h>     /* Import the system's printf */
#include "board.h"     /* Import our board module */

/** Program entry point */
int main(void)
{
    // Initialiaze the game 
    init_game();
    printf("\n\nWelcome to the 7 wonders of the world of the 7 colors\n"
	   "*****************************************************\n\n"
	   "Current board state:\n");
    print_board();

    int turn = 0;
    while(end_game()){
       game_turn(get_player(turn % 2));
       turn++;
    }


    return 0; // Everything went well
}
