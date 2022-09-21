/* para linux, instalar os pacotes libglfw3-dev mesa-common-dev libglew-dev */
/* para compilar no linux: gcc main.c -lglfw -lGL -lGLEW -lm */

/* para windows, instalar bibliotecas compiladas do glfw3 e glew no ambiente mingw */
/* para compilar no windows: gcc main.c -lglfw3dll -lglew32 -lopengl32 */


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h> /* verifique no seu SO onde fica o glfw3.h */
#include "globjects.h"
#include "formas.h"

#define GLFW_INCLUDE_NONE



// variaveis globais
typedef struct{
	float x, y;
} coordenadas;


float t_x = 0.0f;
float t_y = 0.0f;

float theta = 0.0f;


// funcao para processar eventos de teclado
static void key_event(GLFWwindow* window, int key, int scancode, int action, int mods){
	printf("Pressionando tecla %d\n", key);

	if(key==262) t_x += 0.01; // tecla para direita
	if(key==263) t_x -= 0.01; // tecla para direita

	if(key==265) t_y += 0.01; // tecla para cima
	if(key==264) t_y -= 0.01; // tecla para baixo

	if(key == 81) theta += 1.0f;
	if(key == 69) theta -= 1.0f;
}


int main(void){

	// inicicializando o sistema de\ janelas
	glfwInit();

	// deixando a janela invisivel, por enquanto
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);


	// criando uma janela
	GLFWwindow* window = glfwCreateWindow(1500, 1500, "Minha Janela", NULL, NULL);


	// tornando a janela como principal
	glfwMakeContextCurrent(window);

	// inicializando Glew (para lidar com funcoes OpenGL)
	GLint GlewInitResult = glewInit();
	printf("GlewStatus: %s", glewGetErrorString(GlewInitResult));


	// GLSL para Vertex Shader
	char* vertex_code =
		"attribute vec2 position;\n"
		"uniform mat4 mat_transformation;\n"
		"void main()\n"
		"{\n"
		"    gl_Position = mat_transformation*vec4(position, 0.0, 1.0);\n"
		"}\n";

	// GLSL para Fragment Shader
	char* fragment_code =
		"uniform vec4 color;\n"
		"void main()\n"
		"{\n"
		"    gl_FragColor = color;\n"
		"}\n";

	// Requisitando slot para a GPU para nossos programas Vertex e Fragment Shaders
	GLuint program = glCreateProgram();
	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

	// Associando nosso código-fonte GLSL aos slots solicitados
	glShaderSource(vertex, 1, &vertex_code, NULL);
	glShaderSource(fragment, 1, &fragment_code, NULL);

	// Compilando o Vertex Shader e verificando erros
	glCompileShader(vertex);

	GLint isCompiled = 0;
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &isCompiled);
	if(isCompiled == GL_FALSE){

		//descobrindo o tamanho do log de erro
		int infoLength = 512;
		glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &infoLength);

		//recuperando o log de erro e imprimindo na tela
		char info[infoLength];
		glGetShaderInfoLog(vertex, infoLength, NULL, info);

		printf("Erro de compilacao no Vertex Shader.\n");
		printf("--> %s\n",&info);

	}



	// Compilando o Fragment Shader e verificando erros
	glCompileShader(fragment);

	isCompiled = 0;
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &isCompiled);
	if(isCompiled == GL_FALSE){

		//descobrindo o tamanho do log de erro
		int infoLength = 512;
		glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &infoLength);

		//recuperando o log de erro e imprimindo na tela
		char info[infoLength];
		glGetShaderInfoLog(fragment, infoLength, NULL, info);

		printf("Erro de compilacao no Fragment Shader.\n");
		printf("--> %s\n",&info);

	}

	// Associando os programas compilado ao programa principal
	glAttachShader(program, vertex);
	glAttachShader(program, fragment);

	// Linkagem do programa e definindo como default
	glLinkProgram(program);
	glUseProgram(program);




	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);




	// Associando variáveis do programa GLSL (Vertex Shaders) com nossos dados
	GLint loc = glGetAttribLocation(program, "position");
	glEnableVertexAttribArray(loc);

	coordinates estrela[6] = coordinates_estrela;
	glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, sizeof(estrela[0]), (void*) 0); // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml


	GLint loc_color = glGetUniformLocation(program, "color");

	// Associando nossa janela com eventos de teclado
	glfwSetKeyCallback(window, key_event); // teclado

	// Exibindo nossa janela
	glfwShowWindow(window);

	coordinates paredes[4] = paredes_casa;
	coordinates janela_esquerda[4] = janela_esq;
	coordinates janela_direita[4] = janela_dir;
	coordinates porta[4] = porta_casa;
	coordinates telhado[3] = telhado_casa;

	while (!glfwWindowShouldClose(window))
	{

		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(1.0, 1.0, 1.0, 1.0);

		loc = glGetUniformLocation(program, "mat_transformation");

		//estrela
		float mat_translation[16] = translation_matrix(t_x,t_y,0);
		glUniformMatrix4fv(loc, 1, GL_TRUE, mat_translation);
		glBufferData(GL_ARRAY_BUFFER, sizeof(estrela), estrela, GL_DYNAMIC_DRAW);
		glUniform4f(loc_color, 1.0, 1.0, 0.0, 1.0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawArrays(GL_TRIANGLES, 3, 3);

		//casa
		float mat_rotation[16] = rotation_z_matrix(theta);
		glUniformMatrix4fv(loc, 1, GL_TRUE, mat_rotation);
		glBufferData(GL_ARRAY_BUFFER, sizeof(paredes), paredes, GL_DYNAMIC_DRAW);
		glUniform4f(loc_color, 0.0, 0.0, 1.0, 1.0);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBufferData(GL_ARRAY_BUFFER, sizeof(janela_esquerda), janela_esquerda, GL_DYNAMIC_DRAW);
		glUniform4f(loc_color, 1.0, 0.0, 0.0, 1.0);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBufferData(GL_ARRAY_BUFFER, sizeof(janela_direita), janela_direita, GL_DYNAMIC_DRAW);
		glUniform4f(loc_color, 1.0, 0.0, 0.0, 1.0);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBufferData(GL_ARRAY_BUFFER, sizeof(porta), porta, GL_DYNAMIC_DRAW);
		glUniform4f(loc_color, 1.0, 0.0, 0.0, 1.0);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBufferData(GL_ARRAY_BUFFER, sizeof(telhado), telhado, GL_DYNAMIC_DRAW);
		glUniform4f(loc_color, 1.0, 0.0, 0.0, 1.0);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);

	}

	glfwDestroyWindow(window);

	glfwTerminate();
	exit(EXIT_SUCCESS);
}
