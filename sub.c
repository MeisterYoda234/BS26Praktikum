#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "sub.h"
#include <string.h>

#include "keyValStore.h"

keyValStore *createKeyStore(const int count) {
    keyValStore *store = calloc(count, sizeof(struct keyValStore));
    if (store == NULL) {
        return NULL;
    }
    return store;
}

// Liest die Eingabe der Clients, die mit dem Server verbunden sind!
void clientEingabeLesen(int connection_fd) {
    // Buffer für die Client eingabe wird erstellt!
        char recv_buffer[1024];
        // Buffer für die gereinigte Client eingabe (ohne /r und /n) wird erstellt!
        char line_buffer[2048];
        // Index für den "line_buffer" wird erstellt (enthält wie viele Zeichen in einer Zeile sind!)
        int line_len = 0;

        while (1)
        {
            // Die eingabe des Clients wird gelesen und in "recv_buffer" gespeichert!
            int gelesendeBytes = recv(connection_fd, recv_buffer, sizeof(recv_buffer), 0);

            // Prüft, ob etwas gelesen wurde (wenn "etwas leeres" abegeschickt wird beinhaltet dies trotzdem Bytes!)!
            if (gelesendeBytes <= 0)
            {
                printf("Client getrennt\n");
                break;
            }
            // Verarbeitet dem Inhalt der im Buffer steht!
            for (int i = 0; i < gelesendeBytes; i++)
            {
                // Geht jedes Zeichen im Buffer durch!
                char c = recv_buffer[i];

                // CR/LF NICHT in den Buffer aufnehmen
                if (c == '\r')
                    continue;
                //Prüft ob c Zeilenumbruch enthält
                if (c != '\n')
                {
                    // Prüft, ob noch Platz im line_buffer ist!
                    if (line_len < (int)sizeof(line_buffer) - 1)
                    {
                        // Schreibt nur die reine Eingabe des Clients in den "line_Buffer"
                        line_buffer[line_len++] = c;
                    }
                    continue;
                }

                // Die Zeile abgeschlossen (bei '\n')
                line_buffer[line_len] = '\0';

                // Ausgabe was empfangen wurde vom Client in die Server Console!
                printf("Empfangen: %s\n", line_buffer);

                // Der Index des Zeilenbuffers wird "gereinigt" für die nächste Zeile!
                line_len = 0;
            }

            // Schutz gegen Buffer Overflow! Falls eine Zeile zu groß für den Buffer ist!
            if (line_len >= (int)sizeof(line_buffer) - 1)
            {
                printf("Warnung: Zeile zu lang -> reset\n");
                line_len = 0;
            }
        }
}

// Variable für den Datei-Deskriptors des Sever-Sockets und der Client-Verbindung wird deklariert!
int socket_fd;
int connection_fd;
// Erstellt einen Server-Socket, und baut über diesen Socket eine Verbindung mit Clients auf!
void createSocketVerbindung()
{
    //Ein Socket, der mit IPV4-Adressen kommuniziert und TCP-Protokolle verwenden kann wird erstellt!
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    // Hier wird geprüft, ob der socket erstellt wurde oder nicht!
    if (socket_fd < 0)
    {
        printf("Socket Fehler\n");
        // Funktion createSocketVerbindung wird beendet!
        return;
    }

    // Es wird eine Struktur des Typs sockaddr_in erstellt und alle Inhalte dieser Struktur werden auf den Wert 0 gesetzt.
    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));

    // Hier werdem doe Strukturfelder der Struktur "server" mit Inhalten versehen!
    // Adressfamilie: IPV4
    server.sin_family = AF_INET;
    // Server akzeptiert Verbindungen an allen Netzwerkschnittstellen
    server.sin_addr.s_addr = INADDR_ANY;
    // Server verbindet sich über den Port: 5678
    server.sin_port = htons(5678);
    // Hier wird der Socket mit der IP-Adresse (INADDR_ANY) verknüpft! Und es wird eine Fehlermeldung ausgegeben, falls dies nicht funktioniert hat
    if (bind(socket_fd, (struct sockaddr*)&server, sizeof(server)) < 0)
    {
        printf("Bind Fehler\n");
        return;
    }
    // Es wird festgelegt, dass der Socket nun Verbindungsanfragen akzeptiert und davon maximal 5 gleichzeitig (Es wird also eine Warteschlange gebaut)!
    if (listen(socket_fd, 5) < 0)
    {
        printf("Listen Fehler\n");
        return;
    }
    // Server ist bereit sich mit einem Client zu verbinden
    printf("Server läuft...\n");
    // Eine Endlosschleife die bis zum Beenden des Programms auf eine Verbind wartet!
    while (1)
    {
        // Blockiert den rest des Programms und wartet bis sich ein Client verbindet!
        connection_fd = accept(socket_fd, NULL, NULL);
        // Prüfen, ob die Verbindung zum Client funktioniert hat!
        if (connection_fd < 0)
        {
            printf("Accept Fehler\n");
            continue;
        }
        // Konsolen Nachricht, dass sich ein Client verbunden hat!
        printf("Client verbunden\n");

        clientEingabeLesen(connection_fd);

        // Verbindung zum Client wird geschlossen!
        close(connection_fd);
    }
    // Server-Socket wird geschlossen!
    close(socket_fd);
}


