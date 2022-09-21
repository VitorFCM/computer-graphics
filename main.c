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
#include "formas.h"

#define GLFW_INCLUDE_NONE

#define translation_matrix(t_x,t_y,t_z) {   \
	1.0f, 0.0f, 0.0f, t_x,          \
	0.0f, 1.0f, 0.0f, t_y,          \
	0.0f, 0.0f, 1.0f, t_z,          \
	0.0f, 0.0f, 0.0f, 1.0f          \
}                                   \

#define rotation_z_matrix(theta) {                                                  \
	cos(((theta)*M_PI/180.0)), -sin(((theta)*M_PI/180.0)), 0.0f, 0.0f,      \
	sin(((theta)*M_PI/180.0)),  cos(((theta)*M_PI/180.0)), 0.0f, 0.0f,      \
	0.0f, 0.0f, 1.0f, 0.0f,                                                 \
	0.0f, 0.0f, 0.0f, 1.0f                                                  \
}

#define scale_matrix(s_x,s_y,s_z) {     \
	s_x, 0.0f, 0.0f, 0.0f,      \
	0.0f, s_y, 0.0f, 0.0f,      \
	0.0f, 0.0f, s_z, 0.0f,      \
	0.0f, 0.0f, 0.0f, 1.0f      \
}                               \
\

void circ_vertices(coordinates *v, float x, float y, float r, unsigned q) {

	float pi = 3.14f;
	float counter = 0.0f;
	float radius = r;
	float angle = 0.0f;
	float dx = 0.0f, dy = 0.0f;
	for (int i = 0; i < q; i++){
		angle += (2.0f * pi) / q;
		dx = x + cos(angle) * radius;
		dy = y + sin(angle) * radius;
		v[i].x = dx;
		v[i].y = dy;
	}
}


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

	glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, sizeof(coordinates), (void*) 0); // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml


	GLint loc_color = glGetUniformLocation(program, "color");

	// Associando nossa janela com eventos de teclado
	glfwSetKeyCallback(window, key_event); // teclado

	// Exibindo nossa janela
	glfwShowWindow(window);

	//estrela
	coordinates estrela[] = coordinates_estrela;

	//casa
	coordinates paredes[] = paredes_casa;
	coordinates janela_esquerda[] = janela_esq;
	coordinates janela_direita[] = janela_dir;
	coordinates porta[] = porta_casa;
	coordinates telhado[] = telhado_casa;

	//foguete
	coordinates corpo_f[] = corpo_foguete;
	coordinates triangulos_f[] = triangulos_foguete;
	coordinates janela_f[128];
	circ_vertices(janela_f, 0.0f, 0.125f, 0.05f, 128);

	//carro
	coordinates lataria_c[] = lataria_carro(0, 0.0);
	coordinates roda1[128];
	circ_vertices(roda1, -0.85f, -0.97f, 0.05f, 128);
	coordinates roda2[128];
	circ_vertices(roda2, -0.45f, -0.97f, 0.05f, 128);

	//boneco
	coordinates cabeca[128];
	circ_vertices(cabeca, 0.7f, -0.6f, 0.1f, 128);
	coordinates corpo[128];
	circ_vertices(corpo, 0.7f, -0.8f, 0.2f, 128);
	coordinates olho1[128];
	circ_vertices(olho1, 0.625f, -0.6f, 0.05f, 128);
	coordinates olho2[128];
	circ_vertices(olho2, 0.675f, -0.6f, 0.05f, 128);
	coordinates miolho1[128];
	circ_vertices(miolho1, 0.625f, -0.6f, 0.008f, 128);
	coordinates miolho2[128];
	circ_vertices(miolho2, 0.675f, -0.6f, 0.008f, 128);

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

		float mat_rotation2[16] = rotation_z_matrix(0.0f);
		glUniformMatrix4fv(loc, 1, GL_TRUE, mat_rotation2);

		//foguete
		glBufferData(GL_ARRAY_BUFFER, sizeof(corpo_f), corpo_f, GL_DYNAMIC_DRAW);
		glUniform4f(loc_color, 0.0, 0.0, 0.0, 1.0);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		glBufferData(GL_ARRAY_BUFFER, sizeof(janela_f), janela_f, GL_DYNAMIC_DRAW);
		glUniform4f(loc_color, 0.0, 0.0, 1.0, 1.0);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 128);

		glBufferData(GL_ARRAY_BUFFER, sizeof(triangulos_f), triangulos_f, GL_DYNAMIC_DRAW);
		glUniform4f(loc_color, 0.0, 0.0, 1.0, 1.0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawArrays(GL_TRIANGLES, 3, 3);
		glDrawArrays(GL_TRIANGLES, 6, 3);


		//carro
		glBufferData(GL_ARRAY_BUFFER, sizeof(lataria_c), lataria_c, GL_DYNAMIC_DRAW);
		glUniform4f(loc_color, 1.0, 0.0, 0.0, 1.0);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		glBufferData(GL_ARRAY_BUFFER, sizeof(roda1), roda1, GL_DYNAMIC_DRAW);
		glUniform4f(loc_color, 0.0, 0.0, 0.0, 1.0);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 128);

		glBufferData(GL_ARRAY_BUFFER, sizeof(roda2), roda2, GL_DYNAMIC_DRAW);
		glUniform4f(loc_color, 0.0, 0.0, 0.0, 1.0);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 128);


		//boneco
		glBufferData(GL_ARRAY_BUFFER, sizeof(cabeca), cabeca, GL_DYNAMIC_DRAW);
		glUniform4f(loc_color, 1.0, 0.0, 0.0, 1.0);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 128);

		glBufferData(GL_ARRAY_BUFFER, sizeof(corpo), corpo, GL_DYNAMIC_DRAW);
		glUniform4f(loc_color, 1.0, 0.0, 0.0, 1.0);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 128);

		glBufferData(GL_ARRAY_BUFFER, sizeof(olho1), olho1, GL_DYNAMIC_DRAW);
		glUniform4f(loc_color, 1.0, 1.0, 1.0, 1.0);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 128);

		glBufferData(GL_ARRAY_BUFFER, sizeof(olho2), olho2, GL_DYNAMIC_DRAW);
		glUniform4f(loc_color, 1.0, 1.0, 1.0, 1.0);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 128);

		glBufferData(GL_ARRAY_BUFFER, sizeof(miolho1), miolho1, GL_DYNAMIC_DRAW);
		glUniform4f(loc_color, 0.0, 0.0, 0.0, 1.0);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 128);

		glBufferData(GL_ARRAY_BUFFER, sizeof(miolho2), miolho2, GL_DYNAMIC_DRAW);
		glUniform4f(loc_color, 0.0, 0.0, 0.0, 1.0);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 128);
		glfwSwapBuffers(window);

	}

	glfwDestroyWindow(window);

	glfwTerminate();
	exit(EXIT_SUCCESS);
}
