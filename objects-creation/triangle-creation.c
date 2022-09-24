#include <stdio.h>
#include <GL/glew.h>
#include "triangle-creation.h"
#include "../globjects.h"
#include "../objects.h"
#include "file-structs.h"

vertices* createTriangle(objHeader *header){

	coordinates c[3];
	for(int i = 0; i < 3; i++){
		printf("Coordenada do %i ponto\n", i + 1);
		printf("Valor de x: ");
		scanf("%f", &(c[i].x));
		printf("Valor de y: ");
		scanf("%f", &(c[i].y));
	}
	vertices *v = vertices_triangle(c[0].x, c[0].y, c[1].x, c[1].y, c[2].x, c[2].y);

	char letter[3] = {'R', 'G', 'B'};
	float rgb[3];
	for(int i = 0; i < 3; i++){

		printf("Valor de %c: ", letter[i]);
		float value;
		scanf("%f", &value);

		while(value < 0.0 || value > 1.0){
			printf("O valor e cor deve ser um valor entre 0.0 e 1.0.\n");
			printf("Por favor, repita o valor de %c: ", letter[i]);
			scanf("%f", &value);
		}

		rgb[i] = value;

	}

	header->mode = GL_TRIANGLES;

	header->v0 = rgb[0];
	header->v1 = rgb[1];
	header->v2 = rgb[2];
	header->v3 = 1.0f;

	header->nCoordinates = 3;

	return v;
}



