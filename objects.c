#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "program.h"
#include "objects.h"
#include "globjects.h"

vertices* vertices_rectangle(float x, float y, float width, float height) {

    x = convertValue(x);
    y = convertValue(y);

    width = convertValue(width);
    height = convertValue(height);

    float x_v = width / 2.0f;
    float y_v = height / 2.0f;

    coordinates c[] = {
            {x_v + x,y_v + y},
            {x_v + x,-y_v + y},
            {-x_v + x,y_v + y},
            {-x_v + x,-y_v + y}
    };

    unsigned int n = sizeof(c) / sizeof(c[0]);
    coordinates *coord = (coordinates*) malloc(sizeof(coordinates) * n);
    veccpy(coord, n, c, n);

    vertices *v = (vertices*) malloc(sizeof(vertices));
    v->number = n;
    v->v = coord;

    return v;
}

void draw_rectangle() {
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

vertices* vertices_circle(float radius, float x, float y) {

    coordinates *c = (coordinates*) malloc(sizeof(coordinates) * POINTS_CIRCLE);

    float pi = 3.14f;
    float incr = (2.0f * pi) / POINTS_CIRCLE;
    float r = convertValue(radius);
    float angle = 0.0f;
    float x_p, y_p;

    x = convertValue(x);
    y = convertValue(y);

    for (int i = 0; i < POINTS_CIRCLE; i++){
        angle += incr;
        x_p = x + cos(angle) * r;
        y_p = y + sin(angle) * r;
        c[i].x = x_p;
        c[i].y = y_p;
    }

    vertices *v = (vertices*) malloc(sizeof(vertices));
    v->number = POINTS_CIRCLE;
    v->v = c;

    return v;
}

void draw_circle() {
    glDrawArrays(GL_TRIANGLE_FAN, 0, POINTS_CIRCLE);
}

vertices* vertices_triangle(float x1, float y1, float x2, float y2, float x3, float y3) {

    coordinates *c = (coordinates*) malloc(sizeof(coordinates) * 3);

    c[0].x = convertValue(x1);
    c[0].y = convertValue(y1);

    c[1].x = convertValue(x2);
    c[1].y = convertValue(y2);

    c[2].x = convertValue(x3);
    c[2].y = convertValue(y3);

    vertices *v = (vertices*) malloc(sizeof(vertices));
    v->number = 3;
    v->v = c;

    return v;
}

void draw_triangle() {
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

glObject* basic_rectangle(float x, float y, float width, float height) {

    glObject *o = (glObject*) malloc(sizeof(glObject));
    initializeObject(o, vertices_rectangle(0, 0, width, height), draw_rectangle);
    o->t_x = x;
    o->t_y = y;

    return o;
}

glObject* basic_circle(float radius, float x, float y) {

    glObject *o = (glObject*) malloc(sizeof(glObject));
    initializeObject(o, vertices_circle(radius, 0, 0), draw_circle);
    o->t_x = x;
    o->t_y = y;

    return o;
}

glObject* basic_triangle(float x1, float y1, float x2, float y2, float x3, float y3) {

    glObject *o = (glObject*) malloc(sizeof(glObject));

    float x_g = (x1 + x2 + x3) / 3.0f;
    float y_g = (y1 + y2 + y3) / 3.0f;

    x1 -= x_g;
    x2 -= x_g;
    x3 -= x_g;

    y1 -= y_g;
    y2 -= y_g;
    y3 -= y_g;

    initializeObject(o, vertices_triangle(x1,y1,x2,y2,x3,y3), draw_triangle);

    return o;
}