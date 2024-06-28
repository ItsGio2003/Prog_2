#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "sortedSetADT.h"

typedef struct listNode ListNode, *ListNodePtr;

struct listNode {
    void* elem;
    ListNodePtr next;
};

struct sortedSetADT {
    ListNodePtr first; /* Punta al primo nodo dell'insieme, se l'insieme e' vuoto vale NULL */
    ListNodePtr last; /* Punta all'ultimo nodo dell'insieme, se l'insieme e' vuoto vale NULL */
    int (*compare)(void*, void*); /* confronto tra due elementi: -1,0,1 se primo precede, uguale o segue il secondo */
    int size; /* Numero di elementi presenti nell'insieme */
};
typedef struct sortedSetADT SortedSetADT, *SortedSetADTptr;

// for debug: stampa un insieme
void stampaSet(SortedSetADTptr ss, void (*stampaelem)(void*)) {
    ListNodePtr cur;
    if(!ss) printf("Insieme non esiste\n");
    else if(sset_size(ss) == 0) printf("Insieme vuoto\n");
    else {
        printf("Insieme: (size %d) ",ss->size);
        for(cur = ss->first; cur; cur=cur->next) (*stampaelem)(cur->elem);
        printf("\n");
    }
}    

// restituisce un insieme vuoto impostando funzione di confronto, NULL se errore
SortedSetADTptr mkSSet(int (*compare)(void*, void*)) {
    SortedSetADTptr set = malloc(sizeof(SortedSetADT));
    if(set == NULL)
        return NULL;
        
    set -> first = NULL;
    set -> last = NULL;
    set -> size = 0;
    set -> compare = compare;
    
    return set;
}

// distrugge l'insieme, recuperando la memoria
_Bool dsSSet(SortedSetADTptr* ssptr) {
    if(!ssptr || !(*ssptr)){
        return false;
    }
    ListNodePtr aux, curr = (*ssptr) -> first;

    while(curr != NULL){
        aux = curr;
        curr = curr -> next;
        free(aux);
    }

    free(*ssptr);
    *ssptr = NULL;
    return 1;
}

// aggiunge un elemento all'insieme 
_Bool sset_add(SortedSetADTptr ss, void* elem) { 
    if (ss == NULL)
        return false;
    
    if (sset_member(ss, elem) == true)
        return false;
    
    ListNodePtr newLst = malloc(sizeof(ListNode));
    newLst -> elem = elem;

    if (ss -> size == 0) {
        ss -> first = newLst;
        ss -> last = newLst;
        newLst -> next = NULL;

    } else {
        ListNodePtr prev = NULL;
        ListNodePtr curr = ss -> first;
        
        while (curr != NULL && (*ss-> compare)(curr -> elem, elem) == -1) {
            prev = curr;
            curr = curr -> next;
        }
        
        if (prev == NULL) {
            // se sono presenti solo elementi più grandi di elem
            newLst -> next = ss -> first;
            ss -> first = newLst;
            
        } else if (curr == NULL) {
            // se arrivo alla fine della lista senza trovare un elemento più grande di elem
            ss -> last -> next = newLst;
            ss -> last = newLst;
            newLst -> next = NULL;
            
        } else {
            // se raggiungo un elemento più grande di elem
            prev -> next = newLst;
            newLst -> next = curr;
        }
    }
    
    ss -> size++;
    return true;
}  

