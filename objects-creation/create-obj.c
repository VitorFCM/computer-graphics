#include <stdlib.h>
#include <stdio.h>
#include "../globjects.h"
#include "triangle-creation.h"
#include "file-structs.h"

int main(void){
	char shape;
	scanf("%c", &shape);
	while(shape != '!'){
		vertices *v;
		objHeader *header;
		switch(shape){
			case 't': printf("triangulo\n");
				  v = createTriangle(header);
				  break;
			case 'r': printf("retangulo\n");
				  break;
			case 'c': printf("circulo\n");
				  break;
			default:  printf("Forma desconhecida\n");
				  break;
		}
		printf("Object header:\n");
		printf("n coordenadas: %i", header->nCoordinates);
		scanf("%c", &shape);
	}
	return 0;
}

