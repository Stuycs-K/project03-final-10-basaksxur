#include "networking.h"
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int printerror(){
    printf("Error: [%d] (%s)\n", errno, strerror(errno));
    return 0;
}

int server_setup(){
    if (access(WKP, F_OK) == 0) {
        if (unlink(WKP) == -1) {
            printerror();
            exit(EXIT_FAILURE);
        }
    }
    if (mkfifo(WKP, 0666) == -1) {
        printerror();
        exit(EXIT_FAILURE);
    }
    chmod(WKP, 0666);
    int from_client = open(WKP, O_RDONLY);
    if (from_client == -1) {
        printerror();
        exit(EXIT_FAILURE);
    }
    if (unlink(WKP) == -1) {
        printerror();
        exit(EXIT_FAILURE);
    }
    return from_client;
}

int server_handshake(int *to_client){
    int from_client = server_setup();
    server_handshake_half(to_client, from_client);
    return from_client;
}

int client_handshake(int *to_server){
    *to_server = open(WKP, O_WRONLY);
    if (*to_server == -1) {
        printf("1\n");
        printerror();
        exit(EXIT_FAILURE);
    }
    char PP[HANDSHAKE_BUFFER_SIZE];
    sprintf(PP, "%d", getpid());
    if (access(PP, F_OK) == 0) {
        if (unlink(PP) == -1) {
            printerror();
            printf("2\n");
            exit(EXIT_FAILURE);
        }
    }
    if (mkfifo(PP, 0666) == -1) {
        printerror();
        printf("3\n");
        exit(EXIT_FAILURE);
    }
    chmod(PP, 0666);
    write(*to_server, PP, HANDSHAKE_BUFFER_SIZE);
    int downstream = open(PP, O_RDONLY);
    int SYN_ACK;
    read(downstream, &SYN_ACK, sizeof(int));
    if (unlink(PP) == -1) {
        printerror();
        exit(EXIT_FAILURE);
    }
    int ACK = SYN_ACK + 1;
    write(*to_server, &ACK, sizeof(int));
    return downstream;
}

int server_handshake_half(int *to_client, int from_client){
    char downstream[HANDSHAKE_BUFFER_SIZE];
    read(from_client, &downstream, HANDSHAKE_BUFFER_SIZE);

    *to_client = open(downstream, O_WRONLY);
    srand(time(NULL));
    int SYN_ACK = rand();
    write(*to_client, &SYN_ACK, sizeof(int));

    int ACK;
    read(from_client, &ACK, sizeof(int));
    if (ACK != SYN_ACK + 1) {
        printerror();
        exit(EXIT_FAILURE);
    }
    return *to_client;
}
