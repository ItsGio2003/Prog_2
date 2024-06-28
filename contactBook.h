#include "contactOpq.h"

#ifndef GUARD_ContactBookADT
#define GUARD_ContactBookADT

/** 
    Un tipo di dato per una rubrica di contatti
*/
typedef struct contactBookADT ContactBookADT, *ContactBookADTptr;

/**
    NOTA:
    le seguenti funzioni, in base al loro tipo, devono restituire NULL, -1 oppure false (0) in caso di errore
*/

ContactBookADTptr mkCBook(); // restituisce una rubrica vuota, NULL se errore
_Bool dsCBook(ContactBookADTptr*); // distrugge la rubrica, recuperando la memoria, false se errore
int isEmptyCBook(const ContactBookADT*); // controlla se la rubrica e' vuota, -1 se NULL
int cbook_size(const ContactBookADT*); // restituisce il numero di contatti presenti nella rubrica, -1 se NULL
_Bool cbook_add(ContactBookADTptr, ContactPtr); // aggiunge un contatto alla rubrica (restituisce false se l'elemento era gia' presente, true altrimenti)
_Bool cbook_remove(ContactBookADTptr, char* name, char* surname); // toglie un elemento all'insieme (restituisce false se l'elemento non era presente, true altrimenti)
ContactPtr cbook_search(const ContactBookADT*, char* name, char* surname); // restituisce un puntatore al contatto con dato nome e cognome (può essere usata per accedere o modificare il numero e url del contatto), NULL se non presente
ContactBookADTptr cbook_load(FILE* fin); // carica una rubrica da file, NULL se errore
_Bool cbook_dump(const ContactBookADT*, FILE* fout); // salva una rubrica su file, false se errore

#endif