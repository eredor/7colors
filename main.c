/* Template of the 7 wonders of the world of the 7 colors assigment. */

#include <stdio.h>     /* Import the system's printf */
#include "board.h"     /* Import our board module */

/** Program entry point */
int main(void)
{
    int tournament_happening = 0;

    if (tournament_happening) {
        int ai_type1 = 1;
        int ai_type2 = 2;
        int nb_games = 100;
        int victory_1 = tournament_AI(ai_type1, ai_type2, nb_games);

        printf("Taux de victoire de l'IA %d : %d , %.2f %%\n", ai_type1, victory_1, (float) 100 * victory_1 / nb_games);
        printf("Taux de victoire de l'IA %d : %d , %.2f %%\n", ai_type2, nb_games - victory_1, (float) 100 * (nb_games - victory_1) / nb_games);

    } else {
        init_game();  // Initialiaze the game
        printf("\n\nWelcome to the 7 wonders of the world of the 7 colors\n"
    	   "*****************************************************\n\n"
    	   "Current board state:\n");
        print_board();

        int turn = 0;
        while(!end_game()){
           game_turn(get_player(turn % 2));
           turn++;
        }
    }
    return 0; // Everything went well
}
