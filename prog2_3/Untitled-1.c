#include "contactOpq.h"
#include <stdlib.h>
#include <strings.h>

typedef struct contact Contact, *ContactPtr;

struct contact {
   char* name; 
   char* surname;
   char* mobile;
   char* url;
};

ContactPtr mkContact(char* name, char* surname, char* mobile, char* url) {
    
    if ((name == NULL) || (surname == NULL)) {
        return NULL;
    }
    
    else {
        ContactPtr c1 = (ContactPtr) malloc (sizeof(struct contact));
        c1 -> name = name;
        c1 -> surname = surname;
        c1 -> mobile = mobile;
        c1 -> url = url;
        return c1;
    }
}

void dsContact(ContactPtr* cntptr){
        free (*cntptr);
        *cntptr = NULL;
}

void updateMobile(ContactPtr cnt, char* newMobile){
    cnt -> mobile = newMobile; 
}

void updateUrl(ContactPtr cnt, char* newUrl){
    cnt -> url = newUrl;
}

char* getName(const ContactPtr cnt){
    return cnt -> name;
}

char* getSurname(const ContactPtr cnt){
    return cnt -> surname;
}

char* getMobile(const ContactPtr cnt){
    return cnt -> mobile;
}

char* getUrl(const ContactPtr cnt){
    return cnt -> url;
}

_Bool equalsContact(const ContactPtr cnt1, const ContactPtr cnt2){
    
    int ord1 = strcasecmp(cnt1 -> surname, cnt2 -> surname);
    int ord2 = strcasecmp(cnt1 -> name, cnt2 -> name);
    
    if (ord1 == 0 && ord2 ==0) {
        return 1;
    }
    
    else {
        return 0;
    }
}

int cmpContact(const ContactPtr cnt1, const ContactPtr cnt2){
  int ord1 = strcasecmp(cnt1 -> surname, cnt2 -> surname);
    if (ord1 == 0) {
        int ord2 = strcasecmp(cnt1 -> name, cnt2 -> name);
        if (ord2 == 0)
            return 0;
        
        if (ord2 < 0)
            return -1;
        return 1;
    }
    
    if (ord1 < 0)
        return -1;
    return 1;
}
