/* Template of the 7 wonders of the world of the 7 colors assigment */
/* Implentation of the board module */

#include <stdio.h>   /* Import printf */
#include "board.h"   /* Enforce that the header file matches the declarations */
#include "simple_unit_test.h" /* Import the testing infrastructure */
#include <time.h> /* Import time to initialize random seed */
#include "player.h" /* Import player module */
#include "coordinates.h" /* Import coordinates module */


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
#define BOARD_SIZE 30
/* SPOT for the number of colors */
#define NB_COLORS 7


/** List of players*/
player_t* player_list[2];

/** Getter and setter for the list*/
player_t* get_player(int i) {
    return player_list[i];
}

void set_player(int i, player_t* player){
    player_list[i] = player;
}


struct cell {
    char symbol;
    int visited;
    int turn_visited;
};

/** Represent the actual current board game */
cell_t* board[BOARD_SIZE * BOARD_SIZE];

/** Create a player whose symbol is taken in parameter*/
cell_t* create_cell(char symbol){
    cell_t* res = malloc(sizeof(cell_t));
    res -> symbol = symbol;
    res -> visited = 0;
    res -> turn_visited = 0;
    return res;
}

/** Retrieves the color of a given board cell */
char get_cell_color(int x, int y)
{
    return board[y * BOARD_SIZE + x] -> symbol;
}
int get_cell_visited(int x, int y)
{
    return board[y * BOARD_SIZE + x] -> visited;
}
int get_cell_turn_visited(int x, int y)
{
    return board[y * BOARD_SIZE + x] -> turn_visited;
}

/** Changes the color of a given board cell */
void set_cell_color(int x, int y, char color)
{
    board[y * BOARD_SIZE + x]->symbol = color;
}

void set_cell_visited(int x, int y, int visited)
{
    board[y * BOARD_SIZE + x]->visited = visited;
}
void set_cell_turn_visited(int x, int y, int turn)
{
    board[y * BOARD_SIZE + x]->turn_visited = turn;
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
            printf("%c  ", get_cell_color(i, j));
        }
        printf("\n");
    }
}

void clean_board(int x, int y){
    set_cell_visited(x, y, 0);
    set_cell_turn_visited(x, y, 0);
    if ((x < BOARD_SIZE - 1) && (get_cell_visited(x + 1, y) || get_cell_turn_visited(x+1, y))) {
        clean_board(x + 1, y);
    }
    if ((x > 0) && (get_cell_visited(x - 1, y)|| get_cell_turn_visited(x-1, y))) {
        clean_board(x - 1, y);
    }
    if ((y < BOARD_SIZE - 1) && (get_cell_visited(x, y + 1) || get_cell_turn_visited(x, y+1))){
        clean_board(x, y + 1);
    }
    if ((y > 0) && (get_cell_visited(x, y - 1) || get_cell_turn_visited(x, y-1))) {
        clean_board(x, y - 1);
    }
}

void clean_board_turn_visited(int x, int y, int turn){
    set_cell_visited(x, y, 0);
    if(get_cell_turn_visited(x,y) == turn) set_cell_turn_visited(x, y, 0);
    if ((x < BOARD_SIZE - 1) && ((get_cell_turn_visited(x + 1, y) == turn) || get_cell_visited(x+1,y))) {
        clean_board_turn_visited(x + 1, y, turn);
    }
    if ((x > 0) && ((get_cell_turn_visited(x - 1, y) == turn) || get_cell_visited(x-1,y))) {
        clean_board_turn_visited(x - 1, y, turn);
    }
    if ((y < BOARD_SIZE - 1) && ((get_cell_turn_visited(x, y + 1) == turn) || get_cell_visited(x,y+1))){
        clean_board_turn_visited(x, y + 1, turn);
    }
    if ((y > 0) && ((get_cell_turn_visited(x, y - 1) == turn) || get_cell_visited(x,y-1))) {
        clean_board_turn_visited(x, y - 1, turn);
    }
}

/** Functions for AI strategies */

/** Alea chooses a random letter to play */
char alea_strategy(player_t* player)
{
    int x = get_player_init_x(player);
    int y = get_player_init_y(player);
    srand(time(NULL));
    char letter = 'A' + (rand() % NB_COLORS);
    while(simulate_propagate(get_player_symbol(player), get_player_init_x(player), get_player_init_y(player), letter, 0) == get_player_cell_owned(player)) {
        letter = 'A' + (rand() % NB_COLORS);
        clean_board(x, y);
    }
    clean_board(x, y);
    neighbours_counter(0);
    return letter;
}


