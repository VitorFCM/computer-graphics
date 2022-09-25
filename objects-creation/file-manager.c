#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../globjects.h"
#include "../entity.h"
#include "../objects.h"
#include "file-structs.h"
#include "auxiliary.h"

void writeHeader(FILE *fp, objHeader *header){

	fwrite(&header->mode, sizeof(GLenum), 1, fp);

	fwrite(&header->v0, sizeof(GLfloat), 1, fp);
	fwrite(&header->v1, sizeof(GLfloat), 1, fp);
	fwrite(&header->v2, sizeof(GLfloat), 1, fp);
	fwrite(&header->v3, sizeof(GLfloat), 1, fp);

	fwrite(&header->nCoordinates, sizeof(unsigned int), 1, fp);
}

void writeCoordinate(FILE *fp, coordinates *coordinate){
	fwrite(&coordinate->x, sizeof(float), 1, fp);
	fwrite(&coordinate->y, sizeof(float), 1, fp);
}

void writeFigure(vertices** verticesList, objHeader **headers, int nObjects){
	printf("Escreva o nome do objeto: ");
	char fileName[15];
	readline(fileName, 15);

	char path[27] = "../objects/\0";

	strcat(path, fileName);

	FILE *fp;
	fp = fopen(path, "wb");
	fwrite(&nObjects, sizeof(int), 1, fp);
	for(int i = 0; i < nObjects; i++){
		objHeader *header_i = headers[i];
		writeHeader(fp, header_i);


		vertices *v_i = verticesList[i];
		for(int j = 0; j < v_i->number; j++){
			writeCoordinate(fp, &(v_i->v[j]));
		}
	}
	fclose(fp);
}

void readHeader(FILE *fp, objHeader *h){
	fread(&h->mode, sizeof(GLenum), 1, fp);

	fread(&h->v0, sizeof(GLfloat), 1, fp);
	fread(&h->v1, sizeof(GLfloat), 1, fp);
	fread(&h->v2, sizeof(GLfloat), 1, fp);
	fread(&h->v3, sizeof(GLfloat), 1, fp);

	fread(&h->nCoordinates, sizeof(unsigned int), 1, fp);
}

void readCoordinate(FILE *fp, coordinates *c){

	fread(&c->x, sizeof(float), 1, fp);
	fread(&c->y, sizeof(float), 1, fp);
}

//A single file stores information about glObjects that
//will be used to create an entity. The readFile function
//will return all globjects from a single file.
Entity readFile(char *fileName){

	char path[27] = "objects/\0";

	strcat(path, fileName);

	FILE *fp;
	fp = fopen(path, "rb");
	if(fp == NULL){
		printf("Problema na leitura do arquivo\n");
		exit(1);
	}


	int nObjects = 0;
	fread(&nObjects, sizeof(int), 1, fp);

	Entity entity;
	initializeEntity(&entity);

	for(int i = 0; i < nObjects; i++){
		objHeader h;
		readHeader(fp, &h);

		vertices *v_i = (vertices*)malloc(sizeof(vertices));
		v_i->number = h.nCoordinates;
		v_i->v = (coordinates*)malloc(sizeof(coordinates) * h.nCoordinates);
		for(int j = 0; j < h.nCoordinates; j++){
			coordinates c;
			readCoordinate(fp, &c);
			v_i->v[j] = c;
		}

		glObject *o = (glObject*)malloc(sizeof(glObject));
		if(h.mode == GL_TRIANGLES){
			initializeObject(o, v_i, draw_triangle);
		}else if(h.mode == GL_TRIANGLE_STRIP){
			initializeObject(o, v_i, draw_rectangle);
		}

		o->v0 = h.v0;
		o->v1 = h.v1;
		o->v2 = h.v2;
		o->v3 = h.v3;
		entity.addGlObject(&entity, o);
	}
	fclose(fp);
	return entity;
}
