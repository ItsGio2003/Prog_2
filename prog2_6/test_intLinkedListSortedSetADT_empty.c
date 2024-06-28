#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "intSortedSetADT.h"
#include "intLinkedListSortedSetADT.h"

IntSortedSetADT mkSSetv(int count, ...) {
    IntSortedSetADT set = mkSSet();

    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; ++i) {
        int num = va_arg(args, int);
        sset_add(set,num);        
    }
    va_end(args);
    return set;
}

char *toString(IntSortedSetADT set) {
    char *sout = malloc(100*sizeof(char));

    ListNodePtr nptr = set->first;
    sprintf(sout, "{");
    while (nptr) {
        if (nptr == set->first)
            sprintf(sout+strlen(sout), "%d", nptr->elem);
        else
            sprintf(sout+strlen(sout), ",%d", nptr->elem);
        nptr = nptr->next;
    }

    sprintf(sout+strlen(sout), "}");

    return sout;
}

int check_mkSSet() {
    int passed = 1;
    printf("mkSet()\n");    
    IntSortedSetADT sptr = mkSSet();
    if (!sptr) {
        printf("FAILED");
        printf("EXPECTED: not %d\n", 0);   
    } else
        printf("OK\n");
    printf("RESULT:%ld\n\n", sptr);  
    return passed;
}

int check_dsSSet() {
    int passed = 1;

    if (passed) {
        _Bool rv;
        IntSortedSetADT sptr = mkSSet();
        printf("dsSSet({})\n");    
        rv = dsSSet(&sptr);
        if (!rv || sptr) {
            printf("FAILED\n");
            printf("EXPECTED: NOT %d AND PTR %ld\n", 0, NULL); 
            passed=0;  
        } else {
            printf("OK\n");
        }
        printf("RESULT:%d AND PTR %ld\n\n", rv, sptr);
    }  

    if (passed) {
        _Bool rv;
        printf("dsSSet(NULL)\n");    
        rv = dsSSet(NULL);
        if (rv) {
            printf("FAILED\n");
            printf("EXPECTED: %d\n", 0);
            passed=0;   
        } else {
            printf("OK\n");
        }
        printf("RESULT:%d\n\n", rv);
    }

    return passed;
}

