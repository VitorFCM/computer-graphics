#include <stdlib.h>
#include <stdio.h>
#include "../globjects.h"
#include "primitives-creation.h"
#include "file-structs.h"
#include "file-manager.h"
#include "auxiliary.h"

int main(void){
	char shape;
	readline(&shape, 1);

	vertices **shapesVertices = (vertices**)malloc(10*sizeof(vertices*));
	objHeader **shapesHeaders = (objHeader**)malloc(10*sizeof(objHeader*));

	if(shapesVertices == NULL || shapesHeaders == NULL){
		printf("Problema no armazenamento das formas\n");
		return 0;
	}
	int i = 0;
	while(shape != '!'){
		printf("valor de i %i\n", i);
		vertices *v;
		objHeader *header = (objHeader*)malloc(sizeof(objHeader));

		if(shape == 't')
			v = createTriangle(header);
		else if(shape == 'r')
			v = createRectangle(header);
		else
			printf("Forma desconhecida\n");

		printf("Recebeu a forma\n");

		shapesVertices[i] = v;
		shapesHeaders[i++] = header;

		if(i%10 == 0){
			shapesVertices = (vertices**)realloc(shapesVertices, (10 + i)*sizeof(vertices*));
			shapesHeaders = (objHeader**)realloc(shapesHeaders, (10 + i)*sizeof(objHeader*));
		}

		readline(&shape, 1);

	}

	printf("n objetos: %i\n", i);
	writeFigure(shapesVertices, shapesHeaders, i);
	return 0;
}

