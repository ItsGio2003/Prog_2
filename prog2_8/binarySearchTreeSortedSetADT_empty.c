#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "sortedSetADT.h"
#include "binarySearchTreeSortedSetADT.h"

void stampaSet_rec(TreeNodePtr cur, void (*stampaelem)(void*)) {
    #ifdef DEBUG
    printf("( ");
    #endif
    if (cur) {
        stampaSet_rec(cur->left, stampaelem);
        (*stampaelem)(cur->elem);
        stampaSet_rec(cur->right, stampaelem);
    }
    #ifdef DEBUG
    printf(") ");
    #endif
}

// stampa i contenuti dell'insieme, data la funzione di stampa di un elemento
void stampaSet(SortedSetADTptr ss, void (*stampaelem)(void*)) {
    if(!ss) printf("Insieme non esiste\n");
    else if(sset_size(ss) == 0) printf("Insieme vuoto\n");
    else {
        printf("Insieme: (size %d) ",ss->size);
        stampaSet_rec(ss->root, stampaelem);
        printf("\n");
    }
}

// restituisce un insieme vuoto impostando funzione di confronto, NULL se errore
SortedSetADTptr mkSSet(int (*compare)(void*, void*)) {
    SortedSetADTptr New_Albero = malloc(sizeof(SortedSetADT));
    if (!New_Albero)
        return 0;
    
    New_Albero -> root = NULL;
    New_Albero -> size = 0;
    New_Albero -> compare = compare;

    return New_Albero;
}


void dsSSet_node(TreeNodePtr root){
    if(root == NULL)
        return ;

    dsSSet_node(root ->left);
    dsSSet_node(root ->right);
    
    free(root);
}
    
// distrugge l'insieme, recuperando la memoria
_Bool dsSSet(SortedSetADTptr* ssptr) {
    if(!ssptr)
        return 0;
    
    dsSSet_node((*ssptr) ->root);
    free(*ssptr);
    (*ssptr) = NULL;
    
    return 1;
}

// aggiunge un elemento all'insieme 
_Bool sset_add_rec(SortedSetADTptr ss,TreeNodePtr* root, void* elem){
    if(*root == NULL){
        (*root) = malloc(sizeof(SortedSetADT));
        if (*root == NULL) {
            return 0; // Allocation failed
        }
        // Initialize the new node
        (*root) -> elem = elem;
        (*root) -> left = NULL;
        (*root) ->  right = NULL;
        ss -> size++;
        return 1;
    } 
    if(ss -> compare((*root) -> elem, elem) > 0 ) {
        return sset_add_rec(ss, &((*root) -> left) ,elem);
    } else if(ss -> compare((*root) -> elem, elem) < 0){
        return sset_add_rec(ss , &((*root) -> right), elem);
    } 
    return 0;
}
// aggiunge un elemento all'insieme 
_Bool sset_add(SortedSetADTptr ss, void* elem) {
    if(!ss)
        return NULL;

    if (ss->root == NULL) {
        // Allocate memory for the new node
        ss->root = malloc(sizeof(SortedSetADT));
        if (ss->root == NULL) {
            return 0; // Allocation failed
        }
        // Initialize the new node
        ss -> root -> elem = elem;
        ss -> root -> left = NULL;
        ss -> root -> right = NULL;
        ss -> size++;
        return 1; // Indicate success
    }
     return sset_add_rec(ss,&ss->root, elem);
}


void sset_extractMin_rec(TreeNodePtr* cur, void**ptr, int (*compare)(void*, void*));
void sset_extractMax_rec(TreeNodePtr* cur, void**ptr, int (*compare)(void*, void*));

// funzione ausiliaria che toglie un elemento da un sottoalbero
_Bool sset_remove_rec(TreeNodePtr* cur, void* elem, int (*compare)(void*, void*)) {
    if (*cur == NULL) return false;
    int r = compare(elem, (*cur)->elem);
    if (r < 0) return sset_remove_rec(&((*cur)->left), elem, compare);
    if (r > 0) return sset_remove_rec(&((*cur)->right), elem, compare);
    void* ptr;
    if ((*cur)->left == NULL) {
        sset_extractMin_rec(cur, &ptr, compare);
    } else if ((*cur)->right == NULL) {
        sset_extractMax_rec(cur, &ptr, compare);
    } else {
        sset_extractMax_rec(&((*cur)->left), &ptr, compare);
        (*cur)->elem = ptr;
    }
    return true;
}

// toglie un elemento all'insieme
_Bool sset_remove(SortedSetADTptr ss, void* elem) {
    if (ss && sset_remove_rec(&(ss->root), elem, ss->compare)) {
        ss->size--;
        return true;
    }
    return false;
}

