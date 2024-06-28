#include "contact.h"
#include <stdio.h>
#include <strings.h>

// strcmp | strcasecmp
_Bool contactEq(Contact c1, Contact c2) {
    return strcasecmp(c1.name, c2.name) == 0 &&
           strcasecmp(c1.surname, c2.surname) == 0;
}
_Bool contactEqEff(const Contact const *pc1, const Contact const *pc2) {
    return strcasecmp(pc1 -> name, pc2 -> name) == 0 &&
           strcasecmp(pc1 -> surname, pc2 -> surname) == 0;
}
int contactCmp(Contact c1, Contact c2) {
    // n1 = "christian", n2 = "nicholas"
    int ord1 = strcasecmp(c1.surname, c2.surname);
    if (ord1 == 0) {
        int ord2 = strcasecmp(c1.name, c2.name);
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
int contactCmpEff(const Contact const *pc1, const Contact const *pc2) {
    int ord1 = strcasecmp(pc1 -> surname, pc2 -> surname);
    if (ord1 == 0) {
        int ord2 = strcasecmp(pc1 -> name, pc2 -> name);
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