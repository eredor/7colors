/* Template of the 7 wonders of the world of the 7 colors assigment */
/* Implentation of the board module */

#include <stdio.h>            /* Import printf */
#include "board.h"            /* Enforce that the header file matches the declarations */
#include "simple_unit_test.h" /* Import the testing infrastructure */
#include <time.h>             /* Import time to initialize random seed */
#include "player.h"           /* Import player module */
#include "coordinates.h"      /* Import coordinates module */

/* Note: This template comes with several global definitions. For now.
 *
 * Such globals are usually discouraged, but having a few of them is OK in a C program.
 * At first, no dinosaure will get you if you use globals, but you should seek for a better
 * solution for your final version.
 *
 * Encapuslating them in an appropriate data structure, and removing all globals would be a must.
 * Plus, this path often leads to simpler code, that is easier to test.
 */

/* We want a 30x30 board game by default 
For the test we used a 5x5 board*/
#define BOARD_SIZE 30
/* SPOT for the number of colors */
#define NB_COLORS 7

/** List of players*/
player_t *player_list[2];

/** 
 * @param i : the index of a player
 * 
 *@return : the player of index i in player_list */
player_t *get_player(int i)
{
    return player_list[i];
}
/** 
 * @param i : the index of a player
 * @param player : a player
 * 
 * Changes the content of index i in player_list by the player  */
void set_player(int i, player_t *player)
{
    player_list[i] = player;
}

/** Represent a cell of the board*/
struct cell
{
    char color;
    int visited;
    int turn_visited;
};

/** Represent the actual current board game */
cell_t *board[BOARD_SIZE * BOARD_SIZE];
cell_t *board_test[BOARD_SIZE * BOARD_SIZE];

/** 
 * @param color : the color of the cell
 * 
 * Create a cell
 */
cell_t *create_cell(char color)
{
    cell_t *res = malloc(sizeof(cell_t));
    res->color = color;
    res->visited = 0;
    res->turn_visited = 0;
    return res;
}

/**
 * @param cell : a cell
 * 
 * Free the memory
 */
void delete_cell(cell_t *cell)
{
    free(cell);
}

/** 
 * @param x : the coordinate x of the cell
 * @param y : the coordinate y of the cell 
 * 
 * @return : the color of cell(x,y)
 */
char get_cell_color(int x, int y)
{
    return board[y * BOARD_SIZE + x]->color;
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
    return board[y * BOARD_SIZE + x]->visited;
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
    return board[y * BOARD_SIZE + x]->turn_visited;
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

/**
 * Free the memory of all of the board cells
 */
void delete_board()
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            delete_cell(board[j * BOARD_SIZE + i]);
        }
    }
}

/** Prints the current state of the board on screen
 *
 * It would be nicer to do this with ncurse or even SFML or SDL,
 * but this is not required in this assignment. See the extensions.
 */
