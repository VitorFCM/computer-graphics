#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "../globjects.h"
#include "../entity.h"
#include "file-structs.h"

void writeHeader(FILE *fp, objHeader *header);
void writeCoordinate(FILE *fp, coordinates *coordinate);
void writeFigure(vertices** v, objHeader **headers, int nObjects);
void readHeader(FILE *fp, objHeader *h);
void readCoordinate(FILE *fp, coordinates *c);
Entity readFile(char *fileName);



#endif
