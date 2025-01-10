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
        char connectBuffer[10];
        printf("NEW ROUND\n"); //DEBUG
        sleep(1);
        read(from_server, connectBuffer, 1); //server stalls client
        printf("Round %d...\n", i+1);
        printf("Enter rock, paper, or scissors (lowercase): "); //we can add a toupper/tolower later if possible
        fflush(stdout);
        char inputBuffer[10];
        fgets(inputBuffer, sizeof(inputBuffer), stdin);
        write(to_server, inputBuffer, sizeof(inputBuffer));
        sleep(3);
        char receivedBuffer[100];
        read(from_server, receivedBuffer, sizeof(receivedBuffer));
        printf("%s\n",receivedBuffer);
        printf("test %d\n", i+1); //DEBUG
    
    }
    close(to_server);
    close(from_server);
}
