/* Template of the 7 wonders of the world of the 7 colors assigment */
/* Implentation of the board module */

#include <stdio.h>   /* Import printf */
#include "board.h"   /* Enforce that the header file matches the declarations */
#include "simple_unit_test.h" /* Import the testing infrastructure */
#include <time.h> /* Import time to initialize random seed */
#include "chained_lists.h" /* Use of chained lists */


/* Note: This template comes with several global definitions. For now.
 *
 * Such globals are usually discouraged, but having a few of them is OK in a C program.
 * At first, no dinosaure will get you if you use globals, but you should seek for a better
 * solution for your final version.
 *
 * Encapuslating them in an appropriate data structure, and removing all globals would be a must.
 * Plus, this path often leads to simpler code, that is easier to test.
 */

/* We want a 30x30 board game by default */
#define BOARD_SIZE 7
/* SPOT for the number of colors */
#define NB_COLORS 7


/** Player implementation */
struct player {
    char symbol;
    int ai_type; // = 0 if it's a human player, the number corresponding to the ai type otherwise
    int x_init;
    int y_init;
    int square_owned;
    coordinates_t** square_list;
};

/** Create a player whose symbol is taken in parameter*/
player_t* add_player(char symbol, int ai_type, int x_init, int y_init){
    player_t* res = malloc(sizeof(player_t));
    res -> symbol = symbol;
    res -> ai_type = ai_type;
    res -> x_init = x_init;
    res -> y_init = y_init;
    res -> square_owned = 1;
    res -> square_list = malloc((BOARD_SIZE * BOARD_SIZE)/2 * sizeof(coordinates_t*));
    return res;
}

/** Getters and setters for player*/
char get_player_symbol(player_t* player)
{
    return player->symbol;
}
int get_player_square_owned(player_t* player)
{
    return player->square_owned;
}
int get_player_ai_type(player_t* player)
{
    return player -> ai_type;
}
int get_player_init_x(player_t* player) {
    return player -> x_init;
}
int get_player_init_y(player_t* player) {
    return player -> y_init;
}
void set_player_square_owned(player_t* player,  int square_number)
{
    player->square_owned = square_number;
}
coordinates_t* get_player_square_list(player_t* player, int i)
{
    return player -> square_list[i];
}
void add_player_square_list(player_t* player, coordinates_t* coordinates){
    if (get_player_square_owned(player) >= (BOARD_SIZE * BOARD_SIZE)/2 - 1) {
        player -> square_list = realloc(player -> square_list, 10 * sizeof(coordinates_t*));
    }
    player -> square_list[get_player_square_owned(player) - 1] = coordinates;
}


/** List of players*/
player_t* player_list[2];

/** Getter and setter for the list*/
player_t* get_player(int i) {
    return player_list[i];
}

void set_player(int i, player_t* player){
    player_list[i] = player;
}
/** Represent the actual current board game */
char board[BOARD_SIZE * BOARD_SIZE] = { 0 }; // Filled with zeros

/** Initializes the board randomly */
void init_board2(void)
{
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            int case_idx = BOARD_SIZE * i + j;
            srand(time(NULL) + case_idx); // initialize random seed
            board[case_idx] = (rand() % NB_COLORS) + 'A';
        }
    }
    // Initilization of both players' positions
    board[BOARD_SIZE - 1] = '^';
    board[(BOARD_SIZE - 1) * BOARD_SIZE] = 'v';
}

/** Retrieves the color of a given board cell */
char get_cell(int x, int y)
{
    return board[y * BOARD_SIZE + x];
}

/** Changes the color of a given board cell */
void set_cell(int x, int y, char color)
{
    board[y * BOARD_SIZE + x] = color;
}

/** Prints the current state of the board on screen
 *
 * It would be nicer to do this with ncurse or even SFML or SDL,
 * but this is not required in this assignment. See the extensions.
 */
