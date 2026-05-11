#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "sub.h"

keyValStore *createKeyStore(const int count) {
    keyValStore *store = calloc(count, sizeof(struct keyValStore));
    if (store == NULL) {
        return NULL;
    }
    return store;
}

// implementierung von Sockets!
void createSocket() {
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    printf("Ein Socket wurde erstellt! %d", socket_fd);
}


