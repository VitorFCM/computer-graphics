#ifndef PRIMITIVES_CREATION_H
#define PRIMITIVES_CREATION_H

#include "file-structs.h"
#include "../globjects.h"

void colorsInput(objHeader *header);
vertices* createCircle(objHeader *header);
vertices* createRectangle(objHeader *header);
vertices* createTriangle(objHeader *header);

#endif
