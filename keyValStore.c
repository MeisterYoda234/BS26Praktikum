#include <stdio.h>
#include <string.h>
#include "keyValStore.h"
#include "sub.h"

///
/// @param key Key aus dem Socket Aufruf
/// @param value Value aus dem Socket Aufruf
/// @param store Array mit allen Key/Value paaren
/// @param len Array länge
/// @return 1: Erfolgreich; 0: Kein Key gefunden
int put(char *key, char *value, keyValStore *store, int len) {
    for (int i = 0; i < len; i++) {
        if (strcmp(key, store[i].key) == 0) {
            strncpy(store[i].value, value, 254);
            store[i].value[254] = '\0';
            return 1;
        }
    }

    return 0;
}

///
/// @param key Key aus dem Socket Aufruf
/// @param store Array mit allen Key/Value paaren
/// @param len  Array länge
/// @return Value falls existent sonst Fehlermeldung
char *get(char *key, keyValStore *store, int len) {
    for (int i = 0; i < len; i++) {
        if (strcmp(key, store[i].key) == 0) {
            return store[i].value;
        }
    }
    return "key_nonexistent";
}

///
/// @param key Key aus em Socket Aufruf
/// @param store Array mit allen Key/Value paaren
/// @param len Array länge
/// @return Erfolgreiches löchen: key_delete; Key existiert nicht im Speicher: key_nonexistent
char *del(char *key, keyValStore *store, int len) {
    for (int i = 0; i < len; i++) {
        if (strcmp(key, store[i].key) == 0) {
            store[i].value[0] = '\0';
            return "key_deleted";
        }
    }
    return "key_nonexistent";
}
