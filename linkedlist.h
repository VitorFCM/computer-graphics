//
// Created by lucas on 09/06/22.
//

#ifndef TAD_LINKEDLIST_H
#define TAD_LINKEDLIST_H

#define TRUE    1
#define FALSE   0

#define SUCCESS         0
#define ERROR           1
#define NULL_POINTER    -2
#define MALLOC_ERROR    -3
#define DATA_NOT_FOUND  -4

typedef struct Node {
    unsigned int index;
    void *data;
    struct Node *next;
} Node;

typedef struct LinkedList {

    /**
     * Retorna o tamanho atual da lista encadeada.
     */
    int size;

    /**
     * Ponteiro para o primeiro elemento da lista encadeada.
     */
    Node *head;

    /*  --- Functions ---   */
    int (*add)(struct LinkedList *linkedList, void *data);
    int (*set)(struct LinkedList *linkedList,  unsigned int index, void *data);
    int (*freeSet)(struct LinkedList *linkedList, unsigned int index, void *data, void (*freeData)());
    int (*remove)(struct LinkedList *linkedList, void *data, int (*compareData)(), unsigned short allData);
    int (*freeData)(struct LinkedList *linkedList, void *data, int (*compareData)(), unsigned short allData,
                    void *freeData);
    int (*freeAllData)(struct LinkedList *linkedList, void (*freeData)());
    int (*clear)(struct LinkedList *linkedList);
    void (*print)(struct LinkedList linkedList, void (*printData)());

} LinkedList;

int initializeLinkedList(LinkedList *linkedList);

Node* getNodeIndexLinkedList(LinkedList *linkedList, unsigned index);
Node* getNodeDataLinkedList(LinkedList *linkedList, void *data, void (*compareData)());

int addDataLinkedList(LinkedList *linkedList, void *data); // OK
int removeDataLinkedList(LinkedList *linkedList, void *data, int (*compareData)(), unsigned short allData); // OK
int freeRemoveDataLinkedList(LinkedList *linkedList, void *data, int (*compareData)(), unsigned short allData,
                             void *freeData); // OK

int setDataLinkedList(LinkedList *linkedList, unsigned int index, void *data); // OK
int freeSetDataLinkedList(LinkedList *linkedList, unsigned int index, void *data, void (*freeData)());

int freeLinkedList(LinkedList *linkedList);
int freeAllDataLinkedList(LinkedList *linkedList, void (*freeData)()); // OK

void printLinkedList(LinkedList linkedList, void (*printData)());

#endif //TAD_LINKEDLIST_H
