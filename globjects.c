#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "globjects.h"

void multiplica(float *m1, float *m2, float *m_resultado);
void destroyObject(glObject *o);
void loadBuffer(glObject *o);
void transform(glObject *o);
void color(glObject *o);

void initializeObject(glObject *o, unsigned int number_verticex, GLint gltransformation, GLint glcolor, void (*draw)()) {

    if (o == NULL) return;

    o->gltransformation = gltransformation;
    o->glcolor = glcolor;

    o->number_vertices = number_verticex;
    o->vertices = (coordinates*) malloc(sizeof(coordinates) * number_verticex);

    o->ref_rotation = 0;
    o->ref_rotation_x = o->ref_rotation_y = o->ref_rotation_z = 0.0f;
    o->ref_scale = 0;
    o->ref_scale_x = o->ref_scale_y = o->ref_scale_z = 0.0f;
    
    o->v0 = o->v3 = 1.0f;
    o->v1 = o->v2 = 0.0f;

    o->t_x = o->t_y = o->t_z = 0.0f;
    o->s_x = o->s_y = o->s_z = 1.0f;

    o->theta_z = 0.0f;

    o->destroy = destroyObject;
    o->loadBuffer = loadBuffer;
    o->transform = transform;
    o->color = color;
    o->draw = draw;
}

void destroyObject(glObject *o) {
    free(o->vertices);
}

void loadBuffer(glObject *o) {
    if (o == NULL) return;
    glBufferData(GL_ARRAY_BUFFER, o->number_vertices * sizeof(coordinates), o->vertices, GL_DYNAMIC_DRAW);
}

void transform(glObject *o) { // sequencia: translada -> rotacionada -> escala

    if (o == NULL) return;

    float transformation[] = translation_matrix(o->t_x,o->t_y,o->t_z);

    float dx, dy, dz;
    if (o->ref_rotation == 0) {
        dx = o->t_x;
        dy = o->t_y;
        dz = o->t_z;
    } else {
        dx = o->ref_rotation_x;
        dy = o->ref_rotation_y;
        dz = o->ref_rotation_z;
    }

    float tranls1[] = translation_matrix(-dx, -dy, -dz);
    float rot[] = rotation_z_matrix(o->theta_z);
    float tranls2[] = translation_matrix(dx, dy, dz);

    multiplica(tranls1, transformation, transformation);
    multiplica(rot, transformation, transformation);
    multiplica(tranls2, transformation, transformation);

    if (o->ref_scale == 0) {
        dx = o->t_x;
        dy = o->t_y;
        dz = o->t_z;
    } else {
        dx = o->ref_scale_x;
        dy = o->ref_scale_y;
        dz = o->ref_scale_z;
    }

    float tranls3[] = translation_matrix(-dx, -dy, -dz);
    float sca[] = scale_matrix(o->s_x, o->s_y, o->s_z);
    float tranls4[] = translation_matrix(dx, dy, dz);

    multiplica(tranls3, transformation, transformation);
    multiplica(sca, transformation, transformation);
    multiplica(tranls4, transformation, transformation);

    glUniformMatrix4fv(o->gltransformation, 1, GL_TRUE, transformation);
}

void color(glObject *o) {

    if (o == NULL) return;
    glUniform4f(o->glcolor, o->v0, o->v1, o->v2, o->v3);
}

void veccpy(coordinates *dest, unsigned int size_dest, coordinates *origin, unsigned int size_origin) {
    
    if (size_dest != size_origin) return;
    for (int i = 0; i < size_dest; i++) dest[i] = origin[i];
}

coordinates* veccnt(coordinates *c1, unsigned int size_1, coordinates *c2, unsigned int size_2) {

    coordinates *retval = malloc(sizeof(coordinates) * (size_1 + size_2));
    
    int i;
    for (i = 0; i < size_1; i++) retval[i] = c1[i];
    for (int j = 0; j < size_2; j++) retval[i + j] = c2[j];
    
    return retval;
}

void multiplica(float *m1, float *m2, float *m_resultado) {

    float m_a[4][4];
    float m_b[4][4];
    float m_c[4][4]; // m_c = m_a * m_b

    int n = 0;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            m_a[i][j] = m1[n];
            m_b[i][j] = m2[n];
            n += 1;
        }
    }


    for (int i = 0; i < 4 ; i++){    
        for (int j = 0; j < 4 ; j++){
            m_c[i][j] = 0.0f;
            for(int k = 0; k < 4; k++){
                m_c[i][j] += m_a[i][k] * m_b[k][j];    
            }
        }
    }

    n = 0;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            m_resultado[n] = m_c[i][j];
            n += 1;
        }
    }
}

void print_matriz_4x4(float *m) {
    for (int i = 0; i < 16; i++) {
        printf("%.2f ", m[i]);
        if ((i + 1) % 4 == 0 && i != 0) printf("\n");
    }
}