#ifndef GLOBJECTS_H
#define GLOBJECTS_H

#include <GL/glew.h>

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

#define TRANSFORMATION_IN_PLACE       0
#define TRANSFORMATION_IN_REFERENCE   1

typedef struct coordinates {
    float x, y;
} coordinates;

typedef struct vertices {
    unsigned int number;
    coordinates *v;
} vertices;

typedef struct glObject glObject;

typedef struct glObject {

    GLint gltransformation;
    GLint glcolor;

    vertices *vertices;

    float t_x;
    float t_y;
    float t_z;

    GLfloat v0;
    GLfloat v1;
    GLfloat v2;
    GLfloat v3;

    int ref_scale; // 0 -> aplica escala com base na posição atual. 1-> aplica escala com base na referencia.
    float ref_scale_x;
    float ref_scale_y;
    float ref_scale_z;

    float s_x;
    float s_y;
    float s_z;

    int ref_rotation; // 0 -> aplica rotação com base na posição atual. 1-> aplica rotação com base na referencia.
    float ref_rotation_x;
    float ref_rotation_y;
    float ref_rotation_z;

    float theta_z;

    void (*destroy)(glObject *o);
    void (*loadBuffer)(glObject *o);
    void (*transform)(glObject *o);
    void (*color)(glObject *o);
    void (*render)(glObject *o);
    void (*draw)();

} glObject;


void initializeObject(glObject *o, vertices *v, void (*draw)(glObject *o));

/* ---------------------------------------- */
void veccpy(coordinates *dest, unsigned int size_dest, coordinates *origin, unsigned int size_origin);
coordinates* veccnt(coordinates *c1, unsigned int size_1, coordinates *c2, unsigned int size_2);

#endif