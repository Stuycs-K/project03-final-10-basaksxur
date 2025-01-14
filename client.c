#include "networking.h"
#include "server_util.h"


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
    char usernameBuff[20];
    printf("Enter username (case sensitive): ");
    fflush(stdout);
    fgets(usernameBuff, sizeof(usernameBuff), stdin);
    write(to_server, usernameBuff, strlen(usernameBuff)+1);
    /*
    if (loadUser(usernameBuff, ??)) {
        printf("Welcome back %s. Your progress has been loaded and will be saved.\n", usernameBuff);
    }
    else {
        createUser(usernameBuff, ??);
        printf("Hello %s. Your new profile has been created and progress will be saved.\n", usernameBuff);
    }
    */
    char welcomeMessage[200];
    read(from_server, welcomeMessage, sizeof(welcomeMessage));
    printf("%s", welcomeMessage);
    for (int i = 0; i < 3; i++) {
        char connectBuffer[10];
        //sleep(1);
        //printf("about to read\n"); //DEBUG
        //read(from_server, connectBuffer, 1); //server stalls client
        printf("---Round %d---\n", i+1);
        printf("Enter rock, paper, or scissors (lowercase): "); //we can add a toupper/tolower later if possible
        fflush(stdout);
        char inputBuffer[10];
        fgets(inputBuffer, sizeof(inputBuffer), stdin);
        write(to_server, inputBuffer, strlen(inputBuffer)+1);
        //sleep(3);
        char receivedBuffer[100];
        read(from_server, receivedBuffer, sizeof(receivedBuffer));
        printf("%s\n", receivedBuffer);
    }
    sleep(1);
    char finalBuffer[30];
    read(from_server, finalBuffer, sizeof(finalBuffer));
    printf("%s\n", finalBuffer);
    close(to_server);
    close(from_server);
}