void print_board(void)
{
    int i, j;
    for (i = 0; i < BOARD_SIZE; i++)
    {
        for (j = 0; j < BOARD_SIZE; j++)
        {
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
void clean_board(int x, int y)
{
    set_cell_visited(x, y, 0);
    set_cell_turn_visited(x, y, 0);
    if ((x < BOARD_SIZE - 1) && (get_cell_visited(x + 1, y) || get_cell_turn_visited(x + 1, y)))
    {
        clean_board(x + 1, y);
    }
    if ((x > 0) && (get_cell_visited(x - 1, y) || get_cell_turn_visited(x - 1, y)))
    {
        clean_board(x - 1, y);
    }
    if ((y < BOARD_SIZE - 1) && (get_cell_visited(x, y + 1) || get_cell_turn_visited(x, y + 1)))
    {
        clean_board(x, y + 1);
    }
    if ((y > 0) && (get_cell_visited(x, y - 1) || get_cell_turn_visited(x, y - 1)))
    {
        clean_board(x, y - 1);
    }
}

/**
 * @param x : the strating position x of a player
 * @param y : th estrating position y of a player
 * 
 * Reset the value of visited
 */
void clean_board_visited(int x, int y)
{
    set_cell_visited(x, y, 0);
    if ((x < BOARD_SIZE - 1) && get_cell_visited(x + 1, y))
    {
        clean_board_visited(x + 1, y);
    }
    if ((x > 0) && get_cell_visited(x - 1, y))
    {
        clean_board_visited(x - 1, y);
    }
    if ((y < BOARD_SIZE - 1) && get_cell_visited(x, y + 1))
    {
        clean_board_visited(x, y + 1);
    }
    if ((y > 0) && get_cell_visited(x, y - 1))
    {
        clean_board_visited(x, y - 1);
    }
}

/**
 * @param x : the strating position x of a player
 * @param y : th estrating position y of a player
 * 
 * Reset the value of visited 
 * Reset the value of turn_visited if it matches turn
 */
void clean_board_turn_visited(int x, int y, int turn)
{
    set_cell_visited(x, y, 0);
    if (get_cell_turn_visited(x, y) == turn)
        set_cell_turn_visited(x, y, 0);
    if ((x < BOARD_SIZE - 1) && ((get_cell_turn_visited(x + 1, y) == turn) || get_cell_visited(x + 1, y)))
    {
        clean_board_turn_visited(x + 1, y, turn);
    }
    if ((x > 0) && ((get_cell_turn_visited(x - 1, y) == turn) || get_cell_visited(x - 1, y)))
    {
        clean_board_turn_visited(x - 1, y, turn);
    }
    if ((y < BOARD_SIZE - 1) && ((get_cell_turn_visited(x, y + 1) == turn) || get_cell_visited(x, y + 1)))
    {
        clean_board_turn_visited(x, y + 1, turn);
    }
    if ((y > 0) && ((get_cell_turn_visited(x, y - 1) == turn) || get_cell_visited(x, y - 1)))
    {
        clean_board_turn_visited(x, y - 1, turn);
    }
}

/** Functions for AI strategies */

/**
 * @param player : a player
 * 
 * @return : a random letter that will affect the board
 */
char alea_strategy(player_t *player)
{
    int x = get_player_init_x(player);
    int y = get_player_init_y(player);
    char color = get_player_symbol(player);
    int cells_owned = get_player_cell_owned(player);
    char letter = 'A' + (rand() % NB_COLORS);
    while (sim_propagate(color, x, y, letter, 1, 0) == cells_owned)
    {
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
char glouton_strategy(player_t *player)
{
    int x = get_player_init_x(player);
    int y = get_player_init_y(player);
    int color = get_player_symbol(player);
    char letter;
    int max_cells = 0;
    int temp_cells;
    for (char i = 'A'; i < 'A' + NB_COLORS; i++)
    {
        temp_cells = sim_propagate(color, x, y, i, 2, 0);
        clean_board(x, y);
        if (temp_cells > max_cells)
        {
            max_cells = temp_cells;
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
char hegemonique_strategy(player_t *player)
{
    int x = get_player_init_x(player);
    int y = get_player_init_y(player);
    int color = get_player_symbol(player);
    char letter;
    int max_perim = 0;
    int min_cells = get_player_cell_owned(player);
    int temp_perim, temp_cells;
    for (char i = 'A'; i < 'A' + NB_COLORS; i++)
    {
        temp_cells = sim_propagate(color, x, y, i, 3, 0);
        temp_perim = neighbours_counter(1) - 1;
        neighbours_counter(0);
        clean_board(x, y);
        if ((temp_perim > max_perim) && (temp_cells > min_cells))
        {
            max_perim = temp_perim;
            letter = i;
        }
    }
    return letter;
}

/**
 * Counter for the hegemonique_strategy
 * 
 * @return : the number of time the function was called since the last reinitialization
 */
int neighbours_counter(int i)
{
    static int res = 0;
    if (i) {
        res++;
    }
    else{
        res = 0;
    }
    return res;
}

/**
 * @param x : the coordinate x of a cell
 * @param y : the coordinate y of a cell
 * @param color : a player color
 * 
 * @return : 1 if the cell(x,y) is surrounded by cells owned by the player
 */
int is_landlocked(int x, int y, char color)
{
    if ((x < BOARD_SIZE - 1) && (get_cell_color(x + 1, y) != color))
        return 0;

    if ((x > 0) && (get_cell_color(x - 1, y) != color))
        return 0;

    if ((y < BOARD_SIZE - 1) && (get_cell_color(x, y + 1) != color))
        return 0;

    if ((y > 0) && (get_cell_color(x, y - 1) != color))
        return 0;

    return 1;
}

/**
 * @param player : a player
 * 
 * @return : the letter that will make the player earns the most cells in 2 turn
 */
char glouton_prevoyant_strategy(player_t *player)
{
    int x = get_player_init_x(player);
    int y = get_player_init_y(player);
    char color = get_player_symbol(player);
    char letter;
    int max_cells1 = 0;
    int max_cells2 = 0;
    int temp_cells_1, temp_cells_2;
    for (char i = 'A'; i < 'A' + NB_COLORS; i++)
    {
        temp_cells_1 = sim_propagate(color, x, y, i, 4, 1);
        clean_board_visited(x, y);
        if (temp_cells_1 != get_player_cell_owned(player))
        {
            for (char j = 'A'; j < 'A' + NB_COLORS; j++)
            {
                if (i != j)
                {
                    temp_cells_2 = sim_propagate(color, x, y, j, 4, 2);
                    clean_board_turn_visited(x, y, 2);
                    if (temp_cells_2 > max_cells2)
                    {
                        max_cells1 = temp_cells_1;
                        max_cells2 = temp_cells_2;
                        letter = i;
                    }
                    else if ((temp_cells_2 == max_cells2) && (temp_cells_1 > max_cells1))
                    {
                        max_cells1 = temp_cells_1;
                        max_cells2 = temp_cells_2;
                        letter = i;
                    }
                }
            }
        }
        clean_board(x, y);
    }
    return letter;
}

/** 
 * @param player : an AI player
 * 
 * @return : the letter chosen by player 
 */
char ai_move(player_t *player)
{
    switch (get_player_ai_type(player))
    {
    case 1:
        return alea_strategy(player);
        break;
    case 2:
        return glouton_strategy(player);
        break;
    case 3:
        return hegemonique_strategy(player);
        break;
    case 4:
        return glouton_prevoyant_strategy(player);
        break;
    default:
        return 'A';
        break;
    }
}

/** 
 * Initialize the game
 * Ask each player for a symbol
 * Initialize the board
*/
void init_game()
{
    srand(time(NULL)); // initialize random seed
    char symbol, c;
    int ai_type;
    for (int i = 0; i < 2; i++)
    {
        int x_init = i * (BOARD_SIZE - 1);
        int y_init = (1 - i) * (BOARD_SIZE - 1);

        printf("Player %d what type of AI are you ? \n", i + 1);
        scanf("%d", &ai_type);
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
        printf("Player %d enter a symbol \n", i + 1);
        scanf("%c", &symbol);
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }

        set_player(i, add_player(symbol, ai_type, x_init, y_init));
    }
    init_board();
}

/** 
 * Initialize the board 
 */
void init_board()
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            board[i * BOARD_SIZE + j] = create_cell((rand() % NB_COLORS) + 'A');
        }
    }
    set_cell_color(0, BOARD_SIZE - 1, get_player_symbol(get_player(0)));
    set_cell_color(BOARD_SIZE - 1, 0, get_player_symbol(get_player(1)));
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
int sim_propagate(char color, int x, int y, char letter, int ai, int turn)
{
    set_cell_visited(x, y, 1);
    if (turn && !(get_cell_turn_visited(x, y)))
        set_cell_turn_visited(x, y, turn);
    int cells_owned = 1;
    if ((x < BOARD_SIZE - 1) && !get_cell_visited(x + 1, y))
    {
        if ((get_cell_color(x + 1, y) == color) || (get_cell_color(x + 1, y) == letter) || (get_cell_turn_visited(x + 1, y)))
        {
            cells_owned += (sim_propagate(color, x + 1, y, letter, ai, turn));
        }
        else if (ai == 3)
        {
            set_cell_visited(x + 1, y, 1);
            if (!is_landlocked(x + 1, y, color))
                neighbours_counter(1);
        }
    }
    if ((x > 0) && !get_cell_visited(x - 1, y))
    {
        if ((get_cell_color(x - 1, y) == color) || (get_cell_color(x - 1, y) == letter) || (get_cell_turn_visited(x - 1, y)))
        {
            cells_owned += (sim_propagate(color, x - 1, y, letter, ai, turn));
        }
        else if (ai == 3)
        {
            set_cell_visited(x - 1, y, 1);
            if (!is_landlocked(x - 1, y, color))
                neighbours_counter(1);
        }
    }
    if ((y < BOARD_SIZE - 1) && !get_cell_visited(x, y + 1))
    {
        if ((get_cell_color(x, y + 1) == color) || (get_cell_color(x, y + 1) == letter) || (get_cell_turn_visited(x, y + 1)))
        {
            cells_owned += (sim_propagate(color, x, y + 1, letter, ai, turn));
        }
        else if (ai == 3)
        {
            set_cell_visited(x, y + 1, 1);
            if (!is_landlocked(x, y + 1, color))
                neighbours_counter(1);
        }
    }
    if ((y > 0) && !get_cell_visited(x, y - 1))
    {
        if ((get_cell_color(x, y - 1) == color) || (get_cell_color(x, y - 1) == letter) || (get_cell_turn_visited(x, y - 1)))
        {
            cells_owned += (sim_propagate(color, x, y - 1, letter, ai, turn));
        }
        else if (ai == 3)
        {
            set_cell_visited(x, y - 1, 1);
            if (!is_landlocked(x, y - 1, color))
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
int propagate(char color, int x, int y, char letter)
{
    set_cell_color(x, y, color);
    set_cell_visited(x, y, 1);
    int cells_owned = 1;
    if ((x < BOARD_SIZE - 1) && !get_cell_visited(x + 1, y))
    {
        if ((get_cell_color(x + 1, y) == letter) || (get_cell_color(x + 1, y) == color))
            cells_owned += (propagate(color, x + 1, y, letter));
    }
    if ((x > 0) && !get_cell_visited(x - 1, y))
    {
        if ((get_cell_color(x - 1, y) == letter) || (get_cell_color(x - 1, y) == color))
            cells_owned += (propagate(color, x - 1, y, letter));
    }

    if ((y < BOARD_SIZE - 1) && !get_cell_visited(x, y + 1))
    {
        if ((get_cell_color(x, y + 1) == letter) || (get_cell_color(x, y + 1) == color))
            cells_owned += (propagate(color, x, y + 1, letter));
    }
    if ((y > 0) && !get_cell_visited(x, y - 1))
    {
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
void update_board(char letter, player_t *player)
{
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
void game_turn(player_t *player)
{
    char letter, c;
    if (get_player_ai_type(player) == 0)
    {
        printf("Player %c enter a letter\n", get_player_symbol(player));
        scanf("%c", &letter);
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
    }
    else
    {
        letter = ai_move(player);
        printf("AI %d played letter %c\n", get_player_ai_type(player), letter);
    }
    update_board(letter, player);
    print_board();
    for (int i = 0; i < 2; i++)
    {
        printf("Score Player %c = %d , %.2f %% \n", get_player_symbol(get_player(i)), get_player_cell_owned(get_player(i)), (float)100 * get_player_cell_owned(player_list[i]) / (BOARD_SIZE * BOARD_SIZE));
    }
}

/** 
 * Check if the game should end 
 * 
 * @return : 0 if the game continue
 */
int end_game()
{
    for (int i = 0; i < 2; i++)
    {
        if (get_player_cell_owned(get_player(i)) * 2 > BOARD_SIZE * BOARD_SIZE)
        {
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
void init_game_AI(int ai_type1, int ai_type2)
{
    for (int i = 0; i < 2; i++)
    {
        int x_init = i * (BOARD_SIZE - 1);
        int y_init = (1 - i) * (BOARD_SIZE - 1);

        if (i == 0)
        {
            set_player(i, add_player('+', ai_type1, x_init, y_init));
        }
        else
        {
            set_player(i, add_player('-', ai_type2, x_init, y_init));
        }
    }
    init_board();
}

/**
 * @param player : the player whose turn it is 
 * 
 * Play a turn of the game
 */
void game_turn_AI(player_t *player)
{
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
int tournament_AI(int ai_type1, int ai_type2, int nb_games)
{
    srand(time(NULL)); // initialize random seed
    int victory_1 = 0;

    for (int i = 0; i < nb_games; i++)
    {
        init_game_AI(ai_type1, ai_type2);

        int turn = 0;
        while (!end_game())
        {
            game_turn_AI(get_player(turn % 2));
            turn++;
        }

        if (end_game() == 1)
            victory_1 += 1;
        delete_player(player_list[0]);
        delete_player(player_list[1]);
        delete_board();
    }
    return victory_1;
}

/************ The tests **************/

/* Tests player functions work */
SUT_TEST(get_player_symbol)
{
    player_t *player = add_player('+', 0, 3, 1);
    char c = get_player_symbol(player);
    SUT_CHAR_EQUAL(c, '+', "The player's symbol should be '+' but is '%c'", c);
    delete_player(player);

    return 1;
}

SUT_TEST(get_player_ai_type)
{
    player_t *player = add_player('+', 0, 3, 1);
    int i = get_player_ai_type(player);
    SUT_CHAR_EQUAL(i, 0, "The player's ai should be 0 but is '%d'", i);
    delete_player(player);

    return 1;
}

SUT_TEST(get_player_init_x)
{
    player_t *player = add_player('+', 0, 3, 1);
    int i = get_player_init_x(player);
    SUT_CHAR_EQUAL(i, 3, "The player's x position should be 3 but is '%d'", i);
    delete_player(player);

    return 1;
}

SUT_TEST(get_player_init_y)
{
    player_t *player = add_player('+', 0, 3, 1);
    int i = get_player_init_y(player);
    SUT_CHAR_EQUAL(i, 1, "The player's y postion should be 1 but is '%d'", i);
    delete_player(player);

    return 1;
}

SUT_TEST(get_player_cell_owned)
{
    player_t *player = add_player('+', 0, 3, 1);
    int i = get_player_cell_owned(player);
    SUT_CHAR_EQUAL(i, 1, "The player's number of cells owned should be 1 but is '%d'", i);

    delete_player(player);
    return 1;
}

SUT_TEST(set_player_cell_owned)
{
    player_t *player = add_player('+', 0, 3, 1);
    set_player_cell_owned(player, 124);
    int i = get_player_cell_owned(player);
    SUT_CHAR_EQUAL(i, 124, "The player's number of cells owned should be 124 but is '%d'", i);

    delete_player(player);
    return 1;
}

/* Tests that cell functions work */
SUT_TEST(get_cell_color)
{
    cell_t *cell = create_cell('A');
    board[2 * BOARD_SIZE + 2] = cell;
    char c = get_cell_color(2, 2);
    SUT_CHAR_EQUAL(c, 'A', "The cell color should be 'A' but is '%c'", c);
    delete_cell(cell);

    return 1;
}

SUT_TEST(getset_cell_color)
{
    char c;
    cell_t *cell = create_cell('C');
    board[2 * BOARD_SIZE + 2] = cell;
    set_cell_color(2, 2, 'A');
    c = get_cell_color(2, 2);
    SUT_CHAR_EQUAL(c, 'A', "Setting a cell to 'A' leads to '%c' as a value instead", c);
    delete_cell(cell);
    return 1;
}

SUT_TEST(get_cell_visited)
{
    cell_t *cell = create_cell('A');
    board[2 * BOARD_SIZE + 2] = cell;
    int i = get_cell_visited(2, 2);
    SUT_CHAR_EQUAL(i, 0, "The cell's visited attribute should be 0 but is '%d'", i);
    delete_cell(cell);

    return 1;
}

SUT_TEST(getset_cell_visited)
{
    cell_t *cell = create_cell('A');
    board[2 * BOARD_SIZE + 2] = cell;
    set_cell_visited(2, 2, 1);
    int i = get_cell_visited(2, 2);
    SUT_CHAR_EQUAL(i, 1, "The cell's visited attribute should be 1 but is '%d'", i);
    delete_cell(cell);

    return 1;
}

SUT_TEST(get_cell_turn_visited)
{
    cell_t *cell = create_cell('A');
    board[2 * BOARD_SIZE + 2] = cell;
    int i = get_cell_turn_visited(2, 2);
    SUT_CHAR_EQUAL(i, 0, "The cell's turn_visited attribute should be 0 but is '%d'", i);
    delete_cell(cell);

    return 1;
}

SUT_TEST(getset_cell_turn_visited)
{
    cell_t *cell = create_cell('A');
    board[2 * BOARD_SIZE + 2] = cell;
    set_cell_turn_visited(2, 2, 3);
    int i = get_cell_turn_visited(2, 2);
    SUT_CHAR_EQUAL(i, 3, "The cell's turn_visited attribute should be 3 but is '%d'", i);
    delete_cell(cell);

    return 1;
}

/** Tests for the board */
SUT_TEST(init_board)
{
    srand(time(NULL));
    set_player(0, add_player('+', 2, 0, BOARD_SIZE - 1));
    set_player(1, add_player('-', 3, BOARD_SIZE - 1, 0));
    init_board();
    char c1 = get_cell_color(0, BOARD_SIZE - 1);
    char c2 = get_cell_color(BOARD_SIZE - 1, 0);
    SUT_CHAR_EQUAL(c1, '+', "The cell's color should be '+' but is '%s'", c1);
    SUT_CHAR_EQUAL(c2, '-', "The cell's color should be '-' but is '%s'", c2);

    return 1;
}

SUT_TEST(clean_board)
{
    // Using the board and players initialized in SUT_TEST(init_board)
    set_cell_color(0, 0, 'A');
    set_cell_color(0, 1, 'B');
    set_cell_color(0, 2, 'F');
    set_cell_color(0, 3, 'C');
    set_cell_color(0, 4, '+');
    set_cell_color(1, 0, 'F');
    set_cell_color(1, 1, 'F');
    set_cell_color(1, 2, 'F');
    set_cell_color(1, 3, 'G');
    set_cell_color(1, 4, 'D');
    set_cell_color(2, 0, 'C');
    set_cell_color(2, 1, 'G');
    set_cell_color(2, 2, 'B');
    set_cell_color(2, 3, 'A');
    set_cell_color(2, 4, 'D');
    set_cell_color(3, 0, 'B');
    set_cell_color(3, 1, 'E');
    set_cell_color(3, 2, 'A');
    set_cell_color(3, 3, 'E');
    set_cell_color(3, 4, 'C');
    set_cell_color(4, 0, '-');
    set_cell_color(4, 1, 'D');
    set_cell_color(4, 2, 'A');
    set_cell_color(4, 3, 'C');
    set_cell_color(4, 4, 'B');

    char colors[25] = {'A', 'B', 'F', 'C', '+',
                       'F', 'F', 'F', 'G', 'D',
                       'C', 'G', 'B', 'A', 'D',
                       'B', 'E', 'A', 'E', 'C',
                       '-', 'D', 'A', 'C', 'B'};

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            board_test[j * BOARD_SIZE + i] = create_cell(colors[i * BOARD_SIZE + j]);
        }
    }

    set_cell_visited(0, 4, 1);
    set_cell_visited(1, 4, 1);
    set_cell_visited(2, 4, 1);
    set_cell_visited(3, 4, 1);
    set_cell_visited(2, 3, 1);
    set_cell_visited(1, 3, 1);
    set_cell_visited(0, 3, 1);

    set_cell_turn_visited(0, 4, 1);
    set_cell_turn_visited(1, 4, 2);
    set_cell_turn_visited(2, 4, 3);
    set_cell_turn_visited(3, 4, 1);
    set_cell_turn_visited(2, 3, 4);

    clean_board(0, 4);

    int turn, visited, expected_turn, expected_visited;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            visited = get_cell_visited(i, j);
            turn = get_cell_turn_visited(i, j);
            expected_visited = board_test[j * BOARD_SIZE + i]->visited;
            expected_turn = board_test[j * BOARD_SIZE + i]->turn_visited;
            SUT_INT_EQUAL(visited, expected_visited, "The cell's visited attribute should be %d but is %d", expected_visited, visited);
            SUT_INT_EQUAL(turn, expected_turn, "The cell's turn_visited attribute should be %d but is %d", expected_turn, turn);
        }
    }

    return 1;
}

SUT_TEST(clean_board_visited)
{
    set_cell_visited(4, 0, 1);
    set_cell_visited(4, 1, 1);
    set_cell_visited(4, 2, 1);
    set_cell_visited(3, 2, 1);
    set_cell_visited(2, 2, 1);
    set_cell_visited(3, 0, 1);

    clean_board_visited(4, 0);

    int visited, expected_visited;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            visited = get_cell_visited(i, j);
            expected_visited = board_test[j * BOARD_SIZE + i]->visited;
            SUT_INT_EQUAL(visited, expected_visited, "The cell's visited attribute should be %d but is %d", expected_visited, visited);
        }
    }
    return 1;
}

SUT_TEST(clean_board_turn_visited)
{
    set_cell_visited(4, 0, 1);
    set_cell_visited(4, 1, 1);
    set_cell_visited(4, 2, 1);
    set_cell_visited(3, 2, 1);
    set_cell_visited(2, 2, 1);
    set_cell_visited(3, 0, 1);

    set_cell_turn_visited(4, 0, 1);
    set_cell_turn_visited(4, 1, 1);
    set_cell_turn_visited(4, 2, 2);
    set_cell_turn_visited(3, 2, 2);
    set_cell_turn_visited(2, 2, 3);
    set_cell_turn_visited(3, 0, 3);

    clean_board_turn_visited(4, 0, 3);

    board_test[0 * BOARD_SIZE + 4]->turn_visited = 1;
    board_test[1 * BOARD_SIZE + 4]->turn_visited = 1;
    board_test[2 * BOARD_SIZE + 4]->turn_visited = 2;
    board_test[2 * BOARD_SIZE + 3]->turn_visited = 2;
    int turn, visited, expected_turn, expected_visited;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            visited = get_cell_visited(i, j);
            turn = get_cell_turn_visited(i, j);
            expected_visited = board_test[j * BOARD_SIZE + i]->visited;
            expected_turn = board_test[j * BOARD_SIZE + i]->turn_visited;
            SUT_INT_EQUAL(visited, expected_visited, "The cell's visited attribute should be %d but is %d", expected_visited, visited);
            SUT_INT_EQUAL(turn, expected_turn, "The cell's turn_visited attribute should be %d but is %d", expected_turn, turn);
        }
    }
    clean_board(4, 0);
    board_test[0 * BOARD_SIZE + 4]->turn_visited = 0;
    board_test[1 * BOARD_SIZE + 4]->turn_visited = 0;
    board_test[2 * BOARD_SIZE + 4]->turn_visited = 0;
    board_test[2 * BOARD_SIZE + 3]->turn_visited = 0;

    return 1;
}

SUT_TEST(propagate)
{
    char c, expected;
    int nb_cells;

    nb_cells = propagate('-', BOARD_SIZE - 1, 0, 'A');
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            c = get_cell_color(i, j);
            expected = board_test[j * BOARD_SIZE + i]->color;
            SUT_CHAR_EQUAL(c, expected, "The cell color should be %c but is '%c'", expected, c);
        }
    }
    clean_board(0, BOARD_SIZE - 1);
    SUT_INT_EQUAL(nb_cells, 1, "The cell number should be 1 but is '%d'", nb_cells);

    board_test[4 * BOARD_SIZE + 1]->color = '+';
    board_test[4 * BOARD_SIZE + 2]->color = '+';
    nb_cells = propagate('+', 0, BOARD_SIZE - 1, 'D');
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            c = get_cell_color(i, j);
            expected = board_test[j * BOARD_SIZE + i]->color;
            SUT_CHAR_EQUAL(c, expected, "The cell color should be %c but is '%s'", expected, c);
        }
    }
    clean_board(0, BOARD_SIZE - 1);
    SUT_INT_EQUAL(nb_cells, 3, "The cell number should be 3 but is '%d'", nb_cells);

    board_test[3 * BOARD_SIZE + 0]->color = '+';
    board_test[4 * BOARD_SIZE + 3]->color = '+';
    nb_cells = propagate('+', 0, BOARD_SIZE - 1, 'C');
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            c = get_cell_color(i, j);
            expected = board_test[j * BOARD_SIZE + i]->color;
            SUT_CHAR_EQUAL(c, expected, "The cell color should be %c but is '%s'", expected, c);
        }
    }
    clean_board(0, BOARD_SIZE - 1);
    SUT_INT_EQUAL(nb_cells, 5, "The cell number should be 5 but is '%d'", nb_cells);
    return 1;
}

SUT_TEST(update_board)
{
    char c, expected;

    update_board('D', get_player(1));
    board_test[1 * BOARD_SIZE + 4]->color = '-';
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            c = get_cell_color(i, j);
            expected = board_test[j * BOARD_SIZE + i]->color;
            SUT_CHAR_EQUAL(c, expected, "The cell color should be %c but is '%c'", expected, c);
        }
    }
    clean_board(0, BOARD_SIZE - 1);
    int nb_cells = get_player_cell_owned(get_player(1));
    SUT_INT_EQUAL(nb_cells, 2, "The number of cells should be 2 but is '%d'", nb_cells);

    update_board('F', get_player(1));
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            c = get_cell_color(i, j);
            expected = board_test[j * BOARD_SIZE + i]->color;
            SUT_CHAR_EQUAL(c, expected, "The cell color should be %c but is '%c'", expected, c);
        }
    }
    clean_board(0, BOARD_SIZE - 1);
    nb_cells = get_player_cell_owned(get_player(1));
    SUT_INT_EQUAL(nb_cells, 2, "The number of cells should be 2 but is '%d'", nb_cells);

    set_player_cell_owned(get_player(1), 1);
    return 1;
}