/*int sset_member_rec(const SortedSetADT* ss, TreeNodePtr root, void* elem){
    if(ss == NULL)
        return 0;
    
    if(root == NULL)
        return 0;
    
    if(ss -> compare(root -> elem , elem) == 0)
        return 1;

    if( ss -> compare(root -> elem , elem) < 0){
        return sset_member_rec(ss ,root ->right, elem);
    } else if(ss -> compare(root -> elem , elem) > 0){
        return sset_member_rec( ss ,root -> left, elem);
    }
    
    return 0;
}*/

// controlla se un elemento appartiene all'insieme
int sset_member(const SortedSetADT* ss, void* elem) {
    /*if(ss -> root == NULL || ss -> compare(ss -> root -> elem , elem) == 0)
        return 1;

    return sset_member_rec(ss , ss -> root , elem);*/
    
    if(!ss || !ss -> root )
        return -1;
        
    TreeNodePtr append = ss -> root;
    
    while(append != NULL){
        
        if((ss->compare)(elem,append->elem) == 0)
            return 1;
            
        if((ss->compare)(elem,append->elem) < 0){
            append = append -> left;
            if(!append)
                return 0;
        }
        
        if((ss->compare)(elem,append->elem) > 0){
            append = append -> right;
            if(!append)
                return 0;
        }
        
    }
    
    return 0;
}

// cerca un elemento nell'insieme che si compara uguale a quello dato, NULL se non trovato
TreeNodePtr sset_search_rec(const SortedSetADT* ss ,TreeNodePtr root, void* elem){
    if(root == NULL)
        return 0;

    if(ss -> compare(root -> elem , elem) == 0)
        return root -> elem;

    if( ss -> compare(root -> elem , elem) < 0){
        return sset_search_rec(ss ,root ->right, elem);
    } else if(ss -> compare(root -> elem , elem) > 0){
        return sset_search_rec(ss ,root -> left, elem);
    }
    
    return 0;
}

// cerca un elemento nell'insieme che si compara uguale a quello dato, NULL se non trovato
void* sset_search(const SortedSetADT* ss, void* elem) {
    
    if(ss -> root == NULL || ss -> compare(ss -> root -> elem , elem) == 0)
        return ss -> root -> elem;
    
    return sset_search_rec(ss , ss -> root , elem);
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
    if(!ss || ss -> size == 0)
        return 0;
    
    int position = rand() % ss -> size;
    
    void** nodes = sset_toArray(ss);
    *ptr = nodes[position];
    
    return sset_remove(ss, *ptr);
} 

// controlla se due insiemi sono uguali
_Bool sset_equals_rec(TreeNodePtr root, const SortedSetADT* s2) {
    if (!root)
        return 1;
    
    if (sset_member(s2, root->elem) == 0)  // Check if root->elem is not in s2
        return 0;

    return sset_equals_rec(root->left, s2) && sset_equals_rec(root->right, s2);
}

// Check if two sets are equal
int sset_equals(const SortedSetADT* s1, const SortedSetADT* s2) { 
    if (!s1 && !s2)
        return 1;  // Both sets are NULL, they are considered equal
    if (!s1 || !s2) 
        return -1;  // One set is NULL, the other is not
    
    if (s1->size == 0 && s2->size == 0)
        return 1;  // Both sets are empty, they are equal
        
    if (s1->size == 0 && s2->size > 0)
        return 0;  // s1 is empty but s2 is not, they are not equal
    
    if (s1->size != s2->size)
        return 0;  // Different sizes, they are not equal
    
    return sset_equals_rec(s1->root, s2);  // Recursively check if all elements of s1 are in s2
}

// controlla se il primo insieme e' incluso nel secondo
int sset_subseteq(const SortedSetADT* s1, const SortedSetADT* s2) {
    if (!s1 || !s2)
        return -1;

    if (s1 -> size == 0)
        return 1; // Empty set is always a subset
    
    if (s2 -> size == 0)
        return 0; // Non-empty set cannot be a subset of an empty set
    
    if (s1 -> size > s2 -> size)
        return 0;
   
    return sset_equals_rec(s1 -> root, s2);
}

// controlla se il primo insieme e' incluso strettamente nel secondo
int sset_subset(const SortedSetADT* s1, const SortedSetADT* s2) {
    if (!s1 || !s2)
        return -1;

    if (s1 -> size == 0)
        return 1; // Empty set is always a subset
    
    if (s2 -> size == 0)
        return 0; // Non-empty set cannot be a subset of an empty set
    
    if (s1 -> size >= s2 -> size)
        return 0;
   
    return sset_equals_rec(s1 -> root, s2);
} 

