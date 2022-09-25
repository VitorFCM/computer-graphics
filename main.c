/* para linux, instalar os pacotes libglfw3-dev mesa-common-dev libglew-dev */
/* para compilar no linux: gcc main.c -lglfw -lGL -lGLEW -lm */

/* para windows, instalar bibliotecas compiladas do glfw3 e glew no ambiente mingw */
/* para compilar no windows: gcc main.c -lglfw3dll -lglew32 -lopengl32 */


#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "program.h"
#include "globjects.h"
#include "entity.h"
#include "objects.h"

#define GLFW_INCLUDE_NONE

void controller(Entity *e, int key, int action);

void controller(Entity *e, int key, int action) {

    float dt = 1.0f;
    float dtheta = 0.5f;

    switch (key) {

        case GLFW_KEY_UP:
            e->t_y += dt;
            break;
        case GLFW_KEY_DOWN:
            e->t_y -= dt;
            break;
        case GLFW_KEY_LEFT:
            e->t_x -= dt;
            break;
        case GLFW_KEY_RIGHT:
            e->t_x += dt;
            break;
        case GLFW_KEY_Q:
            e->theta_z += dtheta;
            break;
        case GLFW_KEY_E:
            e->theta_z -= dtheta;
            break;

        default:
            break;

    }
}

int main() {

    initializeProgram("Teste", 600, 600);

    glObject rect;
    initializeObject(&rect, vertices_rectangle(0.0,0.0,100,100), draw_rectangle);
    Entity entity;
    initializeEntity(&entity);
    entity.t_x = 300.0;
    entity.addGlObject(&entity, &rect);
    entity.setController(&entity, controller);

    addEntityToProgram(&entity);

    startProgram();
}

