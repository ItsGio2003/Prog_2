#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "intSetADT.h"
#include "intLinkedListSet.h"

IntSetADT mkSetv(int count, ...) {
    IntSetADT set = mkSet();

    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; ++i) {
        int num = va_arg(args, int);
        set_add(set,num);        
    }
    va_end(args);
    return set;
}

char *toString(IntSetADT set) {
    char *sout = malloc(100*sizeof(char));

    ListNodePtr nptr = set->front;
    sprintf(sout, "{");
    while (nptr) {
        if (nptr == set->front)
            sprintf(sout+strlen(sout), "%d", nptr->data);
        else
            sprintf(sout+strlen(sout), ",%d", nptr->data);
        nptr = nptr->next;
    }

    sprintf(sout+strlen(sout), "}");

    return sout;
}

int check_mkSet() {
    int passed = 1;
    printf("mkSet()\n");    
    IntSetADT sptr = mkSet();
    if (!sptr) {
        printf("FAILED");
        printf("EXPECTED: not %d\n", 0);   
    } else
        printf("OK\n");
    printf("RESULT:%p\n\n", sptr);  
    return passed;
}

int check_dsSet1() {
    int passed = 1;
    _Bool rv;
    IntSetADT sptr = mkSet();
    printf("dsSet({})\n");    
    rv = dsSet(&sptr);
    if (!rv || sptr) {
        printf("FAILED\n");
        printf("EXPECTED: NOT %d AND PTR %p\n", 0, NULL); 
        passed=0;  
    } else {
        printf("OK\n");
    }
    printf("RESULT:%d AND PTR %p\n\n", rv, sptr);  
    return passed;
}

int check_dsSet2() {
    int passed=1;
    _Bool rv;
    printf("dsSet(NULL)\n");    
    rv = dsSet(NULL);
    if (rv) {
        printf("FAILED\n");
        printf("EXPECTED: %d\n", 0);
        passed=0;   
    } else {
        printf("OK\n");
    }
    printf("RESULT:%d\n\n", rv);

    return passed;  
}

int check_set_add1() {
    int passed=1;
    _Bool rv;
    printf("set_add(NULL,5)\n");    
    rv = set_add(NULL,5);
    if (rv) {
        printf("FAILED\n");
        printf("EXPECTED: %d\n", 0);
        passed=0;
    } else {
        printf("OK\n");
    }
    printf("RESULT: %d\n", rv);  

    return passed;
}

int check_set_add2() {
    int passed=1;
    _Bool rv;
    IntSetADT sptr = mkSet();
    printf("set_add({},5)\n");    
    rv = set_add(sptr,5);
    if (!rv || sptr->size!=1) {
        printf("FAILED\n");
        printf("EXPECTED: NOT %d WITH SIZE %d\n", 0, 1);
        passed=0;   
    } else {
        printf("OK\n");
    }
    printf("RESULT:%d WITH SIZE %d\n", rv, sptr->size);  
    dsSet(&sptr);

    return passed;
}

int check_set_add3() {
    int passed=1;
    _Bool rv;
    IntSetADT sptr = mkSet();
    rv = set_add(sptr,5);
    printf("set_add({5},7)\n");    
    rv = set_add(sptr,7);
    if (!rv || sptr->size!=2) {
        printf("FAILED\n");
        printf("EXPECTED: NOT %d WITH SIZE %d\n", 0, 2);   
        passed=0;
    } else {
        printf("OK\n");
    }
    printf("RESULT:%d WITH SIZE %d\n", rv, sptr->size);  
    dsSet(&sptr);

    return passed;
}

int check_set_add4() {
    int passed=1;
    _Bool rv;
    IntSetADT sptr = mkSet();  
    rv = set_add(sptr,5);
    rv = set_add(sptr,7);
    printf("set_add({5,7},5)\n");    
    rv = set_add(sptr,5);
    if (rv || sptr->size!=2) {
        printf("FAILED\n");
        printf("EXPECTED: %d WITH SIZE %d\n", 0, 2);
        passed=0;   
    } else {
        printf("OK\n");
    }
    printf("RESULT:%d WITH SIZE %d\n", rv, sptr->size);  
    dsSet(&sptr);

    return passed;
}

int check_set_remove1(){
    int passed=1;
    _Bool rv;

    printf("set_remove(NULL,3)\n");    
    rv = set_remove(NULL, 3);
    if (rv) {
        printf("FAILED\n");
        printf("EXPECTED: %d\n", 0);
        passed=0;
    } else {
        printf("OK\n");
    }
    printf("RESULT: %d\n", rv);

    return passed;
}

int check_set_remove2(){
    int passed=1;
    _Bool rv;

    printf("set_remove({},3)\n");    
    IntSetADT sptr = mkSet();
    rv = set_remove(sptr, 3);
    if (rv || sptr->size!=0) {
        printf("FAILED\n");
        printf("EXPECTED: %d WITH SIZE %d\n", 0, 0);
        passed=0;
    } else {
        printf("OK\n");
    }
    printf("RESULT:%d WITH SIZE %d\n", rv, sptr->size);  
    dsSet(&sptr);

    return passed;
}

