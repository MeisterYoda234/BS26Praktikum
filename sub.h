#ifndef BS26PRAKTIKUM_SUB_H
#define BS26PRAKTIKUM_SUB_H
#include <string.h>

struct keyValStore {
    char key[255];
    char value[255];
} typedef keyValStore;

keyValStore *createKeyStore(int count);

void createSocketVerbindung();
void readClient();

struct commandKeyVal {
    char befehl[255];
    char key[255];
    char value[255];

} typedef commandKeyVal;

#endif //BS26PRAKTIKUM_SUB_H