char glouton_strategy(player_t* player){
    int x = get_player_init_x(player);
    int y = get_player_init_y(player);
    char letter;
    int max = 0;
    int temp;
    for (char i = 'A'; i < 'A' + NB_COLORS; i++) {
        temp = simulate_propagate(get_player_symbol(player), get_player_init_x(player), get_player_init_y(player), i, 0);
        clean_board(x, y);
        if(temp > max){
            max = temp;
            letter = i;
        }
    }
    neighbours_counter(0);
    return letter;
}


char hegemonique_strategy(player_t* player){
    int x = get_player_init_x(player);
    int y = get_player_init_y(player);
    char letter;
    int max = 0;
    int temp, cells;
    for (char i = 'A'; i < 'A' + NB_COLORS; i++) {
        cells = simulate_propagate(get_player_symbol(player), get_player_init_x(player), get_player_init_y(player), i, 0);
        temp = neighbours_counter(1) - 1;
        neighbours_counter(0);
        clean_board(x, y);
        if((temp > max) && (cells > get_player_cell_owned(player))){
            max = temp;
            letter = i;
        }
    }
    return letter;
}

int neighbours_counter(int i){
    static int res = 0;
    if(i) res++;
    else res = 0;
    return res;
}

char glouton_prevoyant_strategy(player_t* player){
    int x = get_player_init_x(player);
    int y = get_player_init_y(player);
    char letter;
    char letter2;
    int max = 0;
    int temp, temp2;
    for (char i = 'A'; i < 'A' + NB_COLORS; i++) {
        temp = simulate_propagate(get_player_symbol(player), get_player_init_x(player), get_player_init_y(player), i, 1);
        if(temp != get_player_cell_owned(player)){
            for (char j = 'A'; j < 'A' + NB_COLORS; j++) {
                temp2 = simulate_propagate(get_player_symbol(player), get_player_init_x(player), get_player_init_y(player), j, 2);
                clean_board_turn_visited(x, y, 2);
                if(temp2 > max){
                max = temp2;
                letter = i;
                letter2 = j;
                }
            }
        }
        clean_board(x, y);
    }
    neighbours_counter(0);
    return letter;
}


/** Returns the move of an ai player */
char ai_move(player_t* player)
{
    switch (get_player_ai_type(player)) {
        case 1: return alea_strategy(player);
                break;
        case 2: return glouton_strategy(player);
                break;
        case 3: return hegemonique_strategy(player);
                break;
        case 4: return glouton_prevoyant_strategy(player);
                break;
        default: return 'A';
                 break;
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
             board[i * BOARD_SIZE + j] = create_cell((rand() % NB_COLORS) + 'A');
        }
    }
    set_cell_color(0, BOARD_SIZE-1, get_player_symbol(get_player(0)));
    set_cell_color(BOARD_SIZE -1, 0, get_player_symbol(get_player(1)));
}

/** Update the board */

// Propagate recursively a color from a square over another color
int propagate(char color_covering, int x, int y, char color_covered) {
    set_cell_color(x, y, color_covering);
    set_cell_visited(x, y, 1);
    int modifs = 1;
    if ((x < BOARD_SIZE - 1) && !get_cell_visited(x+1, y)) {
        if ((get_cell_color(x + 1, y) == color_covered) ||(get_cell_color(x + 1, y) == color_covering))
        modifs += (propagate(color_covering, x + 1, y, color_covered));
    }
    if ((x > 0) && !get_cell_visited(x-1, y)) {
        if ((get_cell_color(x - 1, y) == color_covered) || (get_cell_color(x - 1, y) == color_covering))
        modifs += (propagate(color_covering, x - 1, y, color_covered));
    }

    if ((y < BOARD_SIZE - 1) && !get_cell_visited(x, y+1)){
        if ((get_cell_color(x, y + 1) == color_covered) || (get_cell_color(x, y + 1) == color_covering))
        modifs += (propagate(color_covering, x, y + 1, color_covered));
    }
    if ((y > 0) && !get_cell_visited(x, y-1)) {
        if ((get_cell_color(x, y - 1) == color_covered) || (get_cell_color(x, y - 1) == color_covering))
        modifs += (propagate(color_covering, x, y - 1, color_covered));
    }
    return modifs;
}