int check_set_remove3(){
    int passed=1;
    _Bool rv;

    printf("set_remove({5,7},3)\n");    
    IntSetADT sptr = mkSetv(2,5,7);
    rv = set_remove(sptr, 3);
    if (rv || sptr->size!=2) {
        printf("FAILED\n");
        printf("EXPECTED: %d WITH SIZE %d\n", 0, 2);
        passed=0;   
    } else {
        printf("OK\n");
    }
    printf("RESULT:%d WITH SIZE %d\n", rv, sptr->size);  
    dsSet(&sptr);

    return passed;
}

int check_set_remove4(){
    int passed=1;
    _Bool rv;

    printf("set_remove({5,7},5)\n");    
    IntSetADT sptr = mkSetv(2,5,7);
    rv = set_remove(sptr, 5);
    if (!rv || sptr->size!=1) {
        printf("FAILED\n");
        printf("EXPECTED: NOT %d WITH SIZE %d\n", 0, 1);   
        passed=0;
    } else {
        printf("OK\n");
    }
    printf("RESULT:%d WITH SIZE %d\n", rv, sptr->size);  
    dsSet(&sptr);

    return passed;
}

int check_set_remove5(){
    int passed=1;
    _Bool rv;

    printf("set_remove({7},7)\n");    
    IntSetADT sptr = mkSetv(1,7);
    rv = set_remove(sptr, 7);
    if (!rv || sptr->size!=0) {
        printf("FAILED\n");
        printf("EXPECTED: NOT %d WITH SIZE %d\n", 0, 0);
        passed=0;   
    } else {
        printf("OK\n");
    }
    printf("RESULT:%d WITH SIZE %d\n", rv, sptr->size);  
    dsSet(&sptr);

    return passed;
}
int check_set_member1(){
    int passed=1;
    _Bool rv;

    printf("set_member(NULL,3)\n");    
    rv = set_member(NULL, 3);
    if (rv) {
        printf("FAILED\n");
        printf("EXPECTED: %d\n", 0);   
        passed=0;
    } else {
        printf("OK\n");
    }
    printf("RESULT:%d\n", rv);

    return passed;  
}

int check_set_member2(){
    int passed=1;
    _Bool rv;

    printf("set_member({5,7},3)\n");    
    IntSetADT sptr = mkSetv(2,5,7);
    rv = set_member(sptr, 3);
    if (rv) {
        printf("FAILED\n");
        printf("EXPECTED: %d\n", 0);   
        passed=0;
    } else {
        printf("OK\n");
    }
    printf("RESULT:%d\n", rv);  
    dsSet(&sptr);

    return passed;
}

int check_set_member3(){
    int passed=1;
    _Bool rv;

    printf("set_member({5,7},5)\n");    
    IntSetADT sptr = mkSetv(2,5,7);
    rv = set_member(sptr, 5);
    if (!rv) {
        printf("FAILED\n");
        printf("EXPECTED: NOT %d\n", 0);   
        passed=false;
    } else {
        printf("OK\n");
    }
    printf("RESULT:%d\n", rv);  
    dsSet(&sptr);

    return passed;
}

int check_set_member4(){
    int passed=1;
    _Bool rv;

    printf("set_member({5,7},7)\n");    
    IntSetADT sptr = mkSetv(2,5,7);
    rv = set_member(sptr, 7);
    if (!rv) {
        printf("FAILED\n");
        printf("EXPECTED: NOT %d\n", 0);   
        passed=0;
    } else {
        printf("OK\n");
    }
    printf("RESULT:%d\n", rv);  
    dsSet(&sptr);

    return passed;
}

int check_isEmptySet1(){
    int passed=1;
    _Bool rv;

    printf("isEmptySet(NULL)\n");    
    rv = isEmptySet(NULL);
    if (rv) {
        printf("FAILED\n");
        printf("EXPECTED: %d\n", 0);   
        passed=0;
    } else {
        printf("OK\n");
    }
    printf("RESULT:%d\n", rv);  

    return passed;
}

int check_isEmptySet2(){
    int passed=1;
    _Bool rv;

    printf("isEmptySet({})\n");    
    IntSetADT sptr = mkSet();
    rv = isEmptySet(sptr);
    if (!rv) {
        printf("FAILED\n");
        printf("EXPECTED: NOT %d\n", 0);   
        passed=0;
    } else {
        printf("OK\n");
    }
    printf("RESULT:%d\n", rv);  
    dsSet(&sptr);

    return passed;
}

