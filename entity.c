#include <stdlib.h>
#include <stdio.h>
#include "entity.h"

void addGlObject(Entity *e, glObject *o);
void addEntity(Entity *e, Entity *attached, float attachment_x, float attachment_y);
void setController(Entity *e, void (*controller)(Entity *e, int key, int action));
void renderEntity(Entity *e);

/**
 * Inicializa uma entidade. Por padrão, transformações de rotação e escala acontecem com
 * referência a posição da própria entidade.
 * @param e entidade a ser inicializada.
 */
void initializeEntity(Entity *e) {

    initializeLinkedList(&e->objects);
    initializeLinkedList(&e->entities);

    e->ref_rotation = TRANSFORMATION_IN_PLACE;
    e->ref_rotation_x = e->ref_rotation_y = e->ref_rotation_z = 0.0f;

    e->ref_scale = TRANSFORMATION_IN_PLACE;
    e->ref_scale_x = e->ref_scale_y = e->ref_scale_z = 0.0f;

    e->t_x = e->t_y = e->t_z = 0.0f;
    e->s_x = e->s_y = e->s_z = 1.0f;

    e->theta_z = 0.0f;

    e->addGlObject = addGlObject;
    e->addEntity = addEntity;
    e->setController = setController;
    e->render = renderEntity;


    e->controller = NULL;
}

/**
 * Adiciona objetos à entidade.
 * @param e entidade.
 * @param o objeto a ser adicionado.
 */
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

    o->ref_scale = TRANSFORMATION_IN_REFERENCE;
    o->ref_scale_x = e->t_x;
    o->ref_scale_y = e->t_y;
    o->ref_scale_z = e->t_z;

    o->ref_rotation = TRANSFORMATION_IN_REFERENCE;
    o->ref_rotation_x = e->t_x;
    o->ref_rotation_y = e->t_y;
    o->ref_rotation_z = e->t_z;

    e->objects.add(&e->objects, ao);
}

/**
 * Adiciona um entidade a outra entidade.
 * @param e entidade alvo.
 * @param attached entidade a ser adicionada.
 * @param attachment_x abscissa de ancoragem.
 * @param attachment_y ordenada de ancoragem.
 */
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

    attached->ref_scale = TRANSFORMATION_IN_REFERENCE;
    attached->ref_scale_x = e->t_x;
    attached->ref_scale_y = e->t_y;
    attached->ref_scale_z = e->t_z;

    attached->ref_rotation = TRANSFORMATION_IN_REFERENCE;
    attached->ref_rotation_x = attachment_x;
    attached->ref_rotation_y = attachment_y;
    attached->ref_rotation_z = e->t_z;

    e->entities.add(&e->entities, ae);
}

/**
 * Define a função que irá receber as entradas do teclado.
 * @param e entidade.
 * @param controller função de controle.
 */
void setController(Entity *e, void (*controller)(Entity *e, int key, int action)) {

    if (e == NULL) return;
    e->controller = controller;
}

/**
 * Renderiza a entidade. A ordem de renderização é a mesma ordem de adição nas listas de
 * entidades anexadas e objetos anexados.
 * @param e entidade.
 */
void renderEntity(Entity *e) {

    Node *nodeObj = e->objects.head;

    while (nodeObj != NULL) {

        AttachedObject *ao = (AttachedObject*) nodeObj->data;

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

        nodeObj = nodeObj->next;
    }

    Node *nodeEnt = e->entities.head;

    while (nodeEnt != NULL) {

        AttachedEntity *ae = (AttachedEntity*) nodeEnt->data;

        ae->entity->t_x = e->t_x + ae->t_x;
        ae->entity->t_y = e->t_y + ae->t_y;
        ae->entity->t_z = e->t_z + ae->t_z;

        ae->entity->s_x = e->s_x * ae->s_x;
        ae->entity->s_y = e->s_y * ae->s_y;
        ae->entity->s_z = e->s_z * ae->s_z;

        ae->entity->theta_z = e->theta_z + ae->theta_z;

        ae->entity->ref_scale_x = e->t_x;
        ae->entity->ref_scale_y = e->t_y;
        ae->entity->ref_scale_z = e->t_z;

        ae->entity->ref_rotation_x = e->t_x + ae->entity->ref_rotation_x;
        ae->entity->ref_rotation_y = e->t_y + ae->entity->ref_rotation_y;
        ae->entity->ref_rotation_z = e->t_z + ae->entity->ref_rotation_z;

        ae->entity->render(ae->entity);
        nodeEnt = nodeEnt->next;
    }

}