SUT_TEST(end_game)
{
    int res = end_game();
    SUT_INT_EQUAL(res, 0, "The result should be 0 but is '%d'", res);

    set_player_cell_owned(get_player(1), 15);
    res = end_game();
    SUT_INT_EQUAL(res, 2, "The result should be 2 but is '%d'", res);

    set_player_cell_owned(get_player(1), 1);
    return 1;
}
/** Tests for the AI strategy */
SUT_TEST(sim_propagate)
{
    set_cell_color(0, 3, 'C');
    set_cell_color(1, 4, 'D');
    set_cell_color(2, 4, 'D');
    set_cell_color(3, 4, 'C');
    set_cell_color(4, 1, 'D');

    board_test[4 * BOARD_SIZE + 1]->color = 'D';
    board_test[4 * BOARD_SIZE + 2]->color = 'D';
    board_test[3 * BOARD_SIZE + 0]->color = 'C';
    board_test[4 * BOARD_SIZE + 3]->color = 'C';
    board_test[1 * BOARD_SIZE + 4]->color = 'D';

    int nb_cells;

    nb_cells = sim_propagate('-', BOARD_SIZE - 1, 0, 'A', 1, 0);
    clean_board(0, BOARD_SIZE - 1);
    SUT_INT_EQUAL(nb_cells, 1, "The number of cells should be 1 but is '%d'", nb_cells);

    nb_cells = sim_propagate('+', 0, BOARD_SIZE - 1, 'D', 1, 0);
    clean_board(0, BOARD_SIZE - 1);
    SUT_INT_EQUAL(nb_cells, 3, "The number of cells should be 3 but is '%d'", nb_cells);

    propagate('+', 0, BOARD_SIZE - 1, 'D');
    clean_board(0, BOARD_SIZE - 1);
    nb_cells = sim_propagate('+', 0, BOARD_SIZE - 1, 'C', 3, 0);
    clean_board(0, BOARD_SIZE - 1);
    SUT_INT_EQUAL(nb_cells, 5, "The number of cells should be 5 but is '%d'", nb_cells);

    sim_propagate('+', 0, BOARD_SIZE - 1, 'C', 4, 1);
    clean_board_visited(0, BOARD_SIZE - 1);
    nb_cells = sim_propagate('+', 0, BOARD_SIZE - 1, 'F', 4, 1);
    clean_board(0, BOARD_SIZE - 1);
    SUT_INT_EQUAL(nb_cells, 9, "The number of cells should be 9 but is '%d'", nb_cells);

    set_cell_color(1, 4, 'D');
    set_cell_color(2, 4, 'D');
    return 1;
}

