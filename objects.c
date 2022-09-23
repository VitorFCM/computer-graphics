#include <stdlib.h>
#include "objects.h"
#include "globjects.h"

vertices* vertices_retangulo(float altura, float largura) {

    float x = largura / 2.0f;
    float y = altura / 2.0f;

    coordinates c[] = {
            {x,y},
            {x,-y},
            {-x,y},
            {-x,-y}
    };

    unsigned int n = sizeof(c) / sizeof(c[0]);
    coordinates *coord = (coordinates*) malloc(sizeof(coordinates) * n);
    veccpy(coord, n, c, n);

    vertices *v = (vertices*) malloc(sizeof(vertices));
    v->number = n;
    v->v = coord;

    return v;
}

void desenhar_retangulo() {
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}