// restituisce la sottrazione primo insieme meno il secondo, NULL se errore
SortedSetADTptr sset_subtraction(const SortedSetADT* s1, const SortedSetADT* s2) {
     if(!s1 || !s2)
        return 0; 
    
    SortedSetADTptr new_set = mkSSet(s1 -> compare);
    
    void **Array1 = sset_toArray(s1);
    
    void **Array2 = sset_toArray(s2);
     
    for(size_t i = 0; i < s1->size; i++) {
        sset_add(new_set,Array1[i]);
    
        for(size_t j = 0; j < s2 -> size; j++)
            if (Array1[i] == Array2[j])
                sset_remove(new_set, Array1[i]);
        
    }
    return new_set; 
} 


// restituisce l'unione di due insiemi, NULL se errore
SortedSetADTptr sset_union(const SortedSetADT* s1, const SortedSetADT* s2) {
    if(!s1 || !s2)
        return 0; 
    
    SortedSetADTptr new_set = mkSSet(s1 -> compare);
    
    void **Array1 = sset_toArray(s1);
     
    for(size_t i = 0; i < s1->size; i++)
        sset_add(new_set, Array1[i]);
     
    void **Array2 = sset_toArray(s2);
     
    for(size_t j = 0; j < s2 -> size; j++)
        sset_add(new_set, Array2[j]);
     
    return new_set;
}

// restituisce l'intersezione di due insiemi, NULL se errore
SortedSetADTptr sset_intersection(const SortedSetADT* s1, const SortedSetADT* s2) {
    if(!s1 || !s2)
        return 0; 
    
    SortedSetADTptr new_set = mkSSet(s1 -> compare);
    
    void **Array1 = sset_toArray(s1);
    
    void **Array2 = sset_toArray(s2);
     
    for(size_t i = 0; i < s1->size; i++) 
        for(size_t j = 0; j < s2 -> size; j++)
            if (Array1[i] == Array2[j])
                sset_add(new_set, Array1[i]);
        
     
    return new_set;
}

// restituisce il primo elemento 
_Bool sset_min(const SortedSetADT* ss, void**ptr) {
    if(!ss || !ss -> root )
        return 0;
        
    TreeNodePtr leftnode = ss -> root;
    
    while (leftnode -> left){
        leftnode = leftnode -> left;
        
    }
    
    *ptr = leftnode -> elem;
    
    return ptr;
}

// restituisce l'ultimo elemento 
_Bool sset_max(const SortedSetADT* ss, void**ptr) {
    if(!ss || !ss -> root )
        return 0;
        
    TreeNodePtr rightnode = ss -> root;
    
    while (rightnode -> right){
        rightnode = rightnode -> right;
        
    }
    
    *ptr = rightnode -> elem;
    
    return ptr;
}

void sset_extractMin_rec(TreeNodePtr* cur, void**ptr, int (*compare)(void*, void*)) {
    if ((*cur)->left) sset_extractMin_rec(&((*cur)->left), ptr, compare);
    else {
        (*ptr) = (*cur)->elem;
        if ((*cur)->right) {
            TreeNodePtr tmp = *cur;
            (*cur) = (*cur)->right;
            free(tmp);
        } else {
            free(*cur);
            *cur = NULL;
        }
    }
}

// toglie e restituisce il primo elemento 
_Bool sset_extractMin(SortedSetADTptr ss, void**ptr) {
    if(!ss || !ss -> root )
        return 0;
        
    TreeNodePtr* removemin = &(ss -> root);
    
    sset_extractMin_rec(removemin, ptr, ss -> compare);
    
    return 1;
}

void sset_extractMax_rec(TreeNodePtr* cur, void**ptr, int (*compare)(void*, void*)) {
    if ((*cur)->right) sset_extractMax_rec(&((*cur)->right), ptr, compare);
    else {
        (*ptr) = (*cur)->elem;
        if ((*cur)->left) {
            TreeNodePtr tmp = *cur;
            (*cur) = (*cur)->left;
            free(tmp);
        } else {
            free(*cur);
            *cur = NULL;
        }
    }
}

// toglie e restituisce l'ultimo elemento (0 se lista vuota, -1 se errore, 1 se restituisce elemento)
_Bool sset_extractMax(SortedSetADTptr ss, void**ptr) {
    if(!ss || !ss -> root )
        return 0;
        
    TreeNodePtr* removemax = &(ss -> root);
    
    sset_extractMax_rec(removemax, ptr, ss -> compare);
    
    return 1;
}    


void sset_toArray_rec(TreeNodePtr root, void** array, int* i) {
    if (root == NULL)
        return;
    
    array[*i] = root -> elem;
    *i = *i + 1;
    
    sset_toArray_rec(root -> left, array, i);
    sset_toArray_rec(root -> right, array, i);
}

// crea un array con i contenuti del set in ordine di visita pre-order, NULL se errore
void** sset_toArray(const SortedSetADT* ss) {
    if (!ss)
        return NULL;

    void** array = malloc(sizeof(void*) * ss -> size);
    int i = 0;
    
    sset_toArray_rec(ss -> root, array, &i);

    return array;
}
