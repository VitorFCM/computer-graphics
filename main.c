/*
 * Trabalho de Computação Gráfica
 *
 * Integrantes do Grupo:
 * Gabriel de Avelar Las Casas Rebelo - nUsp: 11800462
 * Lucas Carvalho Freiberger Stapf - nUsp: 11800559
 * Vitor Favrin Carrera Miguel - nUsp: 11800646
 */

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

    float dt = 5.0f;
    float dtheta = 0.5f;
    float ds = 0.05f;

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

        case GLFW_KEY_I:
            e->s_x += ds;
            e->s_y += ds;
            break;

        case GLFW_KEY_O:
            e->s_x -= ds;
            e->s_y -= ds;
            break;

        default:
            break;

    }
}

int main() {

    initializeProgram("Teste", 600, 600);

    Entity e_fundo;
    initializeEntity(&e_fundo);
    e_fundo.addGlObject(&e_fundo, basic_rectangle(0, -450, 1200, 300));
    addEntityToProgram(&e_fundo);

    Entity e_star;
    initializeEntity(&e_star);
    glObject *trian_1 = basic_triangle(0.0f, 173.2f, 100.0f, 0.0f,  -100.0f, 0.0f);
    trian_1->v1 = 1;
    trian_1->v2 = 1;
    e_star.addGlObject(&e_star, trian_1);
    glObject *trian_2 = basic_triangle(0.0f, 173.2f, 100.0f, 0.0f, -100.0f, 0.0f);
    trian_2->v1 = 1;
    trian_2->v2 = 1;
    trian_2->theta_z = 60.0f;
    e_star.addGlObject(&e_star, trian_2);
    e_star.t_y = -450;
    e_fundo.addEntity(&e_fundo, &e_star, 0.0f, 0.0f);

    Entity e_star_mov;
    initializeEntity(&e_star_mov);
    glObject *trian_3 = basic_triangle(0.0f, 173.2f, 100.0f, 0.0f,  -100.0f, 0.0f);
    trian_3->v1 = 1;
    e_star_mov.addGlObject(&e_star_mov, trian_3);
    glObject *trian_4 = basic_triangle(0.0f, 173.2f, 100.0f, 0.0f, -100.0f, 0.0f);
    trian_4->v1 = 1;
    trian_4->theta_z = 60.0f;
    e_star_mov.addGlObject(&e_star_mov, trian_4);
    e_star_mov.setController(&e_star_mov, controller);

    e_star_mov.s_x = e_star_mov.s_y = 2.0f;
    e_star_mov.theta_z = 45.0f;

    addEntityToProgram(&e_star_mov);

    startProgram();
}

