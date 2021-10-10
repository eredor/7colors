/* Header file of the chained_lists module */

#ifndef CHAINEDLISTS_H
#define CHAINEDLISTS_H

/** Coordinates implementation */
typedef struct coordinates coordinates_t;

/** Create a coordinates element*/
coordinates_t* add_coordinates(int x, int y);

/** Getters and setters for coordinates*/
int get_coordinates_x(coordinates_t* coordinates);
int get_coordinates_y(coordinates_t* coordinates);
int get_coordinates_flag(coordinates_t* coordinates);
void set_coordinates_flag(coordinates_t* coordinates, int val);

// Note : we define here the coordinates type because lists use it.



/** Chained lists implementation */
typedef struct element element_t;

typedef struct chained_list list_t;

/** Create a chained list / an element */
list_t* create_list(coordinates_t* coord);

element_t* create_element(coordinates_t* coord);

/** Getters and setters for chained lists */

// For elements
element_t* get_next_elt(element_t* elt);

void set_next_elt(element_t* elt, element_t* next);

coordinates_t* get_value(element_t* elt);

void set_value(element_t* elt, coordinates_t* value);

// For lists
element_t* get_first_elt(list_t* list);

void set_first_elt(list_t* list, element_t* elt);


/** Functions related to lists */
void ajoute_elt(list_t* list, element_t* elt);

element_t* del_first_elt(list_t* list);


#endif