// toglie un elemento all'insieme 
_Bool sset_remove(SortedSetADTptr ss, void* elem) {
    if (ss == NULL || ss -> size == 0)
            return false;
    
        if (ss -> size == 1) {
            if (/*ss -> first -> elem == elem*/ (*ss -> compare)(ss -> first -> elem, elem) == 0) {
                free(ss -> first);
    
                ss -> first = NULL;
                ss -> last = NULL;
                ss -> size = 0;
    
                return true;
            }
            
            return false;
        }
    
        if (/*ss -> first -> elem > elem*/ (*ss -> compare)(ss->first->elem,elem) == 1  || /*ss -> last -> elem < elem*/ (*ss -> compare)(ss->last->elem,elem) == -1)
            return false;
        
        if (/*ss -> first -> elem == elem*/ (*ss -> compare)(ss->first->elem,elem) == 0) {
            ListNodePtr tmp = ss -> first;
            ss -> first = ss -> first -> next;
    
            free(tmp);
        
        } else {
            ListNodePtr prev = NULL;
            ListNodePtr curr = ss -> first;
            while (curr != NULL && /*curr -> elem != elem*/ !((*ss->compare)(curr->elem,elem) == 0)) {
                prev = curr;
                curr = curr -> next;
            
                // se non esiste l'elemento
                if (/*curr -> elem > elem*/ (*ss -> compare)(curr -> elem,elem) == 1)
                    return false;
            }
    
            prev -> next = curr -> next;
            free(curr);
            if (prev -> next == NULL)
                ss -> last = prev;
        }
    
        ss -> size--;
        return true;
}

// controlla se un elemento appartiene all'insieme
int sset_member(const SortedSetADT* ss, void* elem) {
    if(!ss || ss-> size == 0)
        return -1;
    
    if (/*ss -> first -> elem == elem*/ (*ss -> compare)(ss->first->elem,elem) == 0 || /*ss -> last -> elem == elem*/ (*ss->compare)(ss -> last -> elem, elem) == 0 ) 
        return 1;

    int found = 0;
    ListNodePtr curr = ss -> first;
    while(curr != NULL && !found){
        if(/*curr->elem == elem*/ (*ss -> compare)(curr -> elem ,elem) == 0 )
            found = 1;
        curr = curr -> next;
    }
    return found;
}
    
// controlla se l'insieme e' vuoto    
int isEmptySSet(const SortedSetADT* ss) {
    if(!ss)
        return -1;
    
    return (ss -> size == 0);
} 

// restituisce il numero di elementi presenti nell'insieme
int sset_size(const SortedSetADT* ss) {
    if(!ss)
        return -1;
        
    return ss -> size;
} 

_Bool sset_extract(SortedSetADTptr ss, void**ptr) { // toglie e restituisce un elemento a caso dall'insieme
    if(!ss)
        return 0;
        
    if(ss -> size == 0)
        return 0;
    
    int position = rand() % ss -> size;
    ListNodePtr curr = ss -> first;
    
    for(size_t i = 0; i < position ; i++ ){
        curr = curr -> next;
    }
    
    *ptr = curr -> elem;
    sset_remove(ss, *ptr);
    
    return 1;
} 

// controlla se due insiemi sono uguali
int sset_equals(const SortedSetADT* s1, const SortedSetADT* s2) { 
    if (!s1 && !s2)
        return 1;
    if (!s1 || !s2) 
        return -1;
    if(s1 -> size == 0 && s2->size == 0)
        return 1;
        
    if(s1 -> size == 0 && s2 -> size > 0)
        return 0;
    
    if(s1 -> size != s2 -> size ){
        return 0;
    } else {
        ListNodePtr curr1 = s1 -> first;
        
        while(curr1 != NULL){
            if(sset_member(s2,curr1 -> elem) == 0)
                return 0;
                
            curr1 = curr1 -> next;
        }
        
    }
    
    return 1 ;
}

// controlla se il primo insieme e' incluso nel secondo
int sset_subseteq(const SortedSetADT* s1, const SortedSetADT* s2) {
    if(!s2)
        return -1;
    
    if (!s1)
        return -1;
    
    if(s1->size == 0 && s2->size == 0)
        return 1;
    
    if (s1->size > s2->size)
        return 0;
        
    ListNodePtr curr1 = s1 -> first;
    while (curr1 != NULL){
        if(sset_member(s2,curr1 -> elem) == 0)
            return -1;
        
        curr1 = curr1 -> next;
    }
    return 1;
}