int check_isEmptySet3(){
    int passed=1;
    _Bool rv;

    printf("isEmpty({5})\n");    
    IntSetADT sptr = mkSetv(1,5);
    rv = isEmptySet(sptr);
    if (rv) {
        printf("FAILED\n");
        printf("EXPECTED: %d\n", 0);
        passed=0;   
    } else {
        printf("OK\n");
    }
    printf("RESULT:%d\n", rv); 
    dsSet(&sptr);

    return passed;
}

int check_set_size1(){
    int passed=1;
    int rv;

    printf("set_size(NULL)\n");    
    rv = set_size(NULL);
    if (rv!=-1) {
        printf("FAILED\n");
        printf("EXPECTED: %d\n", -1);
        passed=0;   
    } else {
        printf("OK\n");
    }
    printf("RESULT:%d\n", rv);  

    return passed;
}

int check_set_size2(){
    int passed=1;
    int rv;

    printf("set_size({})\n");    
    IntSetADT sptr = mkSet();
    rv = set_size(sptr);
    if (rv!=0) {
        printf("FAILED\n");
        printf("EXPECTED: %d\n", 0);
        passed=0;   
    } else {
        printf("OK\n");
    }
    printf("RESULT:%d\n", rv);  
    dsSet(&sptr);

    return passed;
}

int check_set_size3(){
    int passed=1;
    int rv;

    printf("set_size({5})\n");    
    IntSetADT sptr = mkSetv(1,5);
    rv = set_size(sptr);
    if (rv!=1) {
        printf("FAILED\n");
        printf("EXPECTED: %d\n", 1);
        passed=0;   
    } else {
        printf("OK\n");
    }
    printf("RESULT:%d\n", rv);  
    dsSet(&sptr);

    return passed;
}

int check_set_size4(){
    int passed=1;
    int rv;

    printf("set_size({5,7})\n");    
    IntSetADT sptr = mkSetv(2,5,7);
    rv = set_size(sptr);
    if (rv!=2) {
        printf("FAILED\n");
        printf("EXPECTED: %d\n", 2);   
        passed=0;
    } else {
        printf("OK\n");
    }
    printf("RESULT:%d\n", rv);  
    dsSet(&sptr);

    return passed;
}

int check_set_extract1(){
    int passed=1;
    _Bool rv;
    int dat;

    printf("set_extract(NULL)\n");    
    rv = set_extract(NULL, &dat);
    if (rv) {
        printf("FAILED\n");
        printf("EXPECTED: %d\n", 0);
        passed=0;   
    } else {
        printf("OK\n");
    }
    printf("RESULT: %d\n", rv);  

    return passed;
}

int check_set_extract2(){
    int passed=1;
    _Bool rv;
    int dat;

    printf("set_extract({})\n");    
    IntSetADT sptr = mkSet();
    rv = set_extract(sptr, &dat);
    if (rv) {
        printf("FAILED\n");
        printf("EXPECTED: %d\n", 0);
        passed=0;   
    } else {
        printf("OK\n");
    }
    printf("RESULT: %d\n", rv);  
    dsSet(&sptr);

    return passed;
}

int check_set_extract3(){
    int passed=1;
    _Bool rv;
    int dat1,dat2,dat3;

    IntSetADT sptr = mkSetv(3,3,5,7);
    printf("set_extract(%s)\n", toString(sptr));    
    rv = set_extract(sptr,&dat1);
    if (!rv || (dat1!=3 && dat1!=5 && dat1!=7)) {
        printf("FAILED\n");
        printf("EXPECTED: NOT %d AND VALUE IN %s\n", 0, toString(sptr));
        passed=0;   
    } else {
        printf("OK\n");
    }
    printf("RESULT:%d AND VALUE %d\n", rv, dat1);  

    if (passed) {
        printf("set_extract(%s))\n", toString(sptr));    
        rv = set_extract(sptr,&dat2);
        if (!rv || dat2==dat1 || (dat2!=3 && dat2!=5 && dat2!=7)) {
            printf("FAILED\n");
            printf("EXPECTED: NOT %d AND VALUE IN %s\n", 0, toString(sptr));
            passed=0;   
        } else {
            printf("OK\n");
        }
        printf("RESULT:%d AND VALUE %d\n", rv, dat2);  
    }

    if (passed) {
        printf("set_extract(%s)\n", toString(sptr));    
        rv = set_extract(sptr,&dat3);
        if (!rv || dat3==dat1 || dat3==dat2 || (dat3!=3 && dat3!=5 && dat3!=7)) {
            printf("FAILED\n");
            printf("EXPECTED: NOT %d  AND VALUE IN %s\n", 0, toString(sptr));
            passed=0;   
        } else {
            printf("OK\n");
        }
        printf("RESULT:%d AND VALUE %d\n", rv, dat3);  
    }
    dsSet(&sptr);

    return passed;
}

int check_set_equals1(){
    int passed=1;
    _Bool rv;

    IntSetADT sptr1 = mkSet();
    printf("set_equals(NULL, {})\n");    
    rv = set_equals(NULL,sptr1);
    if (rv) {
        printf("FAILED\n");
        printf("EXPECTED: %d\n", 0);
        passed=0;   
    } else {
        printf("OK\n");
    }
    printf("RESULT: %d\n", rv);
    dsSet(&sptr1);

    return passed;
}

