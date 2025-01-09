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
    char inputBuffer[10];
    for (int i = 0; i < 3; i++) {
        read(from_server, inputBuffer, 1); //server stalls client
        printf("Enter rock, paper, or scissors: ");
        fgets(inputBuffer, sizeof(inputBuffer), stdin);
        write(to_server, inputBuffer, sizeof(inputBuffer));
    }
    close(to_server);
    close(from_server);
}
