#ifndef GUARD_IntSortedSetADT
#define GUARD_IntSortedSetADT

/** Un tipo di dato per gli insiemi ordinati di int
*/
typedef struct intSortedSet *IntSortedSetADT;

/*
 NOTA:
 le seguenti funzioni, in base al loro tipo, devono restituire 
 NULL, -1 oppure false (0) se ricevono uno o più puntatori NULL come parametri di tipo IntSortedSetADT
*/

IntSortedSetADT mkSSet(); // restituisce un insieme vuoto
_Bool dsSSet(IntSortedSetADT*); // distrugge l'insieme, recuperando la memoria
_Bool sset_add(IntSortedSetADT, const int); // aggiunge un elemento all'insieme (restituisce 0 se l'elemento era gia' presente, 1 altrimenti)
_Bool sset_remove(IntSortedSetADT, const int); // toglie un elemento all'insieme (restituisce 0 se l'elemento non era presente, 1 altrimenti)
_Bool sset_member(const IntSortedSetADT, const int); // controlla se un elemento appartiene all'insieme
_Bool isEmptySSet(const IntSortedSetADT); // controlla se l'insieme e' vuoto
int sset_size(const IntSortedSetADT); // restituisce il numero di elementi presenti nell'insieme, -1 se NULL
_Bool sset_extract(IntSortedSetADT, int *); // toglie e restituisce un elemento a caso dall'insieme
_Bool sset_equals(const IntSortedSetADT, const IntSortedSetADT); // controlla se due insiemi sono uguali
_Bool sset_subseteq(const IntSortedSetADT, const IntSortedSetADT); // controlla se il primo insieme e' incluso nel secondo
_Bool sset_subset(const IntSortedSetADT, const IntSortedSetADT); // contr. se il primo ins. e' incluso strettamente nel secondo
IntSortedSetADT sset_union(const IntSortedSetADT, const IntSortedSetADT); // restituisce l'unione di due insiemi
IntSortedSetADT sset_intersection(const IntSortedSetADT, const IntSortedSetADT); // restituisce l'intersezione di due insiemi
IntSortedSetADT sset_subtraction(const IntSortedSetADT, const IntSortedSetADT); // restituisce l’insieme ottenuto dal primo togliendo gli elementi del secondo
_Bool sset_min(const IntSortedSetADT, int *); // restituisce l'elemento minimo
_Bool sset_max(const IntSortedSetADT, int *); // restituisce l'elemento massimo
_Bool sset_extractMin(IntSortedSetADT, int *); // toglie e restituisce l'elemento minimo
_Bool sset_extractMax(IntSortedSetADT, int *); // toglie e restituisce l'elemento massimo

#endif