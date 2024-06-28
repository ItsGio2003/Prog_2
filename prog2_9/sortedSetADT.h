#ifndef GUARD_SortedSetADT
#define GUARD_SortedSetADT

/** 
    Un tipo di dato per gli insiemi ordinati generici 
*/
typedef struct sortedSetADT SortedSetADT, *SortedSetADTptr;

/**
    NOTA:
    le seguenti funzioni, in base al loro tipo, devono restituire NULL, -1 oppure false (0) in caso di errore
*/

SortedSetADTptr mkSSet(int (*compare)(void*, void*)); // restituisce un insieme vuoto impostando funzione di confronto, NULL se errore
_Bool dsSSet(SortedSetADTptr*); // distrugge l'insieme, recuperando la memoria
_Bool sset_add(SortedSetADTptr, void*); // aggiunge un elemento all'insieme (restituisce false se l'elemento era gia' presente, true altrimenti)
_Bool sset_remove(SortedSetADTptr, void*); // toglie un elemento all'insieme (restituisce false se l'elemento non era presente, true altrimenti)
int sset_member(const SortedSetADT*, void*); // controlla se un elemento appartiene all'insieme
void* sset_search(const SortedSetADT*, void*); // cerca un elemento nell'insieme che si compara uguale a quello dato, NULL se non trovato
int isEmptySSet(const SortedSetADT*); // controlla se l'insieme e' vuoto
int sset_size(const SortedSetADT*); // restituisce il numero di elementi presenti nell'insieme, -1 se NULL
_Bool sset_extract(SortedSetADTptr, void**); // toglie e restituisce un elemento a caso dall'insieme
int sset_equals(const SortedSetADT*, const SortedSetADT*); // controlla se due insiemi sono uguali
int sset_subseteq(const SortedSetADT*, const SortedSetADT*); // controlla se il primo insieme e' incluso nel secondo
int sset_subset(const SortedSetADT*, const SortedSetADT*); // contr. se il primo ins. e' incluso strettamente nel secondo
SortedSetADTptr sset_union(const SortedSetADT*, const SortedSetADT*); // restituisce l'unione di due insiemi
SortedSetADTptr sset_intersection(const SortedSetADT*, const SortedSetADT*); // restituisce l'intersezione di due insiemi
SortedSetADTptr sset_subtraction(const SortedSetADT*, const SortedSetADT*); // restituisce l’insieme ottenuto dal primo togliendo gli elementi del secondo
_Bool sset_min(const SortedSetADT*, void**); // restituisce l'elemento minimo
_Bool sset_max(const SortedSetADT*, void**); // restituisce l'elemento massimo
_Bool sset_extractMin(SortedSetADTptr, void**); // toglie e restituisce l'elemento minimo
_Bool sset_extractMax(SortedSetADTptr, void**); // toglie e restituisce l'elemento massimo
void** sset_toArray(const SortedSetADT*); // crea un array con i contenuti del set (per l'implementazione con ARB in ordine di visita pre-order), NULL se errore

#endif