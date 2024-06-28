#ifndef GUARD_IntLinkedListSortedSetADT
#define GUARD_IntLinkedListSortedSetADT

typedef struct listNode ListNode, *ListNodePtr;

struct listNode {
    int elem;
    ListNodePtr next;
};

struct intSortedSet {
    ListNodePtr first; /* Punta al primo nodo dell'insieme, se l'insieme e' vuoto vale NULL */
    ListNodePtr last; /* Punta all'ultimo nodo dell'insieme, se l'insieme e' vuoto vale NULL */
    int size; /* Numero di elementi presenti nell'insieme */
};

typedef struct intSortedSet IntSet, *IntSetPtr;

#endif