int check_set_equals2(){
    int passed=1;
    _Bool rv;

    IntSetADT sptr1 = mkSet();
    printf("set_equals({}, NULL)\n");    
    rv = set_equals(sptr1,NULL);
    if (rv) {
        printf("FAILED\n");
        printf("EXPECTED: %d\n", 0);   
        passed=0;
    } else {
        printf("OK\n");
    }
    printf("RESULT: %d\n", rv);
    dsSet(&sptr1);

    return passed;
}

int check_set_equals3(){
    int passed=1;
    _Bool rv;

    IntSetADT sptr1 = mkSet();
    IntSetADT sptr2 = mkSet();
    printf("set_equals({}, {})\n");    
    rv = set_equals(sptr2,sptr1);
    if (!rv) {
        printf("FAILED\n");
        printf("EXPECTED: NOT %d\n", 0);   
        passed=0;
    } else {
        printf("OK\n");
    }
    printf("RESULT:%d\n", rv);
    dsSet(&sptr2);
    dsSet(&sptr1);

    return passed;
}

int check_set_equals4(){
    int passed=1;
    _Bool rv;

    IntSetADT sptr1 = mkSet();
    IntSetADT sptr2 = mkSetv(3,3,5,7);
    printf("set_equals({}, {3,5,7})\n");    
    rv = set_equals(sptr2,sptr1);
    if (rv) {
        printf("FAILED\n");
        printf("EXPECTED: %d\n", 0);   
        passed=0;
    } else {
        printf("OK\n");
    }
    printf("RESULT:%d\n", rv);
    dsSet(&sptr2);
    dsSet(&sptr1);

    return passed;
}

int check_set_equals5(){
    int passed=1;
    _Bool rv;

    IntSetADT sptr1 = mkSetv(3,3,5,7);
    IntSetADT sptr2 = mkSetv(3,3,5,7);
    printf("set_equals({3,5,7}, {3,5,7})\n");    
    rv = set_equals(sptr2,sptr1);
    if (!rv) {
        printf("FAILED\n");
        printf("EXPECTED: NOT %d\n", 0);   
        passed=0;
    } else {
        printf("OK\n");
    }
    printf("RESULT:%d\n", rv);
    dsSet(&sptr2);
    dsSet(&sptr1);

    return passed;
}

int check_set_equals6(){
    int passed=1;
    _Bool rv;

    IntSetADT sptr1 = mkSetv(3,3,5,7);
    IntSetADT sptr2 = mkSetv(2,3,5);
    printf("set_equals({3,5,7}, {3,5})\n");    
    rv = set_equals(sptr2,sptr1);
    if (rv) {
        printf("FAILED\n");
        printf("EXPECTED: %d\n", 0);   
        passed=0;
    } else {
        printf("OK\n");
    }
    printf("RESULT:%d\n", rv);
    dsSet(&sptr2);
    dsSet(&sptr1);

    return passed;
}

int check_subseteq1(){
    int passed=1;
    _Bool rv;

    IntSetADT sptr1 = mkSet();
    printf("subseteq(NULL, {})\n");    
    rv = subseteq(NULL,sptr1);
    if (rv) {
        printf("FAILED\n");
        printf("EXPECTED: %d\n", 0);
        passed=0;   
    } else {
        printf("OK\n");
    }
    printf("RESULT: %d\n", rv);
    dsSet(&sptr1);

    return passed;
}

int check_subseteq2(){
    int passed=1;
    _Bool rv;

    IntSetADT sptr1 = mkSet();
    printf("subseteq({}, NULL)\n");    
    rv = subseteq(sptr1,NULL);
    if (rv) {
        printf("FAILED\n");
        printf("EXPECTED: %d\n", 0);   
        passed=0;
    } else {
        printf("OK\n");
    }
    printf("RESULT: %d\n", rv);
    dsSet(&sptr1);

    return passed;
}

int check_subseteq3(){
    int passed=1;
    _Bool rv;

    IntSetADT sptr1 = mkSetv(3,3,5,7);
    IntSetADT sptr2 = mkSet();
    printf("subseteq({}, {3,5,7})\n");    
    rv = subseteq(sptr2,sptr1);
    if (!rv) {
        printf("FAILED\n");
        printf("EXPECTED: NOT %d\n", 0);   
        passed=0;
    } else {
        printf("OK\n");
    }
    printf("RESULT:%d\n", rv);
    dsSet(&sptr2);
    dsSet(&sptr1);

    return passed;
}

