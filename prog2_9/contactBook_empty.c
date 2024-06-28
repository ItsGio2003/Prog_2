#include "contactBook.h"
#include "sortedSetADT.h"
#define MAX_STR 100

/**
 Un tipo di dato per una rubrica di contatti
*/
struct contactBookADT {
    SortedSetADTptr contacts; // Tutto quello che serve è già in questa struttura
};

void stampaContact(void* elem) {
    ContactPtr contact = (ContactPtr)elem;
    printf("%s %s: %s (%s)", getName(contact), getSurname(contact), getMobile(contact), getUrl(contact));
}

int contact_cmp(void* c1, void* c2) {
    return cmpContact((ContactPtr)c1, (ContactPtr)c2);
}

// restituisce una rubrica vuota, NULL se errore
ContactBookADTptr mkCBook() {
    ContactBookADTptr New_Book = malloc(sizeof(ContactBookADT));
    if(!New_Book)
        return NULL;
    
    New_Book -> contacts = mkSSet(contact_cmp);
    if (New_Book -> contacts == NULL) {
        free(New_Book);
        return NULL; // Errore di allocazione del SortedSet
    }
    return New_Book;
}

// distrugge la rubrica, recuperando la memoria, false se errore
_Bool dsCBook(ContactBookADTptr* book) {
    if(!book || *book == NULL )
        return 0;
    
    dsSSet(&(*book)->contacts);
    free(*book);
    *book = NULL;
    return 1;
}


// controlla se la rubrica e' vuota, -1 se NULL
int isEmptyCBook(const ContactBookADT* book) {
    if(!book)
        return -1;
        
    return isEmptySSet(book -> contacts);
}

// restituisce il numero di contatti presenti nella rubrica, -1 se NULL
int cbook_size(const ContactBookADT* book) {
    if(!book)
        return -1;
    
    return sset_size(book -> contacts);
}

// aggiunge un contatto alla rubrica (restituisce false se l'elemento era gia' presente, true altrimenti)
_Bool cbook_add(ContactBookADTptr book, ContactPtr cnt) {
    if(!book)
        return 0;
        
    return sset_add(book->contacts, cnt);
}

// toglie un elemento all'insieme (restituisce false se l'elemento non era presente, true altrimenti)
_Bool cbook_remove(ContactBookADTptr book, char* name, char* surname) {
    if(!book)
        return 0;
    
    ContactPtr temp = mkContact( name, surname, NULL, NULL);
      
    if(sset_member(book -> contacts,temp) == 1){
        sset_remove(book -> contacts, temp);
        return true;
    } 
    
    return false;
}

// restituisce un puntatore al contatto con dato nome e cognome (può essere usata per accedere o modificare il numero e url del contatto), NULL se non presente
ContactPtr cbook_search(const ContactBookADT* book, char* name, char* surname) {
    if(!book)
        return 0;
    ContactPtr temp = mkContact( name, surname, NULL, NULL);
    
    return sset_search(book -> contacts,temp);
}

// carica una rubrica da file, NULL se errore
ContactBookADTptr cbook_load(FILE* fin) {
    if (!fin)
        return NULL;
    
    ContactBookADTptr book = mkCBook();
    
    // char* name = (char*) malloc(MAX_STR * sizeof(char));
    // char* surname = (char*) malloc(MAX_STR * sizeof(char));
    // char* mobile = (char*) malloc(MAX_STR * sizeof(char));
    // char* url = (char*) malloc(MAX_STR * sizeof(char));
    
    char name[MAX_STR];
    char surname[MAX_STR];
    char mobile[MAX_STR];
    char url[MAX_STR];
    
    char* nametmp = NULL;
    char* surnametmp = NULL;
    char* mobiletmp = NULL;
    char* urltmp = NULL;
    
    while (fscanf(fin, "%99[^,],%99[^,],%99[^,],%99[^\n]\n", name, surname, mobile, url) > 1) {
        nametmp = malloc(MAX_STR * (sizeof(char)));
        if(nametmp)
             strncpy(nametmp, name, MAX_STR);
        
        surnametmp = malloc(MAX_STR * (sizeof(char)));
        if(surnametmp)
            strncpy(surnametmp, surname, MAX_STR);
        
        mobiletmp = malloc(MAX_STR * (sizeof(char)));
        if(mobiletmp)
            strncpy(mobiletmp, mobile, MAX_STR);
        
        urltmp = malloc(MAX_STR * (sizeof(char)));
        if(urltmp)
             strncpy(urltmp, url, MAX_STR);
            
            
        cbook_add(book,mkContact(nametmp, surnametmp, mobiletmp, urltmp));
        
        name[0]='\0';
        surname[0]='\0';
        mobile[0]='\0';
        url[0]='\0';

    }
    
    return book ;
}

// salva una rubrica su file, false se errore
_Bool cbook_dump(const ContactBookADT* book, FILE* fout) {
    if(!book || !fout)
        return 0;
        
    void** Array = sset_toArray(book -> contacts);
    int size = cbook_size(book);
        
    for(size_t i = 0; i < size ; i++){
            
        char* name = getName(Array[i]);
        char* surname = getSurname(Array[i]);
        char* url = getUrl(Array[i]);
        char* mobile = getMobile(Array[i]);
            
        fprintf(fout, "%s,%s,%s,%s\n", name, surname, mobile, url);
    }
    
    return true;
}

