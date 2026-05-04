#ifndef BS26PRAKTIKUM_KEYVALSTORE_H
#define BS26PRAKTIKUM_KEYVALSTORE_H
#include "sub.h"

int put(char *key, char *value, keyValStore *store, int len);

char* get(char *key, keyValStore *store, int len);

char* del(char *key, keyValStore *store, int len);

#endif //BS26PRAKTIKUM_KEYVALSTORE_H