int check_subseteq4(){
    int passed=1;
    _Bool rv;

    IntSetADT sptr1 = mkSetv(3,3,5,7);
    IntSetADT sptr2 = mkSetv(1,3);
    printf("subseteq({3}, {3,5,7})\n");    
    rv = subseteq(sptr2,sptr1);
    if (!rv) {
        printf("FAILED\n");
        printf("EXPECTED: NOT %d\n", 0);   
        passed=0;
    } else {
        printf("OK\n");
    }
    printf("RESULT:%d\n", rv);
    dsSet(&sptr2);
    dsSet(&sptr1);

    return passed;
}

int check_subseteq5(){
    int passed=1;
    _Bool rv;

    IntSetADT sptr1 = mkSetv(3,3,5,7);
    IntSetADT sptr2 = mkSet(2,3,5);
    printf("subseteq({3,5}, {3,5,7})\n");    
    rv = subseteq(sptr2,sptr1);
    if (!rv) {
        printf("FAILED\n");
        printf("EXPECTED: NOT %d\n", 0);  
        passed=0; 
    } else {
        printf("OK\n");
    }
    printf("RESULT:%d\n", rv);
    dsSet(&sptr2);
    dsSet(&sptr1);

    return passed;
}

int check_subseteq6(){
    int passed=1;
    _Bool rv;

    IntSetADT sptr1 = mkSetv(3,3,5,7);
    IntSetADT sptr2 = mkSet(3,3,5,7);
    printf("subseteq({3,5,7}, {3,5,7})\n");    
    rv = subseteq(sptr2,sptr1);
    if (!rv) {
        printf("FAILED\n");
        printf("EXPECTED: NOT %d\n", 0);   
        passed=0;
    } else {
        printf("OK\n");
    }
    printf("RESULT:%d\n", rv);
    dsSet(&sptr2);
    dsSet(&sptr1);

    return passed;
}

int check_subseteq7(){
    int passed=1;
    _Bool rv;

    IntSetADT sptr1 = mkSetv(3,3,5,7);
    IntSetADT sptr2 = mkSetv(4,3,5,7,9);
    printf("subseteq({3,5,7,9}, {3,5,7})\n");    
    rv = subseteq(sptr2,sptr1);
    if (rv) {
        printf("FAILED\n");
        printf("EXPECTED: %d\n", 0);   
        passed=0;
    } else {
        printf("OK\n");
    }
    printf("RESULT:%d\n", rv);
    dsSet(&sptr2);
    dsSet(&sptr1);

    return passed;
}

int check_subseteq8(){
    int passed=1;
    _Bool rv;

    IntSetADT sptr1 = mkSet();
    IntSetADT sptr2 = mkSetv(1,5);
    printf("subseteq({5}, {})\n");    
    rv = subseteq(sptr2,sptr1);
    if (rv) {
        printf("FAILED\n");
        printf("EXPECTED: %d\n", 0);
        passed=0;   
    } else {
        printf("OK\n");
    }
    printf("RESULT:%d\n", rv);
    dsSet(&sptr2);
    dsSet(&sptr1);

    return passed;
}

int check_subset1() {
    int passed=1;
    _Bool rv;

    IntSetADT sptr1 = mkSet();
    printf("subset(NULL, {})\n");    
    rv = subset(NULL,sptr1);
    if (rv) {
        printf("FAILED\n");
        printf("EXPECTED: %d\n", 0);
        passed=0;   
    } else {
        printf("OK\n");
    }
    printf("RESULT: %d\n", rv);
    dsSet(&sptr1);

    return passed;
}

int check_subset2(){
    int passed=1;
    _Bool rv;

    IntSetADT sptr1 = mkSet();
    printf("subset({}, NULL)\n");    
    rv = subset(sptr1,NULL);
    if (rv) {
        printf("FAILED\n");
        printf("EXPECTED: %d\n", 0);   
        passed=0;
    } else {
        printf("OK\n");
    }
    printf("RESULT: %d\n", rv);
    dsSet(&sptr1);

    return passed;
}

int check_subset3(){
    int passed=1;
    _Bool rv;

    IntSetADT sptr1 = mkSetv(3,3,5,7);
    IntSetADT sptr2 = mkSet();
    printf("subset({}, {3,5,7})\n");    
    rv = subset(sptr2,sptr1);
    if (!rv) {
        printf("FAILED\n");
        printf("EXPECTED: NOT %d\n", 0);   
        passed=0;
    } else {
        printf("OK\n");
    }
    printf("RESULT:%d\n", rv);
    dsSet(&sptr2);
    dsSet(&sptr1);

    return passed;
}

int check_subset4(){
    int passed=1;
    _Bool rv;

    IntSetADT sptr1 = mkSetv(3,3,5,7);
    IntSetADT sptr2 = mkSetv(1,3);
    printf("subset({3}, {3,5,7})\n");    
    rv = subset(sptr2,sptr1);
    if (!rv) {
        printf("FAILED\n");
        printf("EXPECTED: NOT %d\n", 0);   
        passed=0;
    } else {
        printf("OK\n");
    }
    printf("RESULT:%d\n", rv);
    dsSet(&sptr2);
    dsSet(&sptr1);

    return passed;
}

