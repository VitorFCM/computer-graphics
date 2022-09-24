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

    float dt = 0.01f;
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

    initializeProgram("Teste", 500, 500);

    glObject rect;
    initializeObject(&rect, vertices_rectangle(0.3,0.1), draw_rectangle);
    Entity entity;
    initializeEntity(&entity);
    entity.addGlObject(&entity, &rect);
    entity.setController(&entity, controller);

    addEntityToProgram(&entity);

    startProgram();
}


//int main(void){
//
//	glfwInit();
//	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
//	GLFWwindow* window = glfwCreateWindow(400, 400, "Minha Janela", NULL, NULL);
//	glfwMakeContextCurrent(window);
//	GLint GlewInitResult = glewInit();
//	printf("GlewStatus: %s", glewGetErrorString(GlewInitResult));
//
//	const GLchar *vertex_code =
//		"attribute vec2 position;\n"
//		"uniform mat4 mat_transformation;\n"
//		"void main()\n"
//		"{\n"
//		"    gl_Position = mat_transformation*vec4(position, 0.0, 1.0);\n"
//		"}\n";
//
//	const GLchar *fragment_code =
//		"uniform vec4 color;\n"
//		"void main()\n"
//		"{\n"
//		"    gl_FragColor = color;\n"
//		"}\n";
//
//	GLuint program = glCreateProgram();
//	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
//	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
//
//	glShaderSource(vertex, 1, &vertex_code, NULL);
//	glShaderSource(fragment, 1, &fragment_code, NULL);
//
//	glCompileShader(vertex);
//
//	GLint isCompiled = 0;
//	glGetShaderiv(vertex, GL_COMPILE_STATUS, &isCompiled);
//	if (isCompiled == GL_FALSE){
//
//		int infoLength = 512;
//		glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &infoLength);
//
//		char info[infoLength];
//		glGetShaderInfoLog(vertex, infoLength, NULL, info);
//
//		printf("Erro de compilacao no Vertex Shader.\n");
//		printf("--> %s\n", info);
//	}
//
//	glCompileShader(fragment);
//
//	isCompiled = 0;
//	glGetShaderiv(fragment, GL_COMPILE_STATUS, &isCompiled);
//	if (isCompiled == GL_FALSE){
//
//		//descobrindo o tamanho do log de erro
//		int infoLength = 512;
//		glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &infoLength);
//
//		//recuperando o log de erro e imprimindo na tela
//		char info[infoLength];
//		glGetShaderInfoLog(fragment, infoLength, NULL, info);
//
//		printf("Erro de compilacao no Fragment Shader.\n");
//		printf("--> %s\n", info);
//
//	}
//
//	glAttachShader(program, vertex);
//	glAttachShader(program, fragment);
//
//	glLinkProgram(program);
//	glUseProgram(program);
//
//	GLuint buffer;
//	glGenBuffers(1, &buffer);
//	glBindBuffer(GL_ARRAY_BUFFER, buffer);
//
//	GLint loc = glGetAttribLocation(program, "position");
//	glEnableVertexAttribArray(loc);
//	glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, sizeof(coordinates), (void*) 0);
//	GLint loc_color = glGetUniformLocation(program, "color");
//	glfwSetKeyCallback(window, key_event);
//	glfwShowWindow(window);
//
//	loc = glGetUniformLocation(program, "mat_transformation");
//
//    glObject quadr;
//    initializeObject(&quadr, vertices_rectangle(0.5f, 0.1f), loc, loc_color, draw_rectangle);
//    glObject circle;
//    initializeObject(&circle, vertices_circle(0.1f), loc, loc_color, draw_circle);
//
//    circle.v1 = 1.0f;
//    circle.t_y = 0.25;
//
//    glObject quadr2;
//    initializeObject(&quadr2, vertices_rectangle(0.5f, 0.1f), loc, loc_color, draw_rectangle);
//    glObject circle2;
//    initializeObject(&circle2, vertices_circle(0.1f), loc, loc_color, draw_circle);
//
//    circle2.v1 = 1.0f;
//    circle2.t_y = 0.25;
//
//    Entity entity;
//    initializeEntity(&entity);
//    entity.addGlObject(&entity, &quadr);
//    entity.addGlObject(&entity, &circle);
//
//    entity.theta_z = 45.0f;
//
//    Entity entity2;
//    initializeEntity(&entity2);
//    entity.addGlObject(&entity2, &quadr2);
//    entity.addGlObject(&entity2, &circle2);
//
//    entity2.theta_z = -45.0f;
//
//    initializeEntity(&e);
//    e.addEntity(&e, &entity, 0.8f, 0.8f);
//    e.addEntity(&e, &entity2, -0.8f, -0.8f);
//
////    const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
////    printf("%d | %d\n", mode->width, mode->height);
////    int h, w;
////    glfwGetWindowSize(window, &w, &h);
////    printf("%d | %d\n", h, w);
//
//	while (!glfwWindowShouldClose(window)) {
//
//		glfwPollEvents();
//		glClear(GL_COLOR_BUFFER_BIT);
//		glClearColor(1.0, 1.0, 1.0, 1.0);
//
////        entity.render(&entity);
////        entity2.render(&entity2);
//        e.render(&e);
//
//		glfwSwapBuffers(window);
//	}
//
//	glfwDestroyWindow(window);
//
//	glfwTerminate();
//	exit(EXIT_SUCCESS);
//}

