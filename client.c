#include "networking.h"

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

int main() {
    signal(SIGINT, sighandler);
    signal(SIGPIPE, sighandler);
    from_server = client_handshake( &to_server );
    //greetings to user
    //user login/create account? ("accounts" would just be sign in with username)
    //le game
    for (int i = 0; i < 3; i++) {
        char inputBuffer[10];
        read(from_server, inputBuffer, 1); //server stalls client
        printf("Round %d...\n", i);
        printf("Enter rock, paper, or scissors: ");
        fflush(stdout);
        fgets(inputBuffer, sizeof(inputBuffer), stdin);
        write(to_server, inputBuffer, sizeof(inputBuffer));

        char receivedBuffer[100];
        read(from_server, receivedBuffer, sizeof(receivedBuffer));
        printf("%s\n"receivedBuffer);
    
    }
    close(to_server);
    close(from_server);
}
