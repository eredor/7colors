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

/** 
 * @param i : the index of a player
 * 
 *@return : the player of index i in player_list */
player_t* get_player(int i) {
    return player_list[i];
}
/** 
 * @param i : the index of a player
 * @param player : a player
 * 
 * Changes the content of index i in player_list by the player  */
void set_player(int i, player_t* player){
    player_list[i] = player;
}

/** Represent a cell of the board*/
struct cell {
    char color;
    int visited;
    int turn_visited;
};

/** Represent the actual current board game */
cell_t* board[BOARD_SIZE * BOARD_SIZE];

/** 
 * @param color : the color of the cell
 * 
 * Create a cell
 */
cell_t* create_cell(char color){
    cell_t* res = malloc(sizeof(cell_t));
    res -> color = color;
    res -> visited = 0;
    res -> turn_visited = 0;
    return res;
}

/** 
 * @param x : the coordinate x of the cell
 * @param y : the coordinate y of the cell 
 * 
 * @return : the color of cell(x,y)
 */
char get_cell_color(int x, int y)
{
    return board[y * BOARD_SIZE + x] -> color;
}

/** 
 * @param x : the coordinate x of the cell
 * @param y : the coordinate y of the cell 
 * @param color : a color
 * 
 * Changes the color of the cell by the one entered in parameter
 */
void set_cell_color(int x, int y, char color)
{
    board[y * BOARD_SIZE + x]->color = color;
}

/** 
 * @param x : the coordinate x of the cell
 * @param y : the coordinate y of the cell 
 * 
 * @return : the attribute visited of cell(x,y)
 */
int get_cell_visited(int x, int y)
{
    return board[y * BOARD_SIZE + x] -> visited;
}

/** 
 * @param x : the coordinate x of the cell
 * @param y : the coordinate y of the cell 
 * @param visited : 1 if the cell has been visited, if not 0
 * 
 * Changes the value of visited of the cell by the one entered in parameter
 */
void set_cell_visited(int x, int y, int visited)
{
    board[y * BOARD_SIZE + x]->visited = visited;
}

/** 
 * @param x : the coordinate x of the cell
 * @param y : the coordinate y of the cell 
 * 
 * @return : the attribute turn_visited of cell(x,y)
 */
int get_cell_turn_visited(int x, int y)
{
    return board[y * BOARD_SIZE + x] -> turn_visited;
}

/** 
 * @param x : the coordinate x of the cell
 * @param y : the coordinate y of the cell 
 * @param turn : the turn number when the cell was visited for the first time
 * 
 * Changes the value of turn_visited of the cell by the one entered in parameter
 */
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

/**
 * @param x : the strating position x of a player
 * @param y : th estrating position y of a player
 * 
 * Reset the value of visited and turn_visited
 */
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

/**
 * @param x : the strating position x of a player
 * @param y : th estrating position y of a player
 * 
 * Reset the value of visited 
 * Reset the value of turn_visited if it matches turn
 */
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

/**
 * @param player : a player
 * 
 * @return : a random letter that will affect the board
 */
char alea_strategy(player_t* player)
{
    int x = get_player_init_x(player);
    int y = get_player_init_y(player);
    char letter = 'A' + (rand() % NB_COLORS);
    while(simulate_propagate(get_player_symbol(player), get_player_init_x(player), get_player_init_y(player), letter, 1,0) == get_player_cell_owned(player)) {
        letter = 'A' + (rand() % NB_COLORS);
        clean_board(x, y);
    }
    clean_board(x, y);
    return letter;
}


/**
 * @param player : a player
 * 
 * @return : the letter that will make the player earns the most cells
 */
char glouton_strategy(player_t* player){
    int x = get_player_init_x(player);
    int y = get_player_init_y(player);
    char letter;
    int max = 0;
    int temp;
    for (char i = 'A'; i < 'A' + NB_COLORS; i++) {
        temp = simulate_propagate(get_player_symbol(player), get_player_init_x(player), get_player_init_y(player), i, 2, 0);
        clean_board(x, y);
        if(temp > max){
            max = temp;
            letter = i;
        }
    }
    return letter;
}

/**
 * @param player : a player
 * 
 * @return : the letter that will make its perimeter the widest
 */
char hegemonique_strategy(player_t* player){
    int x = get_player_init_x(player);
    int y = get_player_init_y(player);
    char letter;
    int max = 0;
    int temp, cells; 
    int max_cells = get_player_cell_owned(player) ;
    for (char i = 'A'; i < 'A' + NB_COLORS; i++) {
        cells = simulate_propagate(get_player_symbol(player), get_player_init_x(player), get_player_init_y(player), i, 3, 0);
        temp = neighbours_counter(1) - 1;
        neighbours_counter(0);
        clean_board(x, y);
        if((temp > max) && (cells > max_cells)){
            max = temp;
            max_cells = cells;
            letter = i;
        }
    }
    return letter;
}


