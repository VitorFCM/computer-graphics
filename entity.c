#include <stdlib.h>
#include <stdio.h>
#include "entity.h"

void addGlObject(Entity *e, glObject *o);
void renderEntity(Entity *e);

void initializeEntity(Entity *e) {

    initializeLinkedList(&e->objects);

    e->ref_rotation_x = e->ref_rotation_y = e->ref_rotation_z = 0.0f;
    e->ref_scale_x = e->ref_scale_y = e->ref_scale_z = 0.0f;

    e->t_x = e->t_y = e->t_z = 0.0f;
    e->s_x = e->s_y = e->s_z = 1.0f;

    e->theta_z = 0.0f;

    e->addGlObject = addGlObject;
    e->render = renderEntity;
}

void addGlObject(Entity *e, glObject *o) {

    AttachedObject *ao = (AttachedObject*) malloc(sizeof(AttachedObject));

    ao->object = o;

    ao->t_x = o->t_x;
    ao->t_y = o->t_y;
    ao->t_z = o->t_z;

    ao->s_x = o->s_x;
    ao->s_y = o->s_y;
    ao->s_z = o->s_z;

    ao->theta_z = o->theta_z;

    o->ref_rotation = 1;
    o->ref_scale = 1;

    o->ref_scale_x = e->t_x;
    o->ref_scale_y = e->t_y;
    o->ref_scale_z = e->t_z;

    o->ref_rotation_x = e->t_x;
    o->ref_rotation_y = e->t_y;
    o->ref_rotation_z = e->t_z;

    e->objects.add(&e->objects, ao);
}

void renderEntity(Entity *e) {

    Node *node = e->objects.head;

    while (node != NULL) {

        AttachedObject *ao = (AttachedObject*) node->data;

        ao->object->t_x = e->t_x + ao->t_x;
        ao->object->t_y = e->t_y + ao->t_y;
        ao->object->t_z = e->t_z + ao->t_z;

        ao->object->s_x = e->s_x * ao->s_x;
        ao->object->s_y = e->s_y * ao->s_y;
        ao->object->s_z = e->s_z * ao->s_z;

        ao->object->theta_z = e->theta_z + ao->theta_z;

        ao->object->ref_scale_x = e->t_x;
        ao->object->ref_scale_y = e->t_y;
        ao->object->ref_scale_z = e->t_z;

        ao->object->ref_rotation_x = e->t_x;
        ao->object->ref_rotation_y = e->t_y;
        ao->object->ref_rotation_z = e->t_z;

        ao->object->render(ao->object);

        node = node->next;
    }
}