SUT_TEST(alea_strategy)
{
    char letter = alea_strategy(get_player(1));

    SUT_ASSERT(letter != 'A', "The cell color should be B or D but is '%c'", letter);
    SUT_ASSERT(letter != 'C', "The cell color should be B or D but is '%c'", letter);
    SUT_ASSERT(letter != 'E', "The cell color should be B or D but is '%c'", letter);
    SUT_ASSERT(letter != 'F', "The cell color should be B or D but is '%c'", letter);
    SUT_ASSERT(letter != 'G', "The cell color should be B or D but is '%c'", letter);

    set_player_cell_owned(get_player(1), propagate('-', 4, 0, letter));
    clean_board(BOARD_SIZE - 1, 0);

    letter = alea_strategy(get_player(1));

    SUT_ASSERT(letter != 'F', "The cell color should be A B C D or E but is '%c'", letter);
    SUT_ASSERT(letter != 'G', "The cell color should be  A B C D or E but is '%c'", letter);

    set_player_cell_owned(get_player(1), 1);

    set_cell_color(3, 0, 'B');
    set_cell_color(4, 1, 'D');
    return 1;
}

SUT_TEST(glouton_strategy)
{
    char letter = glouton_strategy(get_player(0));
    SUT_CHAR_EQUAL(letter, 'D', "The cell color should be D but is '%c'", letter);
    propagate('+', 0, 4, letter);
    clean_board(BOARD_SIZE - 1, 0);

    letter = glouton_strategy(get_player(0));
    SUT_CHAR_EQUAL(letter, 'C', "The cell color should be C but is '%c'", letter);
    propagate('+', 0, 4, letter);
    clean_board(BOARD_SIZE - 1, 0);

    letter = glouton_strategy(get_player(0));
    SUT_CHAR_EQUAL(letter, 'F', "The cell color should be F but is '%c'", letter);
    propagate('+', 0, 4, letter);
    clean_board(BOARD_SIZE - 1, 0);

    letter = glouton_strategy(get_player(0));
    SUT_CHAR_EQUAL(letter, 'B', "The cell color should be B but is '%c'", letter);

    set_cell_color(1, 4, 'D');
    set_cell_color(2, 4, 'D');
    set_cell_color(0, 3, 'C');
    set_cell_color(3, 4, 'C');
    set_cell_color(0, 2, 'F');
    set_cell_color(1, 2, 'F');
    set_cell_color(1, 1, 'F');
    set_cell_color(1, 0, 'F');

    return 1;
}

