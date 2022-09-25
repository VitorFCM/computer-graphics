#include <stdlib.h>
#include <math.h>
#include "objects.h"
#include "globjects.h"

vertices* vertices_rectangle(float x, float y, float width, float height) {

    float x_v = x + width / 2.0f;
    float y_v = y + height / 2.0f;

    coordinates c[] = {
            {x_v,y_v},
            {x_v,-y_v},
            {-x_v,y_v},
            {-x_v,-y_v}
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
    float r= radius;
    float angle = 0.0f;
    float x_p, y_p;

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

    c[0].x = x1;
    c[0].y = y1;

    c[1].x = x2;
    c[1].y = y2;

    c[2].x = x3;
    c[2].y = y3;

    vertices *v = (vertices*) malloc(sizeof(vertices));
    v->number = 3;
    v->v = c;

    return v;
}

void draw_triangle() {
    glDrawArrays(GL_TRIANGLES, 0, 3);
}