int main() {
    
    printf("\nContact Book Menu:\n");
    printf("1. Create a new contact book\n");
    printf("2. Load contact book from file\n");
    printf("3. Save contact book to file\n");
    printf("4. Add a contact\n");
    printf("5. Remove a contact\n");
    printf("6. Search for a contact\n");
    printf("7. Display all contacts\n");
    printf("8. Check if contact book is empty\n");
    printf("9. Get the size of the contact book\n");
    printf("10. Destroy the contact book\n");
    printf("0. Exit\n");
    printf("Choose an option: ");
    
    ContactBookADTptr book = NULL;
    int choice;
    char filename[MAX_STR];
    FILE *file;
    char name[MAX_STR], surname[MAX_STR], mobile[MAX_STR], url[MAX_STR];
    ContactPtr contact;

    do {
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                if (book) {
                    printf("Contact book already exists. Destroy the existing one first.\n");
                } else {
                    book = mkCBook();
                    if (book) {
                        printf("New contact book created.\n");
                    } else {
                        printf("Error creating contact book.\n");
                    }
                }
                break;

            case 2:
                printf("Enter filename to load: ");
                scanf("%s", filename);
                file = fopen(filename, "r");
                if (file) {
                    if (book) {
                        dsCBook(&book);
                    }
                    book = cbook_load(file);
                    fclose(file);
                    if (book) {
                        printf("Contact book loaded from file.\n");
                    } else {
                        printf("Error loading contact book from file.\n");
                    }
                } else {
                    printf("Error opening file.\n");
                }
                break;

            case 3:
                printf("Enter filename to save: ");
                scanf("%s", filename);
                file = fopen(filename, "w");
                if (file) {
                    if (cbook_dump(book, file)) {
                        printf("Contact book saved to file.\n");
                    } else {
                        printf("Error saving contact book to file.\n");
                    }
                    fclose(file);
                } else {
                    printf("Error opening file.\n");
                }
                break;

            case 4:
                if (book) {
                    printf("Enter contact name: ");
                    scanf("%s", name);
                    printf("Enter contact surname: ");
                    scanf("%s", surname);
                    printf("Enter contact mobile: ");
                    scanf("%s", mobile);
                    printf("Enter contact URL: ");
                    scanf("%s", url);

                    contact = mkContact(name, surname, mobile, url);
                    if (cbook_add(book, contact)) {
                        printf("Contact added successfully.\n");
                    } else {
                        printf("Contact already exists.\n");
                    }
                } else {
                    printf("No contact book available. Create or load one first.\n");
                }
                break;

            case 5:
                if (book) {
                    printf("Enter contact name: ");
                    scanf("%s", name);
                    printf("Enter contact surname: ");
                    scanf("%s", surname);

                    if (cbook_remove(book, name, surname)) {
                        printf("Contact removed successfully.\n");
                    } else {
                        printf("Contact not found.\n");
                    }
                } else {
                    printf("No contact book available. Create or load one first.\n");
                }
                break;

            case 6:
                if (book) {
                    printf("Enter contact name: ");
                    scanf("%s", name);
                    printf("Enter contact surname: ");
                    scanf("%s", surname);

                    contact = cbook_search(book, name, surname);
                    if (contact) {
                        printf("Contact found: %s %s: %s (%s)\n", getName(contact), getSurname(contact), getMobile(contact), getUrl(contact));
                    } else {
                        printf("Contact not found.\n");
                    }
                } else {
                    printf("No contact book available. Create or load one first.\n");
                }
                break;

            case 7:
                if (book) {
                    if (isEmptyCBook(book)) {
                        printf("The contact book is empty.\n");
                    } else {
                        void** array = sset_toArray(book->contacts);
                        int size = cbook_size(book);
                        for (int i = 0; i < size; i++) {
                            stampaContact(array[i]);
                            printf("\n");
                        }
                        free(array);
                    }
                } else {
                    printf("No contact book available. Create or load one first.\n");
                }
                break;

            case 8:
                if (book) {
                    int is_empty = isEmptyCBook(book);
                    if (is_empty == -1) {
                        printf("Error checking if contact book is empty.\n");
                    } else if (is_empty) {
                        printf("The contact book is empty.\n");
                    } else {
                        printf("The contact book is not empty.\n");
                    }
                } else {
                    printf("No contact book available. Create or load one first.\n");
                }
                break;

            case 9:
                if (book) {
                    int size = cbook_size(book);
                    if (size == -1) {
                        printf("Error getting the size of the contact book.\n");
                    } else {
                        printf("The contact book contains %d contacts.\n", size);
                    }
                } else {
                    printf("No contact book available. Create or load one first.\n");
                }
                break;

            case 10:
                if (book) {
                    if (dsCBook(&book)) {
                        printf("Contact book destroyed.\n");
                    } else {
                        printf("Error destroying contact book.\n");
                    }
                } else {
                    printf("No contact book available to destroy.\n");
                }
                break;

            case 0:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid option. Please try again.\n");
                break;
        }
    } while (choice != 0);

    if (book) {
        dsCBook(&book);
    }

    return 0;
}

