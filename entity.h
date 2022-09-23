#ifndef ENTITY_H
#define ENTITY_H

#include "linkedlist.h"
#include "globjects.h"

typedef struct AttachedObject {

    glObject *object;

    float t_x;
    float t_y;
    float t_z;

    float s_x;
    float s_y;
    float s_z;

    float theta_z;

} AttachedObject;

typedef struct Entity Entity;

typedef struct AttachedEntity {

    Entity *entity;

    float t_x;
    float t_y;
    float t_z;

    float s_x;
    float s_y;
    float s_z;

    float theta_z;

} AttachedEntity;

typedef struct Entity {

    LinkedList objects;
    LinkedList entities;

    float t_x;
    float t_y;
    float t_z;

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

    void (*controller)(Entity *e, int key, int action);

    void (*addGlObject)(Entity *e, glObject *o);
    void (*addEntity)(Entity *e, Entity *attached, float attachment_x, float attachment_y);
    void (*setController)(Entity *e, void (*controller)(Entity *e, int key, int action));
    void (*render)();

} Entity;

void initializeEntity(Entity *e);

#endif
