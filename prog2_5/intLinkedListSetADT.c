#include <stdlib.h>
#include <stdbool.h>

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

IntSetADT mkSet() {
    IntSetPtr set = malloc(sizeof(IntSet));
    
    if (set == NULL)
        return NULL;
    
    set -> front = NULL;
    set -> size = 0;

    return set;
}

_Bool dsSet(IntSetADT *sp) {
    if(!sp || !(*sp)){
        return false;
    }
    ListNodePtr aux, curr = (*sp)->front;

    while(curr != NULL){
        aux = curr;
        curr = curr ->next;
        free(aux);
    }

    free(*sp);
    *sp = NULL;
    return true;
}

_Bool set_add(IntSetADT set, const int elem) {
    if(!set){
        return 0;
    }

    ListNodePtr curr = set->front;
    while(curr != NULL){
        if(curr -> data == elem){
            return false;
        }
        curr = curr->next;
    }

    ListNodePtr new_elem= malloc(sizeof(ListNode));
    if(new_elem == NULL){
        return NULL;
    }

    new_elem->data = elem;
    new_elem->next = set->front;
    set->front = new_elem;

    set -> size++;

    return true;
}

_Bool set_remove(IntSetADT set, const int elem) {
    if (!set){
        return 0;
    }
    if (set -> size == 0){
        return 0;
    }
    
    if (set->front->data == elem){ 
        ListNodePtr to_remove = set->front;
        set->front = set->front->next;
        free(to_remove);
    
        set->size--;
        return 1;
    };
    
    int found = 0;
    for(ListNodePtr curr = set -> front; curr != NULL; curr = curr->next){
        ListNodePtr prev = curr;
        curr = curr -> next;
        
        if(curr->data == elem){
            found = 1;
            // fprintf(stderr, "%d %p\n", curr -> data, curr -> next);
            
            ListNodePtr to_remove = curr;
            prev -> next = curr -> next;
            free(to_remove);

            set->size--;
            break;
        }
    }
    return found;
}

_Bool set_member(const IntSetADT set, const int elem) {
    if(!set){
        return 0;
    }
    if(set->size == 0){
        return 0;
    }
    int found = 0;
    ListNodePtr curr = set->front;
    while(curr != NULL && !found){
        if(curr->data == elem){
            found = 1;
        }
        curr = curr->next;
    }
    return found;
}

_Bool isEmptySet(const IntSetADT set){  // nota: restituire false se l'insieme non esiste, anche se ambiguo con caso di insieme non vuoto
    if (set == NULL)
        return 0;
    return (set->size == 0);
}

int set_size(const IntSetADT set) {
    if(!set)
        return -1;
    return set->size;
}

_Bool set_extract(IntSetADT set, int *datap) {
    if(set == NULL)
        return 0;
        
    if(set->size == 0)
        return 0;
        
    int position = rand() % set -> size; // 0...set->size - 1
    ListNodePtr curr = set->front;
    for(size_t i = 0; i < position; i++ ){
        curr = curr -> next;
    }
    
    //fprintf(stderr, "%d: %d\n", position, curr->data);
    *datap = curr->data;
    set_remove(set, *datap);
    
    return 1;    
}

_Bool set_equals(const IntSetADT set1, const IntSetADT set2) {
   if (!set1 && !set2){ // Both sets are empty
        return 1;
    }
    
    
    if (!set1 || !set2) // One set is empty while the other is not
        return 0;

    if(set1->size == 0 && set2->size == 0){
        return 1;
    }
    
    int uguale = 0;
    
    if( set1->size != set2 ->size ){
        uguale = 0;
    } else {
        uguale = 0;
        ListNodePtr curr1 = set1->front;
        ListNodePtr curr2 = set2->front;
        for(;(curr1 != NULL && curr2 !=NULL) || !uguale; ){
            curr1 = curr1 ->next;
            curr2 = curr2->next;
            if(curr1 == curr2)
                uguale = 1;
        }
    }

    return uguale;
}

_Bool subseteq(const IntSetADT set1, const IntSetADT set2) {
    if(set1 == NULL || set2 == NULL)
        return 0;
   
    if(set1 -> size == 0 && set2 -> size >= 0) {
        return 1;
    }
    //fprintf(stderr, "%d %d\n", set1->size, set2 -> size );
    
    ListNodePtr curr = set1 -> front;
     
    for (;curr != NULL;) {
        if (set_member(set2, curr -> data) == 0)
            return 0;
         
        curr = curr -> next;
    }
     
    return 1; 
}

_Bool subset(const IntSetADT set1, const IntSetADT set2) {
    if(set1 == NULL || set2 == NULL)
        return 0;
   
    if(set1 -> size == 0 && set2 -> size >= 0) {
        return 1;
    }
    
    if(set1 -> size == set2 -> size) 
        return 0;
    
    ListNodePtr curr = set1 -> front;
     
    for (;curr != NULL;) {
        if (set_member(set2, curr -> data) == 0)
            return 0;
         
        curr = curr -> next;
    }
    
    return 1;
}

IntSetADT set_union(const IntSetADT set1, const IntSetADT set2) {
    if(set1 == NULL || set2 == NULL)
        return 0;
    
    IntSetADT newSet = mkSet();
    ListNodePtr curr1 = set1 -> front;
    ListNodePtr curr2 = set2 -> front;
   
    while(curr1 != NULL){
        // set1
        set_add(newSet,curr1->data);
        curr1 = curr1 -> next;
    }
    while(curr2 != NULL){
        // set2
        set_add(newSet,curr2->data);
        curr2 = curr2 -> next;
    }
    
    return newSet;
}

IntSetADT set_intersection(const IntSetADT set1, const IntSetADT set2) {
    if(set1 == NULL || set2 == NULL)
        return 0;
        
    IntSetADT newSet = mkSet();
    
    ListNodePtr curr1 = set1 -> front;
    while (curr1 != NULL) {
     //for (ListNodePtr curr1 = set1 -> front; curr1 != NULL; curr1 = curr1 -> next)
        if (set_member(set2, curr1 -> data) == 1)
            set_add(newSet, curr1 -> data);
        
        curr1 = curr1 -> next;
    }

    return newSet;
}


IntSetADT set_subtraction(const IntSetADT set1, const IntSetADT set2) {
    if(set1 == NULL || set2 == NULL)
        return 0;
        
    IntSetADT newSet = mkSet();
    
    ListNodePtr curr1 = set1 -> front;
    while (curr1 != NULL) {
     //for (ListNodePtr curr1 = set1 -> front; curr1 != NULL; curr1 = curr1 -> next)
        if (set_member(set2, curr1 -> data) == 0)
            set_add(newSet, curr1 -> data);
        
        curr1 = curr1 -> next;
    }

    return newSet;
    
    return 0;
}