int check_subset5(){
    int passed=1;
    _Bool rv;

    IntSetADT sptr1 = mkSetv(3,3,5,7);
    IntSetADT sptr2 = mkSet(2,3,5);
    printf("subset({3,5}, {3,5,7})\n");    
    rv = subset(sptr2,sptr1);
    if (!rv) {
        printf("FAILED\n");
        printf("EXPECTED: NOT %d\n", 0);  
        passed=0; 
    } else {
        printf("OK\n");
    }
    printf("RESULT:%d\n", rv);
    dsSet(&sptr2);
    dsSet(&sptr1);

    return passed;
}

int check_subset6(){
    int passed=1;
    _Bool rv;

    IntSetADT sptr1 = mkSetv(3,3,5,7);
    IntSetADT sptr2 = mkSetv(3,3,5,7);
    printf("subset({3,5,7}, {3,5,7})\n");    
    rv = subset(sptr2,sptr1);
    if (rv) {
        printf("FAILED\n");
        printf("EXPECTED: %d\n", 0);   
        passed=0;
    } else {
        printf("OK\n");
    }
    printf("RESULT:%d\n", rv);
    dsSet(&sptr2);
    dsSet(&sptr1);

    return passed;
}

int check_subset7(){
    int passed=1;
    _Bool rv;

    IntSetADT sptr1 = mkSetv(3,3,5,7);
    IntSetADT sptr2 = mkSetv(4,3,5,7,9);
    printf("subset({3,5,7,9}, {3,5,7})\n");    
    rv = subset(sptr2,sptr1);
    if (rv) {
        printf("FAILED\n");
        printf("EXPECTED: %d\n", 0);   
        passed=0;
    } else {
        printf("OK\n");
    }
    printf("RESULT:%d\n", rv);
    dsSet(&sptr2);
    dsSet(&sptr1);

    return passed;
}

int check_subset8(){
    int passed=1;
    _Bool rv;

    IntSetADT sptr1 = mkSet();
    IntSetADT sptr2 = mkSetv(1,5);
    printf("subset({5}, {})\n");    
    rv = subset(sptr2,sptr1);
    if (rv) {
        printf("FAILED\n");
        printf("EXPECTED: %d\n", 0);
        passed=0;   
    } else {
        printf("OK\n");
    }
    printf("RESULT:%d\n", rv);
    dsSet(&sptr2);
    dsSet(&sptr1);

    return passed;
}

int check_set_union1() {
    int passed=1;

    IntSetADT sptr1 = mkSet();
    IntSetADT uset;
    printf("set_union({},NULL)\n");
    uset = set_union(sptr1,NULL);
    if (uset) {
        printf("FAILED\n");
        printf("EXPECTED: NOT %p\n", uset);
        passed=0;   
    } else {
        printf("OK\n");
    }

    return passed;
}

int check_set_union2() {
    int passed=1;

    IntSetADT sptr1 = mkSet();
    IntSetADT uset;
    printf("set_union(NULL,{})\n");
    uset = set_union(NULL,sptr1);
    if (uset) {
        printf("FAILED\n");
        printf("EXPECTED: NOT %p\n", uset);
        passed=0;   
    } else {
        printf("OK\n");
    }

    return passed;
}

int check_set_union3() {
    int passed=1;

    IntSetADT sptr1,sptr2;
    IntSetADT uset,expset;

    sptr1 = mkSetv(3,3,5,7);  
    sptr2 = mkSet();
    printf("set_union({3,5,7},{})\n");
    uset = set_union(sptr1,sptr2);
    expset = mkSetv(3,7,5,3);
    if (!set_equals(uset, expset)) {
        printf("FAILED\n");
        printf("EXPECTED: %s\n", "{7,5,3}");
        passed=0;   
    } else {
        printf("OK\n");
    }
    printf("RESULT: %s\n", toString(uset));
    dsSet(&expset);
    dsSet(&uset);
    dsSet(&sptr2);
    dsSet(&sptr1);

    return passed;
}

int check_set_union4() {
    int passed=1;

    IntSetADT sptr1,sptr2;
    IntSetADT uset,expset;

    sptr1 = mkSetv(3,3,5,7);  
    sptr2 = mkSetv(1,5);
    uset = set_union(sptr1,sptr2);
    printf("set_union({3,5,7},{5})\n");
    expset = mkSetv(3,7,5,3);
    if (!set_equals(uset, expset)) {
        printf("FAILED\n");
        printf("EXPECTED: %s\n", "{7,5,3}");
        passed=0;   
    } else {
        printf("OK\n");
    }
    printf("RESULT: %s\n", toString(uset));
    dsSet(&expset);
    dsSet(&uset);
    dsSet(&sptr2);
    dsSet(&sptr1);

    return passed;
}

