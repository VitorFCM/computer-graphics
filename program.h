#ifndef PROGRAM_H
#define PROGRAM_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "entity.h"
#include "linkedlist.h"

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

void addEntityToProgram(Entity *e);
#endif
