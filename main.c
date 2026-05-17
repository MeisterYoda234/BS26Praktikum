#include <stdio.h>
#include "keyValStore.h"
#include "sub.h"

int main(void) {
    /*
    // Abfrangen einer Key/Value Anzahl und erstellen dieser
    printf("Wie viele Key/Value Stores sollen angelegt werden?");
    int count;
    scanf("%i", &count);
    keyValStore *store = createKeyStore(count);

    // Debug Ausgabe zum Anzeigen das, dass erstellen erfolgreich ist
    for (int i = 0; i < count; i++) {
        printf("Element %d: key=%s, value=%s\n",
               i,
               store[i].key,
               store[i].value);
    }

    */
    createSocketVerbindung();


    return 0;


}
