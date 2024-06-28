#ifndef GUARD_IntSetADT
#define GUARD_IntSetADT

/** Un tipo di dato per gli insiemi di int
*/
typedef struct intSet *IntSetADT;

/*
    NOTA:
    le seguenti funzioni, in base al loro tipo, devono restituire 
    NULL, -1 oppure false (0) se ricevono uno o più puntatori NULL come parametri di tipo IntSetADT
*/

IntSetADT mkSet(); // restituisce un insieme vuoto
_Bool dsSet(IntSetADT*); // distrugge l'insieme (inclusi i suoi elementi), recuperando la memoria
_Bool set_add(IntSetADT, const int); // aggiunge un elemento all'insieme (restituisce 0 se l'elemento era gia' presente, 1 altrimenti)
_Bool set_remove(IntSetADT, const int); // toglie un elemento all'insieme (restituisce 0 se l'elemento non era presente, 1 altrimenti)
_Bool set_member(const IntSetADT, const int); // controlla se un elemento appartiene all'insieme
_Bool isEmptySet(const IntSetADT); // controlla se l'insieme e' vuoto
int set_size(const IntSetADT); // restituisce il numero di elementi presenti nell'insieme, -1 se NULL
_Bool set_extract(IntSetADT, int *); // toglie e restituisce un elemento a caso dall'insieme
_Bool set_equals(const IntSetADT, const IntSetADT); // controlla se due insiemi sono uguali
_Bool subseteq(const IntSetADT, const IntSetADT); // controlla se il primo insieme e' incluso nel secondo
_Bool subset(const IntSetADT, const IntSetADT); // contr. se il primo ins. e' incluso strettamente nel secondo
IntSetADT set_union(const IntSetADT, const IntSetADT); // restituisce l'unione di due insiemi
IntSetADT set_intersection(const IntSetADT, const IntSetADT); // restituisce l'intersezione di due insiemi
IntSetADT set_subtraction(const IntSetADT, const IntSetADT); // restituisce l’insieme ottenuto dal primo togliendo gli elementi del secondo

#endif