void print_board(void)
{
    int i, j;
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            printf("%c  ", get_cell(i, j));
        }
        printf("\n");
    }
}

/** Functions for AI strategies */

/** Alea chooses a random letter to play */
char alea_strategy(void)
{
    srand(time(NULL));
    return 'A' + (rand() % NB_COLORS);
}

/* WORK IN PROGRESS
char better_alea_strategy(player_t* player)
{

}
*/

/** Returns the move of an ai player */
char ai_move(player_t* player)
{
    switch (get_player_ai_type(player)) {
        case 1: return alea_strategy(); break;
        default: return 'A'; break;
        // other cases will be added for future AIs
    }
}


/** Initialize the game
 * Ask each player for a symbol
 * Initialize the board
*/
void init_game(){
    char symbol, c;
    int ai_type;
    for (int i = 0; i<2; i++) {
        int x_init = i * (BOARD_SIZE - 1);
        int y_init = (1 - i) * (BOARD_SIZE - 1);

        printf("Player %d what type of AI are you ? \n", i + 1);
        scanf("%d", &ai_type);
        while ((c = getchar()) != '\n' && c != EOF) {}
        printf("Player %d enter a symbol \n", i + 1);
        scanf("%c", &symbol);
        while ((c = getchar()) != '\n' && c != EOF) {}

        set_player(i, add_player(symbol, ai_type, x_init, y_init));
    }
    init_board();
}

/** Initialize the board */
void init_board() {
    srand(time(NULL)); // initialize random seed
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            set_cell(j, i, ((rand() % NB_COLORS) + 'A'));
        }
    }
    set_cell(0, BOARD_SIZE-1, get_player_symbol(get_player(0)));
    add_player_square_list(get_player(0), add_coordinates(0, BOARD_SIZE-1));
    set_cell(BOARD_SIZE -1, 0, get_player_symbol(get_player(1)));
    add_player_square_list(get_player(1), add_coordinates(BOARD_SIZE - 1, 0));
}

/** Update the board */

// Propagate recursively a color from a square over another color
int propagate(char color_covering, int x, int y, char color_covered) {
    set_cell(x, y, color_covering);
    int modifs = 1;
    if ((x < BOARD_SIZE - 1) && (get_cell(x + 1, y) == color_covered)) {
        modifs += (propagate(color_covering, x + 1, y, color_covered));
    }
    if ((x > 1) && (get_cell(x - 1, y) == color_covered)) {
        modifs += (propagate(color_covering, x - 1, y, color_covered));
    }

    if ((y < BOARD_SIZE - 1) && (get_cell(x, y + 1) == color_covered)) {
        modifs += (propagate(color_covering, x, y + 1, color_covered));
    }
    if ((y > 1) && (get_cell(x, y - 1) == color_covered)) {
        modifs += (propagate(color_covering, x, y - 1, color_covered));
    }
    return modifs;
}

void update_boardV3(char letter, player_t* player){
    char sym = get_player_symbol(player);
    int x = get_player_init_x(player);
    int y = get_player_init_y(player);

    propagate(letter, x, y, sym);
    int modifications = propagate(sym, x, y, letter);

    set_player_square_owned(player, modifications);
}


void update_board(char letter, player_t* player){
    int modifications = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if ((get_cell(j, i) == letter)&& is_player_neighbour(j, i,  get_player_symbol(player))) {
                set_cell(j, i, get_player_symbol(player));
                add_player_square_list(player, add_coordinates(j, i));
                modifications += 1;
            }
        }
    }
    if(modifications != 0) {
        set_player_square_owned(player, get_player_square_owned(player) + modifications);
        update_board(letter, player);
    }
}

