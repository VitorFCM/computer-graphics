//
// Created by lucas on 09/06/22.
//

#include "stdio.h"
#include "stdlib.h"
#include "linkedlist.h"

/**
 * Inicializa os parâmetros internos da lista encadeada simples.
 *
 * @param linkedList lista a ser inicializada.
 * @return retorna <b>NULL_POINTER</b> se o ponteiro da lista for nulo,
 * <b>SUCCESS</b> caso contrário.
 */
int initializeLinkedList(LinkedList *linkedList) {

    if (linkedList == NULL) return NULL_POINTER;

    linkedList->head = NULL;
    linkedList->size = 0;

    /*  --- Functions ---   */
    linkedList->add = addDataLinkedList;
    linkedList->set = setDataLinkedList;
    linkedList->freeSet = freeSetDataLinkedList;
    linkedList->remove = removeDataLinkedList;
    linkedList->freeData = freeRemoveDataLinkedList;
    linkedList->freeAllData = freeAllDataLinkedList;
    linkedList->clear = freeLinkedList;
    linkedList->print = printLinkedList;

    return SUCCESS;
}

/**
 * Adiciona um novo dado na lista encadeada simples.
 *
 * @param linkedList lista encadeada.
 * @param data ponteiro para o dado a ser adicionado.
 * @return retorna <b>NULL_POINTER</b> se o ponteiro da lista for nulo,
 * <b>MALLOC_ERROR</b> se não houver memória para alocar um novo nodo para lista,
 * <b>SUCCESS</b> caso contrário.
 */
int addDataLinkedList(LinkedList *linkedList, void *data) {

    if (linkedList == NULL) return NULL_POINTER;

    Node *node = (Node*) malloc(sizeof(Node));
    if (node == NULL) return MALLOC_ERROR;

    node->index = linkedList->size;
    node->next = NULL;
    node->data = data;

    if (linkedList->size != 0) {

        Node *aux = linkedList->head;
        while (aux->next != NULL) aux = aux->next;
        aux->next = node;

    } else linkedList->head = node;


    linkedList->size++;

    return SUCCESS;
}

/**
 * Remove um ou mais nodos contendo o dado especificado.
 * <p><b>Observação:</b> apenas a memória dos nodos é liberada nesta função. Para liberar a memória dos dados também,
 * utilize a função <i>freeRemoveDataLinkedList</i></p>
 *
 * @param linkedList lista encadeada
 * @param data dado que será removido da lista
 * @param compareData função utilizada para comparar os dados da lista encadeada.
 * @param allData se for TRUE, todos os nodos com o dado passado serão removidos, se for FALSE apenas o primeiro
 * será retirado da lista.
 * @return retorna <b>NULL_POINTER</b> se o ponteiro da lista for nulo,
 * <b>DATA_NOT_FOUND</b> se nenhum dado foi removido,
 * <b>SUCCESS</b> caso contrário.
 */
int removeDataLinkedList(LinkedList *linkedList, void *data, int (*compareData)(), unsigned short allData) {

    if (linkedList == NULL) return NULL_POINTER;
    if (linkedList->size == 0) return DATA_NOT_FOUND;

    Node *prevNode = linkedList->head;
    Node *node = linkedList->head;
    int dataRemoved = 0;
    int flag = 0;

    while (compareData(node->data, data) == 0 && flag == 0) {

        linkedList->head = node->next;
        free(node);
        dataRemoved++;
        node = linkedList->head;

        if (allData == FALSE) flag = 1;
    }

    prevNode = linkedList->head;
    node = linkedList->head;

    while (node != NULL) {

        if (compareData(node->data, data) == 0 && flag == 0) {

            if (allData == FALSE) flag = 1;

            prevNode->next = node->next;
            dataRemoved++;
            free(node);
            node = prevNode->next;

            if (node != NULL) node->index -= dataRemoved;

        } else {

            if (node->next != NULL) node->next->index -= dataRemoved;

            prevNode = node;
            node = node->next;

        }
    }

    linkedList->size -= dataRemoved;

    if (dataRemoved > 0) return SUCCESS;
    else return DATA_NOT_FOUND;
 }

int freeRemoveDataLinkedList(LinkedList *linkedList, void *data, int (*compareData)(), unsigned short allData,
                             void *freeData) {

    if (linkedList == NULL) return NULL_POINTER;
    if (linkedList->size == 0) return DATA_NOT_FOUND;

    LinkedList dataRemovedList;
    initializeLinkedList(&dataRemovedList);

    Node *prevNode = linkedList->head;
    Node *node = linkedList->head;
    int dataRemoved = 0;
    int flag = 0;

    while (compareData(node->data, data) == 0 && flag == 0) {

        linkedList->head = node->next;
        addDataLinkedList(&dataRemovedList, node->data);
        free(node);
        dataRemoved++;
        node = linkedList->head;

        if (allData == FALSE) flag = 1;
    }

    prevNode = linkedList->head;
    node = linkedList->head;

    while (node != NULL) {

        if (compareData(node->data, data) == 0 && flag == 0) {

            if (allData == FALSE) flag = 1;

            prevNode->next = node->next;
            dataRemoved++;
            addDataLinkedList(&dataRemovedList, node->data);
            free(node);
            node = prevNode->next;

            if (node != NULL) node->index -= dataRemoved;

        } else {

            if (node->next != NULL) node->next->index -= dataRemoved;

            prevNode = node;
            node = node->next;

        }
    }

    linkedList->size -= dataRemoved;

    freeAllDataLinkedList(&dataRemovedList, freeData);

    if (dataRemoved > 0) return SUCCESS;
    else return DATA_NOT_FOUND;
}

