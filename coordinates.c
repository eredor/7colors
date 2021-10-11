/* Implentation of the coordinates module */

#include <stdio.h>
#include <stdlib.h> // For malloc
#include "coordinates.h"  /* Enforce that the header file matches the declarations */


/** Coordinates implementation */
struct coordinates {
    int x;
    int y;
    int flag;
};

/** Create a coordinates element*/
coordinates_t* add_coordinates(int x, int y){
    coordinates_t* res = malloc(sizeof(coordinates_t));
    res -> x = x;
    res -> y = y;
    res -> flag = 0;
    return res;
}

/** Getters and setters for coordinates*/
int get_coordinates_x(coordinates_t* coordinates){
    return coordinates -> x;
}
int get_coordinates_y(coordinates_t* coordinates){
    return coordinates -> y;
}
int get_coordinates_flag(coordinates_t* coordinates){
    return coordinates -> flag;
}
void set_coordinates_flag(coordinates_t* coordinates, int val){
    coordinates -> flag = val;
}
