#include "networking.h"
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int to_server = -1;
int from_server = -1;

static void sighandler(int signo) {
    if (signo == SIGINT) {
        if (to_server != -1) {
            close(to_server);
        }
        if (from_server != -1) {
            close(from_server);
        }
        exit(0);
    }
}

int main(){
    signal(SIGINT, sighandler);
    signal(SIGPIPE, sighandler);
    from_server = client_handshake( &to_server );
    printf("Welcome to Rock Paper Scissors! Connected to server, waiting to match against another client...\n");
    //wait for other client to connect
    for (int i = 0; i < 3; i++) {
        char lineBuffer[100];
        printf("Enter rock, paper, or scissors (r, p, s): ");
        fflush(stdout);
        fgets(lineBuffer, sizeof(lineBuffer), stdin);
        printf("You entered: %s\n", lineBuffer);
        write(to_server, lineBuffer, sizeof(lineBuffer));
        read(from_server, lineBuffer, sizeof(lineBuffer)); // result
        printf("%s\n", lineBuffer);
    }

    close(to_server);
    close(from_server);
}