// Propagate recursively a color from a square over another color
int simulate_propagate(char color_covering, int x, int y, char color_covered, int turn) {
    set_cell_visited(x, y, 1);
    if (turn && !(get_cell_turn_visited(x,y)))set_cell_turn_visited(x, y, turn);
    int cell_owned = 1;
    if ((x < BOARD_SIZE - 1) && !get_cell_visited(x+1, y)) {
        if ( (get_cell_color(x + 1, y) == color_covered) || (get_cell_color(x + 1, y) == color_covering) || (get_cell_turn_visited(x+1,y)) ){
        cell_owned += (simulate_propagate(color_covering, x + 1, y, color_covered, turn));
        }
        else if (!turn) {
            set_cell_visited(x+1, y, 1);
            neighbours_counter(1);
        }
    }
    if ((x > 0) && !get_cell_visited(x-1, y)) {
        if ((get_cell_color(x - 1, y) == color_covered) || (get_cell_color(x - 1, y) == color_covering) || (get_cell_turn_visited(x-1,y)))
        {
            cell_owned += (simulate_propagate(color_covering, x - 1, y, color_covered, turn));
        }
        else if (!turn){
            set_cell_visited(x-1, y, 1);
            neighbours_counter(1);
        }
    }
    if ((y < BOARD_SIZE - 1) && !get_cell_visited(x, y+1)){
        if ((get_cell_color(x, y + 1) == color_covered) || (get_cell_color(x, y + 1) == color_covering) || (get_cell_turn_visited(x, y+1))){
            cell_owned += (simulate_propagate(color_covering, x, y + 1, color_covered, turn));
        }
        else if (!turn) {
            set_cell_visited(x, y+1, 1);
            neighbours_counter(1);
        }
    }
    if ((y > 0) && !get_cell_visited(x, y-1)) {
        if ((get_cell_color(x, y - 1) == color_covered) || (get_cell_color(x, y - 1) == color_covering) || (get_cell_turn_visited(x, y-1))){
            cell_owned += (simulate_propagate(color_covering, x, y - 1, color_covered, turn));
        }
        else if (!turn) {
            set_cell_visited(x, y-1, 1);
            neighbours_counter(1);
        }
    }
    return cell_owned;
}

void update_board(char letter, player_t* player){
    char sym = get_player_symbol(player);
    int x = get_player_init_x(player);
    int y = get_player_init_y(player);

    int modifications = propagate(sym, x, y, letter);
    clean_board(x, y);

    set_player_cell_owned(player, modifications);
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
        printf("AI %d played letter %c\n", get_player_ai_type(player),letter);
    }
    update_board(letter, player);
    print_board();
    for (int i = 0; i<2; i++) {
        printf("Score Player %c = %d , %.2f %% \n", get_player_symbol(get_player(i)), get_player_cell_owned(get_player(i)), (float) 100 * get_player_cell_owned(player_list[i]) / (BOARD_SIZE * BOARD_SIZE));
    }
}

/** Check if the game should end */
int end_game() {
    for (int i = 0; i<2; i++) {
        if (get_player_cell_owned(get_player(i)) * 2 > BOARD_SIZE * BOARD_SIZE) {
            return 0;
        }
    }
    return 1;
}


/************ The tests **************/

/* Tests that the initialization works */
SUT_TEST(init_cell)
{
   char c = get_cell_color(5, 5);
   SUT_CHAR_EQUAL(c, '\0', "Creating the board does not initialize the cells to '\\0' but to '%c'", c);

   return 1;
}

/* Tests that the get_cell and set_cell work */
SUT_TEST(getset_cell)
{
   char c;

   set_cell_color(5, 5, 'A');
   c = get_cell_color(5, 5);
   SUT_CHAR_EQUAL(c, 'A', "Setting a cell to 'A' leads to '%c' as a value instead", c);

   return 1;
}

SUT_TEST_SUITE(board) = {
    SUT_TEST_SUITE_ADD(init_cell),
    SUT_TEST_SUITE_ADD(getset_cell),
    SUT_TEST_SUITE_END
};
