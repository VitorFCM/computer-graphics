/* para linux, instalar os pacotes libglfw3-dev mesa-common-dev libglew-dev */
/* para compilar no linux: gcc main.c -lglfw -lGL -lGLEW -lm */

/* para windows, instalar bibliotecas compiladas do glfw3 e glew no ambiente mingw */
/* para compilar no windows: gcc main.c -lglfw3dll -lglew32 -lopengl32 */


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "globjects.h"
#include "entity.h"
#include "objects.h"
#include "formas.h"

#define GLFW_INCLUDE_NONE

float t_x = 0.0f;
float t_y = 0.0f;

float theta = 0.0f;

float s = 1.0f;


// funcao para processar eventos de teclado
static void key_event(GLFWwindow* window, int key, int scancode, int action, int mods){
	printf("Pressionando tecla %d\n", key);

	if(key==262) t_x += 0.01; // tecla para direita
	if(key==263) t_x -= 0.01; // tecla para direita

	if(key==265) t_y += 0.01; // tecla para cima
	if(key==264) t_y -= 0.01; // tecla para baixo

	if(key == 81) theta += 1.0f; // Q
	if(key == 69) theta -= 1.0f; // E

	if (key == 73) s += 0.01f; // I
	if (key == 79) s -= 0.01f; // O
}


int main(void){

	glfwInit();
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
	GLFWwindow* window = glfwCreateWindow(800, 800, "Minha Janela", NULL, NULL);
	glfwMakeContextCurrent(window);
	GLint GlewInitResult = glewInit();
	printf("GlewStatus: %s", glewGetErrorString(GlewInitResult));

	const GLchar *vertex_code =
		"attribute vec2 position;\n"
		"uniform mat4 mat_transformation;\n"
		"void main()\n"
		"{\n"
		"    gl_Position = mat_transformation*vec4(position, 0.0, 1.0);\n"
		"}\n";

	const GLchar *fragment_code =
		"uniform vec4 color;\n"
		"void main()\n"
		"{\n"
		"    gl_FragColor = color;\n"
		"}\n";

	GLuint program = glCreateProgram();
	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertex, 1, &vertex_code, NULL);
	glShaderSource(fragment, 1, &fragment_code, NULL);

	glCompileShader(vertex);

	GLint isCompiled = 0;
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE){

		int infoLength = 512;
		glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &infoLength);

		char info[infoLength];
		glGetShaderInfoLog(vertex, infoLength, NULL, info);

		printf("Erro de compilacao no Vertex Shader.\n");
		printf("--> %s\n", info);

	}

	glCompileShader(fragment);

	isCompiled = 0;
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE){

		//descobrindo o tamanho do log de erro
		int infoLength = 512;
		glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &infoLength);

		//recuperando o log de erro e imprimindo na tela
		char info[infoLength];
		glGetShaderInfoLog(fragment, infoLength, NULL, info);

		printf("Erro de compilacao no Fragment Shader.\n");
		printf("--> %s\n", info);

	}

	glAttachShader(program, vertex);
	glAttachShader(program, fragment);

	glLinkProgram(program);
	glUseProgram(program);

	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	GLint loc = glGetAttribLocation(program, "position");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, sizeof(coordinates), (void*) 0);
	GLint loc_color = glGetUniformLocation(program, "color");
	glfwSetKeyCallback(window, key_event);
	glfwShowWindow(window);

	loc = glGetUniformLocation(program, "mat_transformation");

    glObject quadr;
    initializeObject(&quadr, vertices_rectangle(0.5f, 0.1f), loc, loc_color, draw_rectangle);
    glObject circle;
    initializeObject(&circle, vertices_circle(0.1f), loc, loc_color, draw_circle);

    circle.v1 = 1.0f;
    circle.t_y = 0.25;


    Entity entity;
    initializeEntity(&entity);
    entity.addGlObject(&entity, &quadr);
    entity.addGlObject(&entity, &circle);

//    entity.theta_z = 45.0f;
//    entity.t_x = 0.5f;

//    entity.t_y = -0.5f;
//    entity.theta_z = -45.0f;

	while (!glfwWindowShouldClose(window)) {

		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(1.0, 1.0, 1.0, 1.0);

        entity.render(&entity);
		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);

	glfwTerminate();
	exit(EXIT_SUCCESS);
}