SUT_TEST(is_landlocked)
{
    set_cell_color(2, 0, '-');
    set_cell_color(1, 1, '-');
    set_cell_color(2, 2, '-');
    set_cell_color(3, 1, '-');

    int res = is_landlocked(2, 1, '-');
    SUT_INT_EQUAL(res, 1, "The result should be 1 but is '%c'", res);

    res = is_landlocked(4, 3, '-');
    SUT_INT_EQUAL(res, 0, "The result should be 0 but is '%c'", res);

    set_cell_color(2, 0, 'C');
    set_cell_color(1, 1, 'F');
    set_cell_color(2, 2, 'B');
    set_cell_color(3, 1, 'E');

    return 1;
}

SUT_TEST(neighbours_counter)
{
    neighbours_counter(1);
    neighbours_counter(1);
    neighbours_counter(1);
    neighbours_counter(0);
    neighbours_counter(1);

    int res = neighbours_counter(1);
    SUT_INT_EQUAL(res, 2, "The result should be 2 but is '%c'", res);

    res = neighbours_counter(0);
    SUT_INT_EQUAL(res, 0, "The result should be 0 but is '%c'", res);

    return 1;
}

SUT_TEST(hegemonique_strategy)
{
    char letter = hegemonique_strategy(get_player(0));
    SUT_CHAR_EQUAL(letter, 'D', "The cell color should be D but is '%c'", letter);
    propagate('+', 0, 4, letter);
    clean_board(BOARD_SIZE - 1, 0);

    letter = hegemonique_strategy(get_player(0));
    SUT_CHAR_EQUAL(letter, 'C', "The cell color should be C but is '%c'", letter);
    propagate('+', 0, 4, letter);
    clean_board(BOARD_SIZE - 1, 0);

    letter = hegemonique_strategy(get_player(0));
    SUT_CHAR_EQUAL(letter, 'F', "The cell color should be F but is '%c'", letter);
    propagate('+', 0, 4, letter);
    clean_board(BOARD_SIZE - 1, 0);

    letter = hegemonique_strategy(get_player(0));
    SUT_CHAR_EQUAL(letter, 'E', "The cell color should be E but is '%c'", letter);

    set_cell_color(1, 4, 'D');
    set_cell_color(2, 4, 'D');
    set_cell_color(0, 3, 'C');
    set_cell_color(3, 4, 'C');
    set_cell_color(0, 2, 'F');
    set_cell_color(1, 2, 'F');
    set_cell_color(1, 1, 'F');
    set_cell_color(1, 0, 'F');

    return 1;
}
SUT_TEST(glouton_prevoyant_strategy)
{
    char letter = glouton_prevoyant_strategy(get_player(0));
    SUT_CHAR_EQUAL(letter, 'C', "The cell color should be C but is '%c'", letter);
    propagate('+', 0, 4, letter);
    clean_board(BOARD_SIZE - 1, 0);

    letter = glouton_prevoyant_strategy(get_player(0));
    SUT_CHAR_EQUAL(letter, 'F', "The cell color should be F but is '%c'", letter);
    propagate('+', 0, 4, letter);
    clean_board(BOARD_SIZE - 1, 0);

    letter = glouton_prevoyant_strategy(get_player(0));
    SUT_CHAR_EQUAL(letter, 'B', "The cell color should be B but is '%c'", letter);
    propagate('+', 0, 4, letter);
    clean_board(BOARD_SIZE - 1, 0);

    letter = glouton_prevoyant_strategy(get_player(0));
    SUT_CHAR_EQUAL(letter, 'D', "The cell color should be D but is '%c'", letter);

    set_cell_color(0, 3, 'C');
    set_cell_color(0, 2, 'F');
    set_cell_color(1, 2, 'F');
    set_cell_color(1, 1, 'F');
    set_cell_color(1, 0, 'F');
    set_cell_color(0, 1, 'B');
    set_cell_color(2, 2, 'B');

    return 1;
}

