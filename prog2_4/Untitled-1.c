#include "charQueueADT.h"

typedef struct listNode ListNode, *ListNodePtr;
struct listNode {
   char data;
   ListNodePtr next;
};
typedef struct charQueue Queue, *CharQueueADT;

struct charQueue {
    ListNodePtr front; /* Punta al primo nodo della lista, che contiene l'elemento in testa alla coda, se la coda è vuota vale NULL */
    ListNodePtr rear; /* Punta all'ultimo nodo della lista, che contiene l'elemento in fondo alla coda, se la coda è vuota vale NULL */
    int size;
    /* aggiungere eventuali altre variabili per ottenere una implementazione più efficiente */
};

/* @brief Restituisce una coda vuota, se non trova memoria restituisce NULL */
CharQueueADT mkQueue() {
    
    
    CharQueueADT  nuovo = (CharQueueADT)malloc(sizeof(struct charQueue)) ;
    
    if(nuovo == NULL){
        return NULL;
        
    }
    nuovo ->front=NULL;
    nuovo->rear=NULL;
        
    nuovo->size=0;
    return nuovo;
    
    
}

/* @brief Distrugge la coda, recuperando la memoria */
void dsQueue(CharQueueADT *pq) {
    if(*pq == NULL) {
        return;
    }
    ListNodePtr lista = (*pq) -> front;
    ListNodePtr temp;
    
    while(lista){
        temp=lista;
        lista=lista->next;
        free(temp);
    }
    
    (*pq)->size=0;
    
    free(*pq);
    *pq=NULL;
}

/* @brief Aggiunge un elemento in fondo alla coda */
_Bool enqueue(CharQueueADT q, const char e) {
    if(!q){
        return 0;
    }
    ListNodePtr NewNode=(ListNodePtr)malloc(sizeof(ListNode));
    
    if(!NewNode){
        return 0;
    }
    
    NewNode->data=e;
    NewNode->next=NULL;
    
    if(!q->rear){
        q->front = NewNode;
        q->rear = NewNode;
        
    } else {
        q->rear->next=NewNode;
        q->rear=NewNode;
        
    }
    q->size++;
    return 1;
}
/* @brief Toglie e restituisce l'elemento in testa alla coda */
_Bool dequeue(CharQueueADT q, char* res) {
     if (!q || !q->front ) return 0;
 
ListNodePtr pAppo = q -> front;
 *res = pAppo -> data;
 
 if(q->front==q->rear){
 q->front=NULL;
 q->rear=NULL;
 
 free(pAppo);
 q->size--;
 return 1;
 }
 
 q -> front = pAppo -> next;
 
 q->size--;
 
 free(pAppo);
 
 return 1;

}

/* @brief Controlla se la coda è vuota */
_Bool isEmpty(CharQueueADT q) {
    if(!q || !q->front) return 1;
    
    return 0;
}

/* @brief Restituisce il numero degli elementi presenti nella coda */
int size(CharQueueADT q) {
    if(!q || !q-> front) return 0;
    
    return q->size;
}

/* @brief Restituisce l'elemento nella posizione data (senza toglierlo) */
_Bool peek(CharQueueADT q, int position, char *res) {
    if(!q || position >= q-> size || position <0) return 0;
    
    ListNodePtr lista = q -> front;
    int i=0;
    
    while(i < position){
        lista=lista->next;
        i++;
    }
    
    *res=lista->data;
    return 1;
    
}


