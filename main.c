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
#include "objects-creation/file-manager.h"

#define GLFW_INCLUDE_NONE

int index_l = 0;
int nEntity = 2;
Entity **entityList;

void controller(Entity *e, int key, int action);
void changeControl();

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
			e->theta_z += dt;
			break;
		case GLFW_KEY_E:
			e->theta_z -= dt;
			break;
		case GLFW_KEY_A:
			e->s_x += dt;
			e->s_y += dt;
			break;
		case GLFW_KEY_D:
			e->s_x -= dt;
			e->s_y -= dt;
			break;
		case GLFW_KEY_T:
			printf("Vai fazer a troca\n");
			changeControl();
			break;

		default:
			break;

	}
}

void changeControl(){
	//printf("Entrou com %i\n", index_l);
	Entity *e = entityList[index_l];
	e->setController(e, NULL);

	//index_l++;
	//if(index_l == nEntity)index_l = 0;
	index_l = 1;//fiz isso so pra ver se funcionava
		   //printf("Saiu com %i\n\n", index_l);
		e = entityList[index_l];

	e->setController(e, controller);
}

int main() {

	initializeProgram("Teste", 800, 800);

	entityList = (Entity**)malloc(nEntity*sizeof(Entity*));
	for(int i = 0; i < nEntity; i++){
		entityList[i] = (Entity*)malloc(sizeof(Entity));
	}

	Entity e = readFile("mesa\0");
	e.setController(&e, controller);
	entityList[0] = &e;
	addEntityToProgram(&e);

	Entity e2 = readFile("quadro\0");
	//e2.setController(&e2, controller);
	entityList[1] = &e2;
	addEntityToProgram(&e2);

	startProgram();
}