char strategy(player_t* player){
    int x = get_player_init_x(player);
    int y = get_player_init_y(player);
    int ai = get_player_ai_type(player);
    char letter;
    int temp_cells;
    int max_cells = get_player_cell_owned(player);
    int neighbours = 0;
        for (char i = 'A'; i < 'A' + NB_COLORS; i++) {
            temp_cells = simulate_propagate(get_player_symbol(player), x, y, i, ai, 0);
            clean_board(x, y);
        }

    return letter;
}

/**
 * Counter for the hegemonique_strategy
 * 
 * @return : the number of time the function was called since the last reinitialization
 */ 
int neighbours_counter(int i){
    static int res = 0;
    if(i) res++;
    else res = 0;
    return res;
}

/**
 * @param x : the coordinate x of a cell
 * @param y : the coordinate y of a cell
 * @param color : a player color
 * 
 * @return : 1 if the cell(x,y) is surrounded by cells owned by the player
 */ 
int is_landlocked(int x, int y, char color)  {
    if ((x < BOARD_SIZE - 1) && (get_cell_color(x + 1, y) != color)) 
        return 0;
    
    if ((x> 0) && (get_cell_color(x - 1, y) != color)) 
        return 0;
    
    if ((y < BOARD_SIZE - 1) && (get_cell_color(x, y + 1) != color)) 
        return 0;
    
    if ((y> 0) && (get_cell_color(x, y-1) != color)) 
        return 0;
        
    return 1;
}

/**
 * @param player : a player
 * 
 * @return : the letter that will make the player earns the most cells in 2 turn
 */
char glouton_prevoyant_strategy(player_t* player){
    int x = get_player_init_x(player);
    int y = get_player_init_y(player);
    char letter;
    int max = 0;
    int temp, temp2;
    for (char i = 'A'; i < 'A' + NB_COLORS; i++) {
        temp = simulate_propagate(get_player_symbol(player), get_player_init_x(player), get_player_init_y(player), i, 4, 1);
        if(temp != get_player_cell_owned(player)){
            for (char j = 'A'; j < 'A' + NB_COLORS; j++) {
                temp2 = simulate_propagate(get_player_symbol(player), get_player_init_x(player), get_player_init_y(player), j, 4, 2);
                clean_board_turn_visited(x, y, 2);
                if(temp2 > max){
                max = temp2;
                letter = i;
                }
            }
        }
        clean_board(x, y);
    }
    neighbours_counter(0);
    return letter;
}


/** 
 * @param player : an AI player
 * 
 * @return : the letter chosen by player 
 */
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


