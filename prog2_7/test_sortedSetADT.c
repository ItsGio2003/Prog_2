#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include "sortedSetADT.h"

int compareint(void*e1, void*e2) {
    int i1 = *(int*)e1;
    int i2 = *(int*)e2;
    if(i1 < i2) return -1;
    if(i1 == i2) return 0;
    return 1;
}

void stampaint(void* elem) {
    printf("%d ",(*(int*)elem));
}

void stampaSet(SortedSetADTptr ss, void (*stampaelem)(void*));

// for debug: quickly initialize a set of integers
SortedSetADTptr mkSSetvi(int count, ...) {
    SortedSetADTptr set = mkSSet(&compareint);
    void* elem;
    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; ++i) {
        elem = va_arg(args, void*);
        sset_add(set,elem);        
    }
    va_end(args);
    return set;
}

int main(int argc, char *argv[]) {
    
    SortedSetADTptr set, s1, s2;
    int n_[] = {0,1,2,3,4,5,6,7,8,9}; 
    int check; 
    int elem;
    int* ptr = &elem;
    
    srand(2024);

    puts("BEGIN TEST of SortedSetADT"); 

    puts("*** first part: operations on a single set");
    
    printf("\nCreating set\n");
    set = mkSSet(&compareint);
    stampaSet(set,&stampaint);

    check = sset_add(set,&n_[3]);
    printf("\nAdding 3, check = %d\n",check);
    stampaSet(set,&stampaint);

    check = sset_add(set,&n_[8]);
    printf("\nAdding 8, check = %d\n",check);
    stampaSet(set,&stampaint);

    check = sset_add(set,&n_[8]);
    printf("\nReadding 8, check = %d\n",check);
    stampaSet(set,&stampaint);

    check = sset_add(set,&n_[5]);
    printf("\nAdding 5, check = %d\n",check);
    stampaSet(set,&stampaint);

    check = sset_add(set,&n_[1]);
    printf("\nAdding 1, check = %d\n",check);
    stampaSet(set,&stampaint);

    check = sset_add(set,&n_[1]);
    printf("\nReadding 1, check = %d\n",check);
    stampaSet(set,&stampaint);

    check = sset_add(set,&n_[3]);
    printf("\nReadding 3, check = %d\n",check);
    stampaSet(set,&stampaint);

    check = sset_min(set,(void**)&ptr);
    printf("\nmin, check = %d\n",check);
    if(check) printf("min = %d\n",(int)*ptr);

    check = sset_extractMin(set,(void**)&ptr);
    printf("\nextractMin, check = %d\n",check);
    stampaSet(set,&stampaint);

    check = sset_max(set,(void**)&ptr);
    printf("\nmax, check = %d\n",check);
    if(check) printf("max = %d\n",(int)*ptr);

    check = sset_extractMax(set,(void**)&ptr);
    printf("\nextractMax, check = %d\n",check);
    stampaSet(set,&stampaint);

    check = sset_add(set,&n_[1]);
    printf("\nre-adding 1, check = %d\n",check);
    stampaSet(set,&stampaint);

    check = sset_add(set,&n_[8]);
    printf("\nre-adding 8, check = %d\n",check);
    stampaSet(set,&stampaint);

    check = sset_extract(set,(void**)&ptr);
    printf("\nChecking extract, check = %d\n",check);
    if(check) printf("extracted elem = %d\n",(int)*ptr);
    stampaSet(set,&stampaint);

    check = sset_remove(set,&n_[3]);
    printf("\nRemoving 3, check = %d\n",check);
    stampaSet(set,&stampaint);

    check = sset_member(set, &n_[5]);
    printf("\nChecking member 5, check = %d\n",check);
    check = sset_member(set, &n_[1]);
    printf("\nChecking member 1, check = %d\n",check);
    check = sset_member(set, &n_[7]);
    printf("\nChecking member 7, check = %d\n",check);
    check = sset_member(set, &n_[8]);
    printf("\nChecking member 8, check = %d\n",check);

    check = sset_remove(set,&n_[8]);
    printf("\nRemoving 8, check = %d\n",check);
    stampaSet(set,&stampaint);

    check = sset_remove(set,&n_[1]);
    printf("\nRemoving 1 again, check = %d\n",check);
    stampaSet(set,&stampaint);

    check = sset_remove(set,&n_[7]);
    printf("\nRemoving 7, check = %d\n",check);
    stampaSet(set,&stampaint);

    check = sset_remove(set,&n_[5]);
    printf("\nRemoving 5, check = %d\n",check);
    stampaSet(set,&stampaint);

    check = isEmptySSet(set);
    printf("\nChecking isEmpty, check = %d\n",check);

    check = sset_add(set,&n_[5]);
    printf("\nAdding 5, check = %d\n",check);
    stampaSet(set,&stampaint);

    check = isEmptySSet(set);
    printf("\nChecking isEmpty, check = %d\n",check);

    check = sset_remove(set,&n_[5]);
    printf("\nRemoving 5, check = %d\n",check);
    stampaSet(set,&stampaint);

    printf("\nDestroying set\n");
    dsSSet(&set);
    stampaSet(set,&stampaint);

    /* second part: set operations */
    puts("\n\n*** second part: operations on set pairs");
    
    
    printf("\nCreating s1\n");
    s1 = mkSSetvi(5, &n_[0], &n_[2], &n_[4], &n_[5], &n_[8]);
    stampaSet(s1,&stampaint);
    
    printf("\nCreating s2\n");
    s2 = mkSSetvi(5, &n_[0], &n_[2], &n_[4], &n_[5], &n_[8]);
    stampaSet(s2,&stampaint);

    check = sset_equals(s2,s1);
    printf("\nequals, check = %d\n",check);

    check = sset_subseteq(s1,s2);
    printf("\nsubseteq, check = %d\n",check);
    check = sset_subset(s1,s2);
    printf("\nsubset, check = %d\n",check);
    dsSSet(&s1);
    dsSSet(&s2);
    printf("\nDestroyed s1,s2\n");
    check = sset_equals(s2,s1);
    printf("\nequals, check = %d\n",check);
    check = sset_subseteq(s1,s2);
    printf("\nsubseteq, check = %d\n",check);

    printf("\nCreating s1\n");
    s1 = mkSSetvi(7, &n_[3], &n_[4], &n_[5], &n_[6], &n_[7], &n_[0], &n_[1]);
    stampaSet(s1,&stampaint);
    
    printf("\nCreating s2\n");
    s2 = mkSSetvi(5, &n_[0], &n_[1], &n_[2], &n_[9], &n_[4]); 
    stampaSet(s2,&stampaint);
    
    check = sset_equals(s1,s2);
    printf("\nequals, check = %d\n",check);
    
    set = sset_subtraction(s1,s2);
    printf("\nsubtraction s1-s2\n");
    stampaSet(set,&stampaint);
    dsSSet(&set);

    set = sset_intersection(s1,s2);
    printf("\nintersection s1 and s2\n");
    stampaSet(set,&stampaint);
    dsSSet(&set);

    set = sset_union(s1,s2);
    printf("\nunion s1 + s2\n");
    stampaSet(set,&stampaint);
    dsSSet(&set);

    dsSSet(&s1);
    dsSSet(&s2);

    return 0;
}