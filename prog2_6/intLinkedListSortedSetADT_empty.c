#include <stdlib.h>
#include <stdbool.h>

#include "intSortedSetADT.h"
#include "intLinkedListSortedSetADT.h"

typedef struct intSortedSet IntSet, *IntSetPtr;

IntSortedSetADT mkSSet() {
    IntSetPtr set = malloc(sizeof(IntSet));
    if(set == NULL)
        return NULL;
        
    set -> first = NULL;
    set -> last = NULL;
    set -> size = 0;
    
    return set;
}

_Bool dsSSet(IntSortedSetADT *ssptr) {
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

_Bool sset_add(IntSortedSetADT ss, const int elem) {
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
        
        while (curr != NULL && curr -> elem < elem) {
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

_Bool sset_remove(const IntSortedSetADT ss, const int elem) {
        if (ss == NULL || ss -> size == 0)
            return false;
    
        if (ss -> size == 1) {
            if (ss -> first -> elem == elem) {
                free(ss -> first);
    
                ss -> first = NULL;
                ss -> last = NULL;
                ss -> size = 0;
    
                return true;
            }
            
            return false;
        }
    
        if (ss -> first -> elem > elem || ss -> last -> elem < elem)
            return false;
        
        if (ss -> first -> elem == elem) {
            ListNodePtr tmp = ss -> first;
            ss -> first = ss -> first -> next;
    
            free(tmp);
        
        } else {
            ListNodePtr prev = NULL;
            ListNodePtr curr = ss -> first;
            while (curr != NULL && curr -> elem != elem) {
                prev = curr;
                curr = curr -> next;
            
                // se non esiste l'elemento
                if (curr -> elem > elem)
                    return false;
            }
    
            prev -> next = curr -> next;
            free(curr);
            if (prev -> next == NULL)
                ss -> last = prev;
        }
    
        ss -> size--;
        return true;
    
    /*if(!ss || ss -> size == 0)
        return 0;
    
    if(ss->first->elem == elem){ 
        ListNodePtr to_remove = ss->first;
        ss->first = ss->first->next;
        free(to_remove);
    
        ss->size--;
        return 1;
    }
    
    
    int found = 0;
    for(ListNodePtr curr = ss -> first; curr != NULL; curr = curr->next){
        ListNodePtr prev = curr;
        curr = curr -> next;
        
        if(prev -> elem == elem && curr == ss -> last){
            found = 1;
            
            ListNodePtr to_remove = curr;
            prev = ss -> last;
            free(to_remove);
            ss->size--;
            break;
        }
        
        if(curr->elem == elem){
            found = 1;
            // fprintf(stderr, "%d %p\n", curr -> data, curr -> next);
            
            ListNodePtr to_remove = curr;
            prev -> next = curr -> next;
            free(to_remove);

            ss->size--;
            break;
        }
    }
            
    return found;*/
    
}

_Bool sset_member(const IntSortedSetADT ss, const int elem) {
    if(!ss || ss-> size == 0)
        return 0;
    
    if (ss -> first -> elem == elem || ss -> last -> elem == elem) 
        return 1;

    int found = 0;
    ListNodePtr curr = ss -> first;
    while(curr != NULL && !found){
        if(curr->elem == elem)
            found = 1;
        curr = curr -> next;
    }
    return found;
}

_Bool isEmptySSet(const IntSortedSetADT ss) {
    if(!ss)
        return 0;
    
    return (ss -> size == 0);
}

int sset_size(const IntSortedSetADT ss) {
    if(!ss)
        return -1;
        
    return ss -> size;
}

_Bool sset_extract(IntSortedSetADT ss, int *ptr) {
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

_Bool sset_equals(const IntSortedSetADT s1, const IntSortedSetADT s2) {
    if (!s1 && !s2)
        return 1;
    if (!s1 || !s2) 
        return 0;
    if(s1->size == 0 && s2->size == 0)
        return 1;
    
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

_Bool sset_subseteq(const IntSortedSetADT s1, const IntSortedSetADT s2) {
    if(!s2)
        return !s1;
    
    if (!s1)
        return 0;
    
    if(s1->size == 0 && s2->size == 0)
        return 1;
    
    if (s1->size > s2->size)
        return 0;
        
    ListNodePtr curr1 = s1 -> first;
    while (curr1 != NULL){
        if(sset_member(s2,curr1 -> elem) == 0)
            return 0;
        
        curr1 = curr1 -> next;
    }
    return 1;
}

_Bool sset_subset(const IntSortedSetADT s1, const IntSortedSetADT s2) {
    if (!s2)
        return !s1;
    
    if (!s1)
        return 0;
    
    if (s1->size == 0 && s2->size == 0)
        return 1;
    
    if (s1->size >= s2->size)
        return 0;
    
    ListNodePtr curr1 = s1 -> first;
    while (curr1 != NULL){
        if (curr1 -> next)
            printf("data: %d (next: %d)\n", curr1 -> elem, curr1 -> next -> elem);
        else
            printf("data: %d (next: NULL)\n", curr1 -> elem);
            
        if(sset_member(s2,curr1 -> elem) == 0)
            return 0;
        
        curr1 = curr1 -> next;
    }
    return 1;
}

IntSortedSetADT sset_union(const IntSortedSetADT s1, const IntSortedSetADT s2) {
    if(!s1 || !s2)
        return 0; 
    
    IntSortedSetADT newSet = mkSSet();
    
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

IntSortedSetADT sset_intersection(const IntSortedSetADT s1, const IntSortedSetADT s2) {
    if(!s1 || !s2)
        return 0;
    
    IntSortedSetADT newset = mkSSet();
    
    ListNodePtr curr1 = s1 -> first;
    
    while(curr1 != NULL){
        if(sset_member(s2, curr1 -> elem) == 1)
            sset_add(newset, curr1 -> elem);
        
        curr1 = curr1 -> next;
    }
    return newset;
}

IntSortedSetADT sset_subtraction(const IntSortedSetADT s1, const IntSortedSetADT s2) {
    if(!s1 || !s2)
        return 0;
        
    IntSortedSetADT newset = mkSSet();
    
    ListNodePtr curr1 = s1 -> first;
    
    while(curr1 != NULL){
        if(sset_member(s2, curr1 -> elem) == 0)
            sset_add(newset, curr1 -> elem);
        
        curr1 = curr1 -> next;
    }
    return newset;
}

_Bool sset_min(const IntSortedSetADT ss, int *ptr) {
    if (!ss || ss-> size == 0 )
        return 0;
    
    *ptr = ss -> first -> elem;
    
    return 1;
}

_Bool sset_max(const IntSortedSetADT ss, int *ptr) {
    if (!ss || ss -> size == 0 )
        return 0;
    
    
    
    *ptr = ss -> last -> elem;
    return 1;
}

_Bool sset_extractMin(IntSortedSetADT ss, int *ptr) {
    if (!ss || ss-> size == 0 )
        return 0;
    
    *ptr = ss -> first -> elem;
    sset_remove(ss,*ptr);
    
    return 1;
}

_Bool sset_extractMax(IntSortedSetADT ss, int *ptr) {
    if (!ss || ss -> size == 0 )
        return 0;
    
    *ptr = ss -> last -> elem;
    sset_remove(ss, *ptr);
    
    return 1 ;
}