/** 
 * Initialize the game
 * Ask each player for a symbol
 * Initialize the board
*/
void init_game(){
    srand(time(NULL)); // initialize random seed
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

/** 
 * Initialize the board 
 */
void init_board() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
             board[i * BOARD_SIZE + j] = create_cell((rand() % NB_COLORS) + 'A');
        }
    }
    set_cell_color(0, BOARD_SIZE-1, get_player_symbol(get_player(0)));
    set_cell_color(BOARD_SIZE -1, 0, get_player_symbol(get_player(1)));
}

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
int simulate_propagate(char color, int x, int y, char letter, int ai, int turn) {
    set_cell_visited(x, y, 1);
    if (turn && !(get_cell_turn_visited(x,y))) set_cell_turn_visited(x, y, turn);
    int cells_owned = 1;
    if ((x < BOARD_SIZE - 1) && !get_cell_visited(x+1, y)) {
        if ((get_cell_color(x+1, y) == color) || (get_cell_color(x+1, y) == letter) || (get_cell_turn_visited(x+1, y))){
            cells_owned += (simulate_propagate(color, x+1, y, letter, ai, turn));
        }
        else if (ai == 3){
            set_cell_visited(x+1, y, 1);
            if(!is_landlocked(x+1,y,color))
            neighbours_counter(1);
        }
    }
    if ((x > 0) && !get_cell_visited(x-1, y)) {
        if ((get_cell_color(x-1, y) == color) || (get_cell_color(x-1, y) == letter) || (get_cell_turn_visited(x-1, y))){
            cells_owned += (simulate_propagate(color, x-1, y, letter, ai, turn));
        }
        else if (ai == 3){
            set_cell_visited(x-1, y, 1);
            if(!is_landlocked(x-1,y,color))
            neighbours_counter(1);
        }
    }
    if ((y < BOARD_SIZE - 1) && !get_cell_visited(x, y+1)){
        if ((get_cell_color(x, y+1) == color) || (get_cell_color(x, y+1) == letter) || (get_cell_turn_visited(x, y+1))){
            cells_owned += (simulate_propagate(color, x, y+1, letter, ai, turn));
        }
        else if (ai == 3){
            set_cell_visited(x, y+1, 1);
            if(!is_landlocked(x,y+1,color))
            neighbours_counter(1);
        }
    }
    if ((y > 0) && !get_cell_visited(x, y-1)) {
        if ((get_cell_color(x, y-1) == color) || (get_cell_color(x, y-1) == letter)|| (get_cell_turn_visited(x, y-1))){
            cells_owned += (simulate_propagate(color, x, y-1, letter, ai, turn));
        }
        else if (ai == 3){
            set_cell_visited(x, y-1, 1);
            if(!is_landlocked(x,y-1,color))
            neighbours_counter(1);
        }
    }
    return cells_owned;
}


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
int propagate(char color, int x, int y, char letter) {
    set_cell_color(x, y, color);
    set_cell_visited(x, y, 1);
    int cells_owned = 1;
    if ((x < BOARD_SIZE - 1) && !get_cell_visited(x+1, y)) {
        if ((get_cell_color(x + 1, y) == letter) ||(get_cell_color(x + 1, y) == color))
        cells_owned += (propagate(color, x + 1, y, letter));
    }
    if ((x > 0) && !get_cell_visited(x-1, y)) {
        if ((get_cell_color(x - 1, y) == letter) || (get_cell_color(x - 1, y) == color))
        cells_owned += (propagate(color, x - 1, y, letter));
    }

    if ((y < BOARD_SIZE - 1) && !get_cell_visited(x, y+1)){
        if ((get_cell_color(x, y + 1) == letter) || (get_cell_color(x, y + 1) == color))
        cells_owned += (propagate(color, x, y + 1, letter));
    }
    if ((y > 0) && !get_cell_visited(x, y-1)) {
        if ((get_cell_color(x, y - 1) == letter) || (get_cell_color(x, y - 1) == color))
        cells_owned += (propagate(color, x, y - 1, letter));
    }
    return cells_owned;
}



/**
 * @param letter : the letter played by the player
 * @param player : the player
 * 
 * Update the board and the player's data 
 */
void update_board(char letter, player_t* player){
    char sym = get_player_symbol(player);
    int x = get_player_init_x(player);
    int y = get_player_init_y(player);

    int modifications = propagate(sym, x, y, letter);
    clean_board(x, y);

    set_player_cell_owned(player, modifications);
}

/**
 * @param player : the player whose turn it is 
 * 
 * Play a turn of the game
 */
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

/** 
 * Check if the game should end 
 * 
 * @return : 0 if the game continue
 */
int end_game() {
    for (int i = 0; i<2; i++) {
        if (get_player_cell_owned(get_player(i)) * 2 > BOARD_SIZE * BOARD_SIZE) {
            //printf("Joueur %d a gagné ! \n", i+1);
            return i + 1;
        }
    }
    return 0;
}


/** 
 * @param ai_type1 : the ai type of player 1
 * @param ai_type2 : the ai type of player 2 
 * 
 * Fight between AIs implementation 
 */
void init_game_AI(int ai_type1, int ai_type2) {
    for (int i = 0; i < 2; i++) {
        int x_init = i * (BOARD_SIZE - 1);
        int y_init = (1 - i) * (BOARD_SIZE - 1);

        if (i == 0){
            set_player(i, add_player(48 + i, ai_type1, x_init, y_init));
        } else {
            set_player(i, add_player(48 + i, ai_type2, x_init, y_init));
        }

    }
    init_board();
}


/**
 * @param player : the player whose turn it is 
 * 
 * Play a turn of the game
 */
void game_turn_AI(player_t* player){
    char letter = ai_move(player);
    update_board(letter, player);
}

/** 
 * @param ai_type1 : the ai type of player 1
 * @param ai_type2 : the ai type of player 2
 * @param nb_games : number of games played
 * 
 * Tournament implementation 
 * 
 * @return : number of victory of player 1
 */
int tournament_AI(int ai_type1, int ai_type2, int nb_games) {
    srand(time(NULL)); // initialize random seed
    int victory_1 = 0;

    for (int i = 0; i < nb_games; i++) {
        init_game_AI(ai_type1, ai_type2);

        int turn = 0;
        while(!end_game()){
           game_turn_AI(get_player(turn % 2));
           turn++;
        }

        if(end_game() == 1) victory_1 += 1;
    }
    return victory_1;
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
