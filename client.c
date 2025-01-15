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

    char usernameBuff[20];
    printf("Enter username (case sensitive): ");
    fflush(stdout);
    fgets(usernameBuff, sizeof(usernameBuff), stdin);
    int userwrite = write(to_server, usernameBuff, strlen(usernameBuff)+1);
    if (userwrite == -1) {
        printf("Server likely disconnected, game shutting down. No stats logged.\n");
        printerror();
        close(to_server);
        close(from_server);
        exit(0);
    }
    char welcomeMessage[200];
    int wcread = read(from_server, welcomeMessage, sizeof(welcomeMessage));
    if (wcread == -1) {
        printf("Reading welcome message failed.\n");
        printerror();
        close(to_server);
        close(from_server);
        exit(0);
    }
    printf("%s", welcomeMessage);
    char wcsubstring[14];
    strncpy(wcsubstring, welcomeMessage, 13);
    wcsubstring[13] = '\0';
    if (!strcmp(wcsubstring, "{DISCONNECT}:")) {
        close(to_server);
        close(from_server);
        exit(0);
    }
    for (int i = 0; i < 3; i++) {
        char connectBuffer[10];
        //sleep(1);
        //read(from_server, connectBuffer, 1); //server stalls client
        printf("---Round %d---\n", i+1);
        printf("Enter rock, paper, or scissors (case insensitive): ");
        fflush(stdout);
        char inputBuffer[10];
        fgets(inputBuffer, sizeof(inputBuffer), stdin);
        int count = 0;
        while (inputBuffer[count]){
            inputBuffer[count] = tolower(inputBuffer[count]);
            count++;
        }
        int movewrite = write(to_server, inputBuffer, strlen(inputBuffer)+1);
        if (movewrite == -1) {
            printf("Server likely disconnected, game shutting down. No stats logged.\n");
            printerror();
            close(to_server);
            close(from_server);
            exit(0);
        }
        //sleep(3);
        char receivedBuffer[100];
        int resultread = read(from_server, receivedBuffer, sizeof(receivedBuffer));
        if (resultread == -1) {
            printf("Reading move logic failed.\n");
            printerror();
            close(to_server);
            close(from_server);
            exit(0);
        }
        printf("%s\n", receivedBuffer);
        char substring[14];
        strncpy(substring, receivedBuffer, 13);
        substring[13] = '\0';
        if (!strcmp(substring, "{DISCONNECT}:")) {
            close(to_server);
            close(from_server);
            exit(0);
        }
    }
    sleep(1);
    char finalBuffer[30];
    int finalread = read(from_server, finalBuffer, sizeof(finalBuffer));
    if (finalread == -1) {
        printf("Reading final message failed.\n");
        printerror();
        close(to_server);
        close(from_server);
        exit(0);
    }
    printf("%s\n", finalBuffer);
    close(to_server);
    close(from_server);
}