/** Upgraded version of upgrade_board*/
void update_boardV2(char letter, player_t* player){
    int modifications = 0;
    for(int i = 0; i < get_player_square_owned(player); i++) {
        coordinates_t* cell = get_player_square_list(player, i);
        int x = get_coordinates_x(cell);
        int y = get_coordinates_y(cell);
        if (y != 0){
            if (get_cell(x, y-1)== letter) {
                set_cell(x, y-1, get_player_symbol(player));
                set_player_square_owned(player, get_player_square_owned(player) + 1);
                add_player_square_list(player, add_coordinates(x, y-1));
                modifications += 1;
            }
        }
        if (x != BOARD_SIZE - 1) {
            if (get_cell(x+1, y) == letter) {
                set_cell(x+1, y, get_player_symbol(player));
                set_player_square_owned(player, get_player_square_owned(player) + 1);
                add_player_square_list(player, add_coordinates(x+1, y));
                modifications += 1;
            }
        }
        if (y != BOARD_SIZE - 1) {
            if (get_cell(x, y+1) == letter) {
                set_cell(x, y+1, get_player_symbol(player));
                set_player_square_owned(player, get_player_square_owned(player) + 1);
                add_player_square_list(player, add_coordinates(x, y+1));
                modifications += 1;
            }
        }
        if (x != 0) {
            if (get_cell(x-1, y) == letter) {
                set_cell(x-1, y, get_player_symbol(player));
                set_player_square_owned(player, get_player_square_owned(player) + 1);
                add_player_square_list(player, add_coordinates(x-1, y));
                modifications += 1;
            }
        }

    }
    if(modifications != 0) {
        update_boardV2(letter, player);
    }
}

/** Returns 1 if the given cell has a neighbouring cell owned by the given player*/
int is_player_neighbour(int x, int y, char player) {
    if (y != 0){
        if (get_cell(x, y-1)== player) {
            return 1;
        }
    }
    if (x != BOARD_SIZE - 1) {
        if (get_cell(x+1, y) == player) {
            return 1;
        }
    }
    if (y != BOARD_SIZE - 1) {
        if (get_cell(x, y+1) == player) {
            return 1;
        }
    }
    if (x != 0) {
        if (get_cell(x-1, y) == player) {
            return 1;
        }
    }
    return 0;
}

/** Main loop*/
void game_turn(player_t* player){
    char letter, c;
    if (get_player_ai_type(player) == 0) {
        printf("Player %c enter a letter\n", get_player_symbol(player));
        scanf("%c", &letter);
        while ((c = getchar()) != '\n' && c != EOF) {}
    } else {
        letter = ai_move(player);
        printf("AI played letter %c\n", letter);
    }
    update_boardV3(letter, player);
    print_board();
    for (int i = 0; i<2; i++) {
        printf("Score Player %c = %d , %.2f %% \n", get_player_symbol(get_player(i)), get_player_square_owned(get_player(i)), (float) get_player_square_owned(player_list[i]) / (BOARD_SIZE * BOARD_SIZE));
    }
}

/** Check if the game should end */
int end_game() {
    for (int i = 0; i<2; i++) {
        if (get_player_square_owned(get_player(i)) * 2 > BOARD_SIZE * BOARD_SIZE) {
            return 0;
        }
    }
    return 1;
}


/************ The tests **************/

/* Tests that the initialization works */
SUT_TEST(init_cell)
{
   char c = get_cell(5, 5);
   SUT_CHAR_EQUAL(c, '\0', "Creating the board does not initialize the cells to '\\0' but to '%c'", c);

   return 1;
}

/* Tests that the get_cell and set_cell work */
SUT_TEST(getset_cell)
{
   char c;

   set_cell(5, 5, 'A');
   c = get_cell(5, 5);
   SUT_CHAR_EQUAL(c, 'A', "Setting a cell to 'A' leads to '%c' as a value instead", c);

   return 1;
}

SUT_TEST_SUITE(board) = {
    SUT_TEST_SUITE_ADD(init_cell),
    SUT_TEST_SUITE_ADD(getset_cell),
    SUT_TEST_SUITE_END
};
