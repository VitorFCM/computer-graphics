#ifndef FILESTRUCTS_H
#define FILESTRUCTS_H

//The objHeader struct will be used to inform
//the file reader function about how many coordinates
//will be found for that specifc shape.
//Besides that, objHeader will store witch
//mode of shape will be used and it's color values.
//The final file will have one objHeader for each
//primitive.

typedef struct objHeader{
	GLenum mode;

	GLfloat v0;
	GLfloat v1;
	GLfloat v2;
	GLfloat v3;

	unsigned int nCoordinates;
} objHeader;

#endif