/**
 * Altera o dado armazenado de uma posição com um determinado índice.
 * <p><b>Observações:</b></p>
 * <p> - Se o índice passado for maior ou igual ao tamanho da lista, novos nodos, com dados nulos,
 * serão adicionados até que a lista possua tamanho (índice + 1).</p>
 * <p> - Quando um dado é trocado pelo outro, <b>não ocorre a liberação de memória</b> do antigo dado. Para isso, use a
 * função <i>freeSetDataLinkedList</i></p>
 *
 * @param linkedList lista encadeada.
 * @param index índice da posição no qual o dado será setado.
 * @param data ponteiro para o novo dado a ser salvo na lista.
 * @return retorna <b>NULL_POINTER</b> se o ponteiro da lista for nulo,
 * <b>MALLOC_ERROR</b> se não houver memória para alocar um novo nodo para lista,
 * <b>SUCCESS</b> caso contrário.
 */
int setDataLinkedList(LinkedList *linkedList, unsigned int index, void *data) {

    if (linkedList == NULL) return NULL_POINTER;

    if (index < linkedList->size) {

        Node *node = linkedList->head;
        for (int i = 0; i < index; i++) node = node->next;
        node->data = data;

    } else {

        Node *aux = linkedList->head;
        while (aux->next != NULL) aux = aux->next;

        for (int i = linkedList->size; i <= index; i++) {

            Node *node = (Node*) malloc(sizeof(Node));
            if (node == NULL) return MALLOC_ERROR;

            node->index = linkedList->size;
            node->data = NULL;
            node->next = NULL;

            if (i == index) node->data = data;

            aux->next = node;
            aux = node;

            linkedList->size++;
        }
    }

    return SUCCESS;
}

/**
 * Altera o dado armazenado de uma posição com um determinado índice.
 * <p><b>Observações:</b></p>
 * <p> - Se o índice passado for maior ou igual ao tamanho da lista, novos nodos, com dados nulos,
 * serão adicionados até que a lista possua tamanho (índice + 1).</p>
 * <p> - Quando um dado é trocado pelo outro, <b>ocorre a liberação de memória</b> do antigo dado.</p>
 *
 * @param linkedList lista encadeada.
 * @param index índice da posição no qual o dado será setado.
 * @param data ponteiro para o novo dado a ser salvo na lista.
 * @param freeData função utilizada para liberar a memória do tipo de dado da lista encadeada.
 * @return retorna <b>NULL_POINTER</b> se o ponteiro da lista for nulo,
 * <b>MALLOC_ERROR</b> se não houver memória para alocar um novo nodo para lista,
 * <b>SUCCESS</b> caso contrário.
 */
int freeSetDataLinkedList(LinkedList *linkedList, unsigned int index, void *data, void (*freeData)()) {

    if (linkedList == NULL) return NULL_POINTER;

    if (index >= linkedList->size) return setDataLinkedList(linkedList, index, data);

    Node *node = linkedList->head;
    for (int i = 0; i < index; i++) node = node->next;
    freeData(node->data);
    node->data = data;

    return SUCCESS;
}

/**
 * Libera toda a memória alocada para a geração da lista encadeada.
 * <p><b>Observação:</b> não libera a memória dos dados armazenados.</p>
 *
 * @param linkedList lista encadeada.
 * @return retorna <b>NULL_POINTER</b> se o ponteiro da lista for nulo,
 * <b>SUCCESS</b> caso contrário.
 */
int freeLinkedList(LinkedList *linkedList) {

    if (linkedList == NULL) return NULL_POINTER;

    for (int i = 0; i < linkedList->size; i++) {
        Node *aux = linkedList->head->next;
        free(linkedList->head);
        linkedList->head = aux;
    }

    return SUCCESS;
}

/**
 * Libera toda a memória alocada para a geração da lista encadeada.
 * <p><b>Observação:</b> libera a memória dos dados armazenados.</p>
 *
 * @param linkedList lista encadeada.
 * @param freeData função que libera a memória do tipo de dado salvo na lista encadeada.
 * @return retorna <b>NULL_POINTER</b> se o ponteiro da lista for nulo,
 * <b>SUCCESS</b> caso contrário.
 */
int freeAllDataLinkedList(LinkedList *linkedList, void (*freeData)()) {

    if (linkedList == NULL) return NULL_POINTER;

    for (int i = 0; i < linkedList->size; i++) {
        Node *aux = linkedList->head->next;
        freeData(linkedList->head);
        free(linkedList->head);
        linkedList->head = aux;
    }

    return SUCCESS;
}

void printLinkedList(LinkedList linkedList, void (*printData)()) {

    Node *node = linkedList.head;
    for (int i = 0; i < linkedList.size; i++) {
        printf("{ i: %d | ", node->index);
        printData(node->data);
        printf("}");
        node = node->next;
    }
}
