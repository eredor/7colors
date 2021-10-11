/* Header file of the coordinates module */

#ifndef COORDINATES_H
#define COORDINATES_H

/** Coordinates implementation */
typedef struct coordinates coordinates_t;

/** Create a coordinates element*/
coordinates_t* add_coordinates(int x, int y);

/** Getters and setters for coordinates*/
int get_coordinates_x(coordinates_t* coordinates);
int get_coordinates_y(coordinates_t* coordinates);
int get_coordinates_flag(coordinates_t* coordinates);
void set_coordinates_flag(coordinates_t* coordinates, int val);

#endif