int check_set_union5() {
    int passed=1;

    IntSetADT sptr1,sptr2;
    IntSetADT uset,expset;

    sptr1 = mkSetv(3,3,5,7);  
    sptr2 = mkSetv(1,9);
    uset = set_union(sptr1,sptr2);
    printf("set_union({3,5,7},{9})\n");
    expset = mkSetv(4,9,7,5,3);
    if (!set_equals(uset, expset)) {
        printf("FAILED\n");
        printf("EXPECTED: %s\n", "{9,7,5,3}");
        passed=0;   
    } else {
        printf("OK\n");
    }
    printf("RESULT: %s\n", toString(uset));
    dsSet(&expset);
    dsSet(&uset);
    dsSet(&sptr2);
    dsSet(&sptr1);

    return passed;
}

int check_set_intersection1() {
    int passed=1;

    IntSetADT sptr1 = mkSet();
    IntSetADT uset;
    printf("set_intersection({},NULL)\n");
    uset = set_intersection(sptr1,NULL);
    if (uset) {
        printf("FAILED\n");
        printf("EXPECTED: NOT %p\n", uset);
        passed=0;   
    } else {
        printf("OK\n");
    }

    return passed;
}

int check_set_intersection2() {
    int passed=1;

    IntSetADT sptr1 = mkSet();
    IntSetADT uset;
    printf("set_intersection(NULL,{})\n");
    uset = set_intersection(NULL,sptr1);
    if (uset) {
        printf("FAILED\n");
        printf("EXPECTED: NOT %p\n", uset);
        passed=0;   
    } else {
        printf("OK\n");
    }

    return passed;
}

int check_set_intersection3() {
    int passed=1;

    IntSetADT sptr1,sptr2;
    IntSetADT iset,expset;

    sptr1 = mkSetv(3,3,5,7);  
    sptr2 = mkSet();
    iset = set_intersection(sptr1,sptr2);
    printf("set_intersection({3,5,7},{})\n");
    expset = mkSet();
    if (!set_equals(iset, expset)) {
        printf("FAILED\n");
        printf("EXPECTED: %s\n", toString(expset));
        passed=0;   
    } else {
        printf("OK\n");
    }
    printf("RESULT: %s\n", toString(iset));
    dsSet(&expset);
    dsSet(&iset);
    dsSet(&sptr2);
    dsSet(&sptr1);

    return passed;
}

int check_set_intersection4() {
    int passed=1;

    IntSetADT sptr1,sptr2;
    IntSetADT iset,expset;

    sptr1 = mkSetv(3,3,5,7);  
    sptr2 = mkSetv(1,5);
    iset = set_intersection(sptr1,sptr2);
    printf("set_intersection({3,5,7},{5})\n");
    expset = mkSetv(1,5);
    if (!set_equals(iset, expset)) {
        printf("FAILED\n");
        printf("EXPECTED: %s\n", toString(expset));
        passed=0;   
    } else {
        printf("OK\n");
    }
    printf("RESULT: %s\n", toString(iset));
    dsSet(&expset);
    dsSet(&iset);
    dsSet(&sptr2);
    dsSet(&sptr1);

    return passed;
}

int check_set_intersection5() {
    int passed=1;

    IntSetADT sptr1,sptr2;
    IntSetADT iset,expset;

    sptr1 = mkSetv(3,3,5,7);  
    sptr2 = mkSetv(3,5,7,9);
    printf("set_intersection({3,5,7},{5,7,9})\n");
    iset = set_intersection(sptr1,sptr2);
    expset = mkSetv(2,5,7);
    if (!set_equals(iset, expset)) {
        printf("FAILED\n");
        printf("EXPECTED: %s\n", toString(expset));
        passed=0;   
    } else {
        printf("OK\n");
    }
    printf("RESULT: %s\n", toString(iset));
    dsSet(&expset);
    dsSet(&iset);
    dsSet(&sptr2);
    dsSet(&sptr1);

    return passed;
}

int check_set_subtraction1() {
    int passed=1;

    IntSetADT sptr1 = mkSet();
    IntSetADT uset;
    printf("set_subtraction({},NULL)\n");
    uset = set_subtraction(sptr1,NULL);
    if (uset) {
        printf("FAILED\n");
        printf("EXPECTED: NOT %p\n", uset);
        passed=0;   
    } else {
        printf("OK\n");
    }

    return passed;
}

int check_set_subtraction2() {
    int passed=1;

    IntSetADT sptr1 = mkSet();
    IntSetADT uset;
    printf("set_subtraction(NULL,{})\n");
    uset = set_subtraction(NULL,sptr1);
    if (uset) {
        printf("FAILED\n");
        printf("EXPECTED: NOT %p\n", uset);
        passed=0;   
    } else {
        printf("OK\n");
    }

    return passed;
}

