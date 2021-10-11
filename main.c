/* Template of the 7 wonders of the world of the 7 colors assigment. */

#include <stdio.h>     /* Import the system's printf */
#include "board.h"     /* Import our board module */

int tournament_happening = 1;



/** Program entry point */
int main(void)
{
    if (tournament_happening == 0) {
        // Initialiaze the game
        init_game();
        printf("\n\nWelcome to the 7 wonders of the world of the 7 colors\n"
    	   "*****************************************************\n\n"
    	   "Current board state:\n");
        print_board();

        int turn = 0;
        while(end_game() == 1){
           game_turn(get_player(turn % 2));
           turn++;
        }
    } else {
        int ai_type1 = 2;
        int ai_type2 = 3;
        int nb_games = 100;
        double victory_1 = tournament_AI(ai_type1, ai_type2, nb_games) / 100;

        printf("Taux de victoire de l'IA %d : %f\n", ai_type1, victory_1);
        printf("Taux de victoire de l'IA %d : %f\n", ai_type2, 1 - victory_1);
    }



    return 0; // Everything went well
}
