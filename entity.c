#include <stdlib.h>
#include <stdio.h>
#include "entity.h"

void addGlObject(Entity *e, glObject *o);
void addEntity(Entity *e, Entity *attached, float attachment_x, float attachment_y);
void renderEntity(Entity *e);

void initializeEntity(Entity *e) {

    initializeLinkedList(&e->objects);
    initializeLinkedList(&e->entities);

    e->ref_rotation = 0;
    e->ref_rotation_x = e->ref_rotation_y = e->ref_rotation_z = 0.0f;

    e->ref_scale = 0;
    e->ref_scale_x = e->ref_scale_y = e->ref_scale_z = 0.0f;

    e->t_x = e->t_y = e->t_z = 0.0f;
    e->s_x = e->s_y = e->s_z = 1.0f;

    e->theta_z = 0.0f;

    e->addGlObject = addGlObject;
    e->addEntity = addEntity;
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

    o->ref_scale = 1;
    o->ref_scale_x = e->t_x;
    o->ref_scale_y = e->t_y;
    o->ref_scale_z = e->t_z;

    o->ref_rotation = 1;
    o->ref_rotation_x = e->t_x;
    o->ref_rotation_y = e->t_y;
    o->ref_rotation_z = e->t_z;

    e->objects.add(&e->objects, ao);
}

void addEntity(Entity *e, Entity *attached, float attachment_x, float attachment_y) {

    AttachedEntity *ae = (AttachedEntity *) malloc(sizeof(AttachedEntity));

    ae->entity = attached;

    ae->t_x = attached->t_x;
    ae->t_y = attached->t_y;
    ae->t_z = attached->t_z;

    ae->s_x = attached->s_x;
    ae->s_y = attached->s_y;
    ae->s_z = attached->s_z;

    ae->theta_z = attached->theta_z;

    attached->ref_scale = 1;
    attached->ref_scale_x = e->t_x;
    attached->ref_scale_y = e->t_y;
    attached->ref_scale_z = e->t_z;

    attached->ref_rotation = 1;
    attached->ref_rotation_x = attachment_x;
    attached->ref_rotation_y = attachment_y;
    attached->ref_rotation_z = e->t_z;

    e->objects.add(&e->entities, ae);
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