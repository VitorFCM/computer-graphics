#ifndef OBJECTS_H
#define OBJECTS_H

#include "globjects.h"

#define POINTS_CIRCLE   128

vertices* vertices_rectangle(float altura, float largura);
void draw_rectangle();

vertices* vertices_circle(float radius);
void draw_circle();

vertices* vertices_triangle(float x1, float y1, float x2, float y2, float x3, float y3);
void draw_triangle();
#endif