int check_set_subtraction3() {
    int passed=1;

    IntSetADT sptr1,sptr2;
    IntSetADT sset,expset;

    sptr1 = mkSetv(3,3,5,7);  
    sptr2 = mkSet();
    sset = set_subtraction(sptr1,sptr2);
    printf("set_subtraction({3,5,7},{})\n");
    expset = mkSetv(3,3,5,7);
    if (!set_equals(sset, expset)) {
        printf("FAILED\n");
        printf("EXPECTED: %s\n", toString(expset));
        passed=0;   
    } else {
        printf("OK\n");
    }
    printf("RESULT: %s\n", toString(sset));
    dsSet(&expset);
    dsSet(&sset);
    dsSet(&sptr2);
    dsSet(&sptr1);

    return passed;
}

int check_set_subtraction4() {
    int passed=1;

    IntSetADT sptr1,sptr2;
    IntSetADT sset,expset;

    sptr1 = mkSetv(3,3,5,7);  
    sptr2 = mkSetv(1,5);
    sset = set_subtraction(sptr1,sptr2);
    printf("set_subtraction({3,5,7},{5})\n");
    expset = mkSetv(2,3,7);
    if (!set_equals(sset, expset)) {
        printf("FAILED\n");
        printf("EXPECTED: %s\n", toString(expset));
        passed=0;   
    } else {
        printf("OK\n");
    }
    printf("RESULT: %s\n", toString(sset));
    dsSet(&expset);
    dsSet(&sset);
    dsSet(&sptr2);
    dsSet(&sptr1);

    return passed;
}

int check_set_subtraction5() {
    int passed=1;

    IntSetADT sptr1,sptr2;
    IntSetADT sset,expset;

    sptr1 = mkSetv(3,3,5,7);  
    sptr2 = mkSetv(3,5,7,9);
    sset = set_subtraction(sptr1,sptr2);
    printf("set_subtraction({3,5,7},{5,7,9})\n");
    expset = mkSetv(1,3);
    if (!set_equals(sset, expset)) {
        printf("FAILED\n");
        printf("EXPECTED: %s\n", toString(expset));
        passed=false;   
    } else {
        printf("OK\n");
    }
    printf("RESULT: %s\n", toString(sset));
    dsSet(&expset);
    dsSet(&sset);
    dsSet(&sptr2);
    dsSet(&sptr1);

    return passed;
}

int main(int argc, char *argv[]) {
  puts("BEGIN TEST intLinkedListSetADT"); 

  {
    printf("TEST mkSet\n");
    check_mkSet();
    printf("\n");
  }

  {
    printf("TEST dsSet\n");
    check_dsSet1();
    check_dsSet2();
    printf("\n");
  }

  {
    printf("TEST set_add\n");
    check_set_add1();
    check_set_add2();
    check_set_add3();
    check_set_add4();
    printf("\n");
  }

  {
    printf("TEST set_remove\n");    
    check_set_remove1();
    check_set_remove2();
    check_set_remove3();
    check_set_remove4();
    check_set_remove5();
    printf("\n");
  }

  {
    printf("TEST set_member\n");    
    check_set_member1();
    check_set_member2();
    check_set_member3();
    check_set_member4();
    
    printf("\n");
  }

  {
    printf("TEST isEmptySet\n");    
    check_isEmptySet1();
    check_isEmptySet2();
    check_isEmptySet3();
    printf("\n");
  }

  {
    printf("TEST set_size\n");    
    check_set_size1();
    check_set_size2();
    check_set_size3();
    check_set_size4();
    printf("\n");
  }

  {
    printf("TEST set_extract\n");    
    check_set_extract1();
    check_set_extract2();
    check_set_extract3();
    printf("\n");
  }

  {
    printf("TEST set_equals\n");    
    check_set_equals1();
    check_set_equals2();
    check_set_equals3();
    check_set_equals4();
    check_set_equals5();
    check_set_equals6();
    printf("\n");
  }

  {
    printf("TEST subseteq\n");    
    check_subseteq1();
    check_subseteq2();
    check_subseteq3();
    check_subseteq4();
    check_subseteq5();
    check_subseteq6();
    check_subseteq7();
    check_subseteq8();
    printf("\n");
  }

  {
    printf("TEST subset\n");    
    check_subset1();
    check_subset2();
    check_subset3();
    check_subset4();
    check_subset5();
    check_subset6();
    check_subset7();
    check_subset8();
    printf("\n");
  }

  {
    printf("TEST set_union\n");    
    check_set_union1();
    check_set_union2();
    check_set_union3();
    check_set_union4();
    check_set_union5();
    printf("\n");
  }

  {
    printf("TEST set_intersection\n");    
    check_set_intersection1();
    check_set_intersection2();
    check_set_intersection3();
    check_set_intersection4();
    check_set_intersection5();
    printf("\n");
  }

  {
    printf("TEST set_subtraction\n");    
    check_set_subtraction1();
    check_set_subtraction2();
    check_set_subtraction3();
    check_set_subtraction4();
    check_set_subtraction5();
    printf("\n");
  }

}