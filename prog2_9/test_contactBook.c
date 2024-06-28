#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include "contactBook.h"


int main(int argc, char *argv[]) {
    
    ContactBookADTptr book;
    int check;
    ContactPtr ptr;

    srand(2024);

    puts("BEGIN TEST of ContactBookADT");

    printf("\nCreating contact book\n");
    book = mkCBook();
    printf("Contact book size: %d\n", cbook_size(book));
    printf("/*contact book start*/\n");
    cbook_dump(book,stdout);
    printf("/*contact book end*/\n");

    check = cbook_add(book, mkContact("Primo", "Contatto", "123456", "primo@contatto.it"));
    printf("\nAdding contact, check = %d\n",check);
    printf("Contact book size: %d\n", cbook_size(book));
    printf("/*contact book start*/\n");
    cbook_dump(book,stdout);
    printf("/*contact book end*/\n");

    check = cbook_add(book, mkContact("Secondo", "Contatto", "42", ""));
    printf("\nAdding contact, check = %d\n",check);
    printf("Contact book size: %d\n", cbook_size(book));
    printf("/*contact book start*/\n");
    cbook_dump(book,stdout);
    printf("/*contact book end*/\n");

    ptr = cbook_search(book, "Terzo", "Contatto");
    printf("\nSearching non-existing contact, check = %p\n", ptr);

    ptr = cbook_search(book, "Primo", "Contatto");
    printf("\nSearching existing contact, check = %p\n", ptr);
    printf("mobile: %s, url: %s\n", getMobile(ptr), getUrl(ptr));
    printf("\nModifying existing contact\n");
    updateMobile(ptr, "000000");
    updateUrl(ptr, "---");
    printf("Contact book size: %d\n", cbook_size(book));
    printf("/*contact book start*/\n");
    cbook_dump(book,stdout);
    printf("/*contact book end*/\n");

    FILE* file;
    file = fopen("temp.csv", "w");
    check = cbook_dump(book, file);
    printf("\nWriting to file, check = %d\n", check);
    fclose(file);
    printf("\nDestroying contact book\n");
    dsCBook(&book);
    printf("Contact book size: %d\n", cbook_size(book));
    printf("/*contact book start*/\n");
    cbook_dump(book,stdout);
    printf("/*contact book end*/\n");
    file = fopen("temp.csv", "r");
    book = cbook_load(file);
    printf("\nReading from file, check = %p\n", book);
    fclose(file);
    printf("Contact book size: %d\n", cbook_size(book));
    printf("/*contact book start*/\n");
    cbook_dump(book,stdout);
    printf("/*contact book end*/\n");

    check = cbook_remove(book, "Terzo", "Contatto");
    printf("\nRemoving non-existing contact, check = %d\n", check);
    printf("Contact book size: %d\n", cbook_size(book));
    printf("/*contact book start*/\n");
    cbook_dump(book,stdout);
    printf("/*contact book end*/\n");

    check = cbook_remove(book, "Secondo", "Contatto");
    printf("\nRemoving existing contact, check = %d\n", check);
    printf("Contact book size: %d\n", cbook_size(book));
    printf("/*contact book start*/\n");
    cbook_dump(book,stdout);
    printf("/*contact book end*/\n");

    printf("\nDestroying contact book\n");
    dsCBook(&book);
    return 0;
}