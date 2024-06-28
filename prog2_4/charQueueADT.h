/* Un tipo di dato astratto per le code di char */
typedef struct charQueue *CharQueueADT;

/* @brief Restituisce una coda vuota, se non trova memoria restituisce NULL */
CharQueueADT mkQueue();

/* @brief Distrugge la coda, recuperando la memoria */
void dsQueue(CharQueueADT *pq);

/* @brief Aggiunge un elemento in fondo alla coda, restituisce esito 0/1 */
_Bool enqueue(CharQueueADT q, const char e);

/* @brief Toglie e restituisce l'elemento in testa alla coda, restituisce esito 0/1 */
_Bool dequeue(CharQueueADT q, char*res);

/* @brief Controlla se la coda è vuota */
_Bool isEmpty(CharQueueADT q);

/* @brief Restituisce il numero degli elementi presenti nella coda */
int size(CharQueueADT q);

/* @brief Restituisce l'elemento nella posizione data (a partire dalla testa con indice zero) (senza toglierlo), restituisce esito 0/1 */
_Bool peek(CharQueueADT q, int position, char* res);