/** Tests for the tournament */
SUT_TEST(init_game_AI)
{
    delete_player(player_list[0]);
    delete_player(player_list[1]);
    delete_board();
    init_game_AI(1, 2);

    SUT_CHAR_EQUAL(get_player_symbol(get_player(0)), '+', "The player color should be '+' but is '%d'", get_player_symbol(get_player(0)));
    SUT_CHAR_EQUAL(get_player_symbol(get_player(1)), '-', "The player color should be '-' but is '%d'", get_player_symbol(get_player(1)));

    SUT_INT_EQUAL(get_player_ai_type(get_player(0)), 1, "The player ai type should be 1 but is '%d'", get_player_ai_type(get_player(0)));
    SUT_INT_EQUAL(get_player_ai_type(get_player(1)), 2, "The player ai type should be 2  but is '%d'", get_player_ai_type(get_player(1)));

    SUT_INT_EQUAL(get_player_init_x(get_player(0)), 0, "The player x position should be 4 but is '%d'", get_player_init_x(get_player(0)));
    SUT_INT_EQUAL(get_player_init_x(get_player(1)), 4, "The player x position should be 0  but is '%d'", get_player_init_x(get_player(1)));

    SUT_INT_EQUAL(get_player_init_y(get_player(0)), 4, "The player y position should be 0 but is '%d'", get_player_init_y(get_player(0)));
    SUT_INT_EQUAL(get_player_init_y(get_player(1)), 0, "The player y position should be 4 but is '%d'", get_player_init_y(get_player(1)));

    SUT_INT_EQUAL(get_player_cell_owned(get_player(0)), 1, "The player number of cells owned should be 1 but is '%d'", get_player_cell_owned(get_player(0)));
    SUT_INT_EQUAL(get_player_cell_owned(get_player(1)), 1, "The player number of cells owned  be 1 but is '%d'", get_player_cell_owned(get_player(1)));

    delete_player(player_list[0]);
    delete_player(player_list[1]);
    delete_board();
    return 1;
}
SUT_TEST_SUITE(board) = {
    //Tests for player struct
    SUT_TEST_SUITE_ADD(get_player_symbol),
    SUT_TEST_SUITE_ADD(get_player_ai_type),
    SUT_TEST_SUITE_ADD(get_player_init_x),
    SUT_TEST_SUITE_ADD(get_player_init_y),
    SUT_TEST_SUITE_ADD(get_player_cell_owned),
    SUT_TEST_SUITE_ADD(set_player_cell_owned),

    //Tests for cell struct
    SUT_TEST_SUITE_ADD(get_cell_color),
    SUT_TEST_SUITE_ADD(getset_cell_color),
    SUT_TEST_SUITE_ADD(get_cell_visited),
    SUT_TEST_SUITE_ADD(getset_cell_visited),
    SUT_TEST_SUITE_ADD(get_cell_turn_visited),
    SUT_TEST_SUITE_ADD(getset_cell_turn_visited),

    //Tests for the board
    SUT_TEST_SUITE_ADD(init_board),
    SUT_TEST_SUITE_ADD(clean_board),
    SUT_TEST_SUITE_ADD(clean_board_visited),
    SUT_TEST_SUITE_ADD(clean_board_turn_visited),
    SUT_TEST_SUITE_ADD(propagate),
    SUT_TEST_SUITE_ADD(update_board),
    SUT_TEST_SUITE_ADD(end_game),

    //Tests for the AI
    SUT_TEST_SUITE_ADD(sim_propagate),
    SUT_TEST_SUITE_ADD(alea_strategy),
    SUT_TEST_SUITE_ADD(glouton_strategy),
    SUT_TEST_SUITE_ADD(neighbours_counter),
    SUT_TEST_SUITE_ADD(is_landlocked),
    SUT_TEST_SUITE_ADD(hegemonique_strategy),
    SUT_TEST_SUITE_ADD(glouton_prevoyant_strategy),

    //Tests for the tournament
    SUT_TEST_SUITE_ADD(init_game_AI),

    SUT_TEST_SUITE_END};