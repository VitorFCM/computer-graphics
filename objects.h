#ifndef OBJECTS_H
#define OBJECTS_H

#include "globjects.h"

#define POINTS_CIRCLE   128

vertices* vertices_rectangle(float x, float y, float width, float height);
void draw_rectangle();

vertices* vertices_circle(float radius, float x, float y);
void draw_circle();

vertices* vertices_triangle(float x1, float y1, float x2, float y2, float x3, float y3);
void draw_triangle();

glObject* basic_rectangle(float x, float y, float width, float height);
glObject* basic_circle(float radius, float x, float y);
glObject* basic_triangle(float x1, float y1, float x2, float y2, float x3, float y3);

#endif
