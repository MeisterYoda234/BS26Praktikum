#ifndef BS26PRAKTIKUM_SUB_H
#define BS26PRAKTIKUM_SUB_H

struct keyValStore {
    char key[255];
    char value[255];
} typedef keyValStore;

keyValStore *createKeyStore(int count);

#endif //BS26PRAKTIKUM_SUB_H
