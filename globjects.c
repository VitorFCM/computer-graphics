#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "globjects.h"
#include "program.h"

void destroyObject(glObject *o);
void loadBuffer(glObject *o);
void transform(glObject *o);
void color(glObject *o);
void render(glObject *o);

void multiplica(float *m1, float *m2, float *m_resultado);

/**
 * Inicializa um objeto. Todos os objetos na aplicação precisam ter seus vértices informados
 * juntamente com a função que os controem.
 * @param o objeto a ser inicializado.
 * @param v vértices do objeto.
 * @param draw função que irá desenhar o objeto.
 */
void initializeObject(glObject *o, vertices *v, void (*draw)(glObject *o)) {

    if (o == NULL) return;

    o->gltransformation = getGLTransformation();
    o->glcolor = getGLColor();

    o->vertices = v;

    o->ref_rotation = TRANSFORMATION_IN_PLACE;
    o->ref_rotation_x = o->ref_rotation_y = o->ref_rotation_z = 0.0f;
    o->ref_scale = TRANSFORMATION_IN_PLACE;
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
    o->render = render;
    o->draw = draw;
}

void destroyObject(glObject *o) {
    free(o->vertices);
}

/**
 * Carrega os vértices do objeto no buffer da aplicação.
 * @param o objeto.
 */
void loadBuffer(glObject *o) {
    if (o == NULL) return;
    glBufferData(GL_ARRAY_BUFFER, o->vertices->number * sizeof(coordinates), o->vertices->v, GL_DYNAMIC_DRAW);
}

/**
 * Aplica uma transformação (composta por translação, rotação e escala) no objeto.
 * A sequência de transformações é: translação -> rotação -> escala.
 *
 * @param o objeto que sofrerá a transformação.
 */
void transform(glObject *o) {

    if (o == NULL) return;

    float c_t_x, c_t_y, c_t_z;
    float c_ref_rot_x, c_ref_rot_y, c_ref_rot_z;
    float c_ref_sca_x, c_ref_sca_y, c_ref_sca_z;

    c_t_x = convertValue(o->t_x);
    c_t_y = convertValue(o->t_y);
    c_t_z = convertValue(o->t_z);

    c_ref_rot_x = convertValue(o->ref_rotation_x);
    c_ref_rot_y = convertValue(o->ref_rotation_y);
    c_ref_rot_z = convertValue(o->ref_rotation_z);

    c_ref_sca_x = convertValue(o->ref_scale_x);
    c_ref_sca_y = convertValue(o->ref_scale_y);
    c_ref_sca_z = convertValue(o->ref_scale_z);

    float transformation[] = translation_matrix(c_t_x,c_t_y,c_t_z);

    float dx, dy, dz;
    if (o->ref_rotation == TRANSFORMATION_IN_PLACE) {
        dx = c_t_x;
        dy = c_t_y;
        dz = c_t_z;
    } else {
        dx = c_ref_rot_x;
        dy = c_ref_rot_y;
        dz = c_ref_rot_z;
    }

    float tranls1[] = translation_matrix(-dx, -dy, -dz);
    float rot[] = rotation_z_matrix(o->theta_z);
    float tranls2[] = translation_matrix(dx, dy, dz);

    multiplica(tranls1, transformation, transformation);
    multiplica(rot, transformation, transformation);
    multiplica(tranls2, transformation, transformation);

    if (o->ref_scale == TRANSFORMATION_IN_PLACE) {
        dx = c_t_x;
        dy = c_t_y;
        dz = c_t_z;
    } else {
        dx = c_ref_sca_x;
        dy = c_ref_sca_y;
        dz = c_ref_sca_z;
    }

    float tranls3[] = translation_matrix(-dx, -dy, -dz);
    float sca[] = scale_matrix(o->s_x, o->s_y, o->s_z);
    float tranls4[] = translation_matrix(dx, dy, dz);

    multiplica(tranls3, transformation, transformation);
    multiplica(sca, transformation, transformation);
    multiplica(tranls4, transformation, transformation);

    glUniformMatrix4fv(o->gltransformation, 1, GL_TRUE, transformation);
}

/**
 * Aplica a coloração no objeto.
 * @param o objeto.
 */
void color(glObject *o) {

    if (o == NULL) return;
    glUniform4f(o->glcolor, o->v0, o->v1, o->v2, o->v3);
}

/**
 * Renderiza o objeto, carregando seus vértices no buffer da aplicação, aplicando transformação e
 * colorindo-o.
 * @param o objeto a ser renderizado.
 */
void render(glObject *o) {

    if (o == NULL) return;
    loadBuffer(o);
    transform(o);
    color(o);
    o->draw();
}

// **********************************************************************

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