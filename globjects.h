#ifndef GLOBJECTS_H
#define GLOBJECTS_H

#include <GL/glew.h>

/**
 * Matriz de translação: translada o objeto da origem até o ponto (t_x, t_y, t_z).
 */
#define translation_matrix(t_x,t_y,t_z) {   \
            1.0f, 0.0f, 0.0f, t_x,          \
            0.0f, 1.0f, 0.0f, t_y,          \
            0.0f, 0.0f, 1.0f, t_z,          \
            0.0f, 0.0f, 0.0f, 1.0f          \
        }                                   \

/**
 * Matriz de rotação (eixo z): rotaciona o objeto em relação ao eixo z em theta graus.
 */
#define rotation_z_matrix(theta) {                                                  \
            cos(((theta)*M_PI/180.0)), -sin(((theta)*M_PI/180.0)), 0.0f, 0.0f,      \
            sin(((theta)*M_PI/180.0)),  cos(((theta)*M_PI/180.0)), 0.0f, 0.0f,      \
            0.0f, 0.0f, 1.0f, 0.0f,                                                 \
            0.0f, 0.0f, 0.0f, 1.0f                                                  \
        }

/**
 * Matriz de escala: aplica escala no objeto.
 */
#define scale_matrix(s_x,s_y,s_z) {     \
            s_x, 0.0f, 0.0f, 0.0f,      \
            0.0f, s_y, 0.0f, 0.0f,      \
            0.0f, 0.0f, s_z, 0.0f,      \
            0.0f, 0.0f, 0.0f, 1.0f      \
        }                               \

/**
 * A transformação (rotação ou escala) ocorre em relação à coordenada do objeto.
 */
#define TRANSFORMATION_IN_PLACE       0

/**
 * A transformação (rotação ou escala) ocorre em relação à um ponto de referência.
 */
#define TRANSFORMATION_IN_REFERENCE   1

/**
 * Estrutura para armazenar as coordenadas dos vértices dos objetos.
 */
typedef struct coordinates {
    float x, y;
} coordinates;

/**
 * Estrutura que representa os vértices de um determinado objeto.
 */
typedef struct vertices {
    unsigned int number;
    coordinates *v;
} vertices;

/**
 * Estrutura responsável pelos objetos que serão desenhados na janela da aplicação.
 */
typedef struct glObject glObject;

struct glObject {

    GLint gltransformation;
    GLint glcolor;

    /**
     * Vértices que compoẽm o objeto em questão.
     */
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

};


void initializeObject(glObject *o, vertices *v, void (*draw)(glObject *o));

/* ---------------------------------------- */
void veccpy(coordinates *dest, unsigned int size_dest, coordinates *origin, unsigned int size_origin);
coordinates* veccnt(coordinates *c1, unsigned int size_1, coordinates *c2, unsigned int size_2);

#endif