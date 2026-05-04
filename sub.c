#include <stdio.h>
#include <stdlib.h>
#include "sub.h"

keyValStore *createKeyStore(const int count) {
    keyValStore *store = calloc(count, sizeof(struct keyValStore));
    if (store == NULL) {
        return NULL;
    }
    return store;
}