int check_sset_add() {
    int passed=1;
    _Bool rv;
    printf("sset_add(NULL,5)\n");    
    rv = sset_add(NULL,5);
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

int check_sset_remove(){
    int passed=1;
    _Bool rv;

    printf("sset_remove(NULL,3)\n");    
    rv = sset_remove(NULL, 3);
    if (rv) {
        printf("FAILED\n");
        printf("EXPECTED: %d\n", 0);
        passed=0;
    } else {
        printf("OK\n");
    }
    printf("RESULT: %d\n", rv);

    return passed;;
}

int check_sset_member(){
    int passed=1;
    _Bool rv;

    printf("set_member(NULL,3)\n");    
    rv = sset_member(NULL, 3);
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

int check_isEmptySSet(){
    int passed=1;
    _Bool rv;

    printf("isEmpty({5})\n");    
    IntSortedSetADT sptr = mkSSetv(1,5);
    rv = isEmptySSet(sptr);
    if (rv) {
        printf("FAILED\n");
        printf("EXPECTED: %d\n", 0);
        passed=0;   
    } else {
        printf("OK\n");
    }
    printf("RESULT:%d\n", rv); 
    dsSSet(&sptr);

    return passed;
}

int check_sset_size(){
    int passed=1;
    int rv;

    printf("set_size({5,7})\n");    
    IntSortedSetADT sptr = mkSSetv(2,5,7);
    rv = sset_size(sptr);
    if (rv!=2) {
        printf("FAILED\n");
        printf("EXPECTED: %d\n", 2);   
        passed=0;
    } else {
        printf("OK\n");
    }
    printf("RESULT:%d\n", rv);  
    dsSSet(&sptr);

    return passed;
}


int check_sset_extract(){
    int passed=1;
    _Bool rv;
    int dat;

    printf("set_extract({})\n");    
    IntSortedSetADT sptr = mkSSet();
    rv = sset_extract(sptr, &dat);
    if (rv) {
        printf("FAILED\n");
        printf("EXPECTED: %d\n", 0);
        passed=0;   
    } else {
        printf("OK\n");
    }
    printf("RESULT: %d\n", rv);  
    dsSSet(&sptr);

    return passed;
}

int check_sset_equals(){
    int passed=1;
    _Bool rv;

    IntSortedSetADT sptr1 = mkSSetv(3,3,5,7);
    IntSortedSetADT sptr2 = mkSSetv(3,3,5,7);
    printf("set_equals({3,5,7}, {3,5,7})\n");    
    rv = sset_equals(sptr2,sptr1);
    if (!rv) {
        printf("FAILED\n");
        printf("EXPECTED: NOT %d\n", 0);   
        passed=0;
    } else {
        printf("OK\n");
    }
    printf("RESULT:%d\n", rv);
    dsSSet(&sptr2);
    dsSSet(&sptr1);

    return passed;
}

int check_sset_subseteq(){
    int passed=1;
    _Bool rv;

    IntSortedSetADT sptr1 = mkSSetv(3,3,5,7);
    IntSortedSetADT sptr2 = mkSSetv(1,3);
    printf("subseteq({3}, {3,5,7})\n");    
    rv = sset_subseteq(sptr2,sptr1);
    if (!rv) {
        printf("FAILED\n");
        printf("EXPECTED: NOT %d\n", 0);   
        passed=0;
    } else {
        printf("OK\n");
    }
    printf("RESULT:%d\n", rv);
    dsSSet(&sptr2);
    dsSSet(&sptr1);

    return passed;
}

int check_sset_subset() {
    int passed=1;
    _Bool rv;

    IntSortedSetADT sptr1 = mkSSetv(3,3,5,7);
    IntSortedSetADT sptr2 = mkSSetv(4,3,5,7,9);
    printf("subset({3,5,7,9}, {3,5,7})\n");    
    rv = sset_subset(sptr2,sptr1);
    if (rv) {
        printf("FAILED\n");
        printf("EXPECTED: %d\n", 0);   
        passed=0;
    } else {
        printf("OK\n");
    }
    printf("RESULT:%d\n", rv);
    dsSSet(&sptr2);
    dsSSet(&sptr1);

    return passed;
}


int check_sset_union() {
    int passed=1;

    IntSortedSetADT sptr1,sptr2;
    IntSortedSetADT uset,expset;

    sptr1 = mkSSetv(3,3,5,7);  
    sptr2 = mkSSetv(1,5);
    uset = sset_union(sptr1,sptr2);
    printf("set_union({3,5,7},{5})\n");
    expset = mkSSetv(3,7,5,3);
    if (!sset_equals(uset, expset)) {
        printf("FAILED\n");
        printf("EXPECTED: %s\n", "{7,5,3}");
        passed=0;   
    } else {
        printf("OK\n");
    }
    printf("RESULT: %s\n", toString(uset));
    dsSSet(&expset);
    dsSSet(&uset);
    dsSSet(&sptr2);
    dsSSet(&sptr1);

    return passed;
}

int check_sset_intersection() {
    int passed=1;

    IntSortedSetADT sptr1,sptr2;
    IntSortedSetADT iset,expset;

    sptr1 = mkSSetv(3,3,5,7);  
    sptr2 = mkSSetv(1,5);
    iset = sset_intersection(sptr1,sptr2);
    printf("sset_intersection({3,5,7},{5})\n");
    expset = mkSSetv(1,5);
    if (!sset_equals(iset, expset)) {
        printf("FAILED\n");
        printf("EXPECTED: %s\n", toString(expset));
        passed=0;   
    } else {
        printf("OK\n");
    }
    printf("RESULT: %s\n", toString(iset));
    dsSSet(&expset);
    dsSSet(&iset);
    dsSSet(&sptr2);
    dsSSet(&sptr1);

    return passed;
}

int check_sset_subtraction() {
   int passed=1;

    IntSortedSetADT sptr1,sptr2;
    IntSortedSetADT sset,expset;

    sptr1 = mkSSetv(3,3,5,7);  
    sptr2 = mkSSetv(1,5);
    sset = sset_subtraction(sptr1,sptr2);
    printf("sset_subtraction({3,5,7},{5})\n");
    expset = mkSSetv(2,3,7);
    if (!sset_equals(sset, expset)) {
        printf("FAILED\n");
        printf("EXPECTED: %s\n", toString(expset));
        passed=0;   
    } else {
        printf("OK\n");
    }
    printf("RESULT: %s\n", toString(sset));
    dsSSet(&expset);
    dsSSet(&sset);
    dsSSet(&sptr2);
    dsSSet(&sptr1);

    return passed;
}

int check_sset_min(){
    int passed=1;

    return passed;
}

int check_sset_max(){
    int passed=1;

    return passed;
}

int check_sset_extractMin(){
    int passed=1;

    return passed;
}

int check_sset_extractMax(){
    int passed=1;

    return passed;
}

int main(int argc, char *argv[]) {
  puts("BEGIN TEST intLinkedListSortedSetADT"); 

  {
    printf("TEST mkSSet\n");
    check_mkSSet();
    printf("\n");
  }

  {
    printf("TEST dsSSet\n");
    check_dsSSet();
    printf("\n");
  }

  {
    printf("TEST sset_add\n");
    check_sset_add();
    printf("\n");
  }

  {
    printf("TEST sset_remove\n");    
    check_sset_remove();
    printf("\n");
  }

  {
    printf("TEST sset_member\n");    
    check_sset_member();
    printf("\n");
  }

  {
    printf("TEST isEmptySSet\n");    
    check_isEmptySSet();
    printf("\n");
  }

  {
    printf("TEST sset_size\n");    
    check_sset_size();
    printf("\n");
  }

  {
    printf("TEST sset_extract\n");    
    check_sset_extract();
    printf("\n");
  }

  {
    printf("TEST sset_equals\n");    
    check_sset_equals();
    printf("\n");
  }

  {
    printf("TEST sset_subseteq\n");    
    check_sset_subseteq();
    printf("\n");
  }

  {
    printf("TEST sset_subset\n");    
    check_sset_subset();
    printf("\n");
  }

  {
    printf("TEST sset_union\n");    
    check_sset_union();
    printf("\n");
  }

  {
    printf("TEST sset_intersection\n");    
    check_sset_intersection();
    printf("\n");
  }

  {
    printf("TEST sset_subtraction\n");    
    check_sset_subtraction();
    printf("\n");
  }

  {
    printf("TEST sset_min\n");    
    check_sset_min();
    printf("\n");
  }

  {
    printf("TEST sset_max\n");    
    check_sset_max();
    printf("\n");
  }

  {
    printf("TEST sset_extractMin\n");    
    check_sset_extractMin();
    printf("\n");
  }

  {
    printf("TEST sset_extractMax\n");    
    check_sset_extractMax();
    printf("\n");
  }
}