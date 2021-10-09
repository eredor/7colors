/* Implentation of the chaiend_lists module */

#include <stdio.h>
#include <stdlib.h> // For malloc
#include "chained_lists.h"  /* Enforce that the header file matches the declarations */


/** Coordinates implementation */
struct coordinates {
    int x;
    int y;
};

/** Create a coordinates element*/
coordinates_t* add_coordinates(int x, int y){
    coordinates_t* res = malloc(sizeof(coordinates_t));
    res -> x = x;
    res -> y = y;
    return res;
}

/** Getters and setters for coordinates*/
int get_coordinates_x(coordinates_t* coordinates){
    return coordinates -> x;
}
int get_coordinates_y(coordinates_t* coordinates){
    return coordinates -> y;
}



/** Chained lists implementation */
typedef struct element element_t;
struct element {
    coordinates_t* coord;
    element_t* next;
};

typedef struct chained_list list_t;
struct chained_list {
    element_t* first;
};

/** Create a chained list / an element */
list_t* create_list(coordinates_t* coord) {
    list_t* list = malloc(sizeof(list_t*));
    element_t* elt = malloc(sizeof(element_t*));

    elt->next = NULL;
    elt->coord = coord;

    list->first = elt;

    return list;
}

element_t* create_element(coordinates_t* coord) {
    element_t* elt = malloc(sizeof(element_t*));

    elt->next = NULL;
    elt->coord = coord;

    return elt;
}

/** Getters and setters for chained lists */
element_t* get_next_elt(element_t* elt) {
    return elt -> next;
}
void set_next_elt(element_t* elt, element_t* next) {
    elt -> next = next;
}
coordinates_t* get_value(element_t* elt) {
    return elt -> coord;
}
void set_value(element_t* elt, coordinates_t* value) {
    elt -> coord = value;
}

element_t* get_first_elt(list_t* list) {
    return list -> first;
}
void set_first_elt(list_t* list, element_t* elt) {
    list -> first = elt;
}

/** Functions related to lists */
void ajoute_elt(list_t* list, element_t* elt) {
    element_t* first = get_first_elt(list);
    set_next_elt(elt, first);
    set_first_elt(list, elt);
}

element_t* del_first_elt(list_t* list) {
    element_t* elt = get_first_elt(list);
    if (elt != NULL) {
        element_t* next = get_next_elt(elt);
        set_first_elt(list, next);

        return elt;

    } else {
        exit(EXIT_FAILURE);
    }
}
