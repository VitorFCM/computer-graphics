#ifndef PROGRAM_H
#define PROGRAM_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "entity.h"
#include "linkedlist.h"

/**
 * Define o tamanho da área lógica da aplicação. Este número define como o sistema de
 * coordenadas da aplicação é construido.
 */
#define SCREEN_SIZE 600

typedef struct Program {

    GLFWwindow *window;
    GLuint program_code;

    GLint glPosition;
    GLint glTransformation;
    GLint glColor;

    LinkedList entities;

} Program;

void initializeProgram(const char* title_window, int width_window, int height_window);
void startProgram();

GLint getGLPosition();
GLint getGLTransformation();
GLint getGLColor();

float convertValue(float value);

void addEntityToProgram(Entity *e);
#endif
