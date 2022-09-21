#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "globjects.h"

void initializeObject(glObject *o, unsigned int number_verticex) {

    o->number_vertices = number_verticex;
    o->vertices = malloc(sizeof(coordinates) * number_verticex);
    
    o->t_x = o->t_y = o->t_z = 0.0f;
    o->s_x = o->s_y = o->s_z = 0.0f;

    o->theta = 0.0f;
}

void destroyObject(glObject *o) {
    free(o->vertices);
}

void veccpy(coordinates *dest, unsigned int size_dest, coordinates *origin, unsigned int size_origin) {
    
    if (size_dest != size_origin) return;
    for (int i = 0; i < size_dest; i++) dest[i] = origin[i];
}

coordinates* veccnt(coordinates *c1, unsigned int size_1, coordinates *c2, unsigned int size_2) {

    coordinates *retval = malloc(sizeof(coordinates) * (size_1 + size_2));
    
    int i;
    for (i = 0; i < size_1; i++) retval[i] = c1[i];
    for (int j = 0; j < size_2; j++) retval[i + j] = c2[j];
    
    return retval;
}