// controlla se il primo insieme e' incluso strettamente nel secondo
int sset_subset(const SortedSetADT* s1, const SortedSetADT* s2) {
    
    if (!s2) 
        return -1;
    
    if (!s1)
        return -1;
    
    if (s1->size == 0 && s2->size == 0)
        return 1;
        
    if( s1 -> size > 0 && s2 -> size == 0)
        return 0;
    
    if (s1->size > s2->size)
        return -1;
    
    if (s1->size == s2->size)
        return 0; 
    
    ListNodePtr curr1 = s1 -> first;
    while (curr1 != NULL){
        
        if(sset_member(s2,curr1 -> elem) == 0)
            return 0;
        
        curr1 = curr1 -> next;
    }
    return 1;
} 

// restituisce la sottrazione primo insieme meno il secondo, NULL se errore
SortedSetADTptr sset_subtraction(const SortedSetADT* s1, const SortedSetADT* s2) {
    if(!s1 || !s2)
        return 0;
    
    SortedSetADTptr newset = mkSSet(s1 -> compare);
    
    ListNodePtr curr1 = s1 -> first;
    
    while(curr1 != NULL){
        if(sset_member(s2, curr1 -> elem) == -1 || sset_member(s2, curr1 -> elem) == 0 )
            sset_add(newset, curr1 -> elem);
        
        curr1 = curr1 -> next;
    }
    return newset;  
} 

// restituisce l'unione di due insiemi, NULL se errore
SortedSetADTptr sset_union(const SortedSetADT* s1, const SortedSetADT* s2) {
    if(!s1 || !s2)
        return 0; 
    
    SortedSetADTptr newSet = mkSSet(s1 -> compare);
    
    ListNodePtr curr1 = s1 -> first;
    ListNodePtr curr2 = s2 -> first;
    
    while(curr1 != NULL){
        
        sset_add(newSet,curr1 -> elem);
        curr1 = curr1 -> next;
    }
    while(curr2 != NULL){
        sset_add(newSet, curr2 -> elem);
        curr2 = curr2 -> next;
    }
    
    return newSet;
} 

// restituisce l'intersezione di due insiemi, NULL se errore
SortedSetADTptr sset_intersection(const SortedSetADT* s1, const SortedSetADT* s2) {
    if(!s1 || !s2)
        return 0;
    
    SortedSetADTptr newset = mkSSet(s1 -> compare);
    
    ListNodePtr curr1 = s1 -> first;
    
    while(curr1 != NULL){
        if(sset_member(s2, curr1 -> elem) == 1)
            sset_add(newset, curr1 -> elem);
        
        curr1 = curr1 -> next;
    }
    return newset;
}

// restituisce il primo elemento 
_Bool sset_min(const SortedSetADT* ss, void**ptr) {
    if (!ss || ss-> size == 0 )
        return 0;
    
    *ptr = ss -> first -> elem;
    
    return 1;
}

// restituisce l'ultimo elemento 
_Bool sset_max(const SortedSetADT* ss, void**ptr) {
    if (!ss || ss -> size == 0 )
        return 0;
    
    *ptr = ss -> last -> elem;
    return 1;
}

// toglie e restituisce il primo elemento 
_Bool sset_extractMin(SortedSetADTptr ss, void**ptr) {
    if (!ss || ss-> size == 0 )
        return 0;
    
    *ptr = ss -> first -> elem;
    sset_remove(ss,*ptr);
    
    return 1;    
}

// toglie e restituisce l'ultimo elemento (0 se lista vuota, -1 se errore, 1 se restituisce elemento)
_Bool sset_extractMax(SortedSetADTptr ss, void**ptr) {
    if (!ss || ss -> size == 0 )
        return 0;
    
    *ptr = ss -> last -> elem;
    sset_remove(ss, *ptr);
    
    return 1 ;      
}
