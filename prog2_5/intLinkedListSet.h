#ifndef GUARD_IntLinkedListSetADT
#define GUARD_IntLinkedListSetADT

#include "intSetADT.h"

typedef struct listNode ListNode, *ListNodePtr;

struct listNode {
    int data;
    ListNodePtr next;
};

struct intSet {
    ListNodePtr front; /* Punta al primo nodo dell'insieme, se l'insieme e' vuoto vale NULL */
    int size; /* Numero di elementi presenti nell'insieme */
};

typedef struct intSet IntSet, *IntSetPtr;

#endif