#include "networking.h"

int to_client1 = -1;
int from_client1 = -1;
int to_client2 = -1;
int from_client2 = -1;

static void sighandler(int signo) {
    if (signo == SIGINT) {
        if (to_client1 != -1) {
            close(to_client1);
        }
        if (from_client1 != -1) {
            close(from_client1);
        }
        if (to_client2 != -1) {
            close(to_client2);
        }
        if (from_client2 != -1) {
            close(from_client2);
        }
        unlink(WKP);
        exit(0);
    }
}

int main() {
    srand(time(NULL));
    signal(SIGINT, sighandler);
    while (1) {
        printf("Looking for client 1\n");
        from_client1 = server_setup();
        printf("Client 1 found\n");
        printf("Looking for client 2\n");
        from_client2 = server_setup();
        printf("Client 2 found\n");

        if (fork() == 0) {
            //game logic, can communicate with 2 clients
            to_client1 = server_handshake_half(&to_client1, from_client1);
            to_client2 = server_handshake_half(&to_client2, from_client2);
            char client1Input[10];
            char client2Input[10];
            for (int i = 0; i < 3; i++) {
                //stop stalling clients
                printf("New round\n"); //DEBUG
                //write(to_client1, "a", 1);
                //write(to_client2, "a", 1);
                //printf("got past write\n"); //DEBUG
                read(from_client1, client1Input, sizeof(client1Input));
                read(from_client2, client2Input, sizeof(client2Input));
                printf("got past read inputs\n"); //DEBUG
                if (client1Input[strlen(client1Input) - 1] == '\n') { //to make comparison smoother
                    client1Input[strlen(client1Input) - 1] = '\0';
                }
                if (client2Input[strlen(client2Input) - 1] == '\n') { //to make comparison smoother
                    client2Input[strlen(client2Input) - 1] = '\0';
                }

                printf("Client 1 played %s, client 2 played %s.\n", client1Input, client2Input);
                char resultbuff[100];
                if (!strcmp(client1Input, client2Input)) {
                    sprintf(resultbuff, "Both clients chose %s. Round skipped.\n", client1Input);
                }
                else {
                    if (!strcmp(client1Input, "rock")) {
                        if (!strcmp(client2Input, "paper")) { //client 2 wins
                            sprintf(resultbuff, "Client 1 chose %s. Client 2 chose %s. Client 2 wins.\n", client1Input, client2Input);
                        }
                        else if (!strcmp(client2Input, "scissors")) { //client 1 wins
                            sprintf(resultbuff, "Client 1 chose %s. Client 2 chose %s. Client 1 wins.\n", client1Input, client2Input);
                        }
                        else {
                            sprintf(resultbuff, "Client 2 chose an illegal move: %s. Round skipped.\n", client2Input);
                        }
                    }
                    else if (!strcmp(client1Input, "paper")) {
                        if (!strcmp(client2Input, "rock")) { //client 1 wins
                            sprintf(resultbuff, "Client 1 chose %s. Client 2 chose %s. Client 1 wins.\n", client1Input, client2Input);
                        }
                        else if (!strcmp(client2Input, "scissors")) { //client 2 wins
                            sprintf(resultbuff, "Client 1 chose %s. Client 2 chose %s. Client 2 wins.\n", client1Input, client2Input);
                        }
                        else {
                            sprintf(resultbuff, "Client 2 chose an illegal move: %s. Round skipped.\n", client2Input);
                        }
                    }
                    else if (!strcmp(client1Input, "scissors")) {
                        if (!strcmp(client2Input, "paper")) { //client 1 wins
                            sprintf(resultbuff, "Client 1 chose %s. Client 2 chose %s. Client 1 wins.\n", client1Input, client2Input);
                        }
                        else if (!strcmp(client2Input, "rock")) { //client 2 wins
                            sprintf(resultbuff, "Client 1 chose %s. Client 2 chose %s. Client 2 wins.\n", client1Input, client2Input);
                        }
                        else {
                            sprintf(resultbuff, "Client 2 chose an illegal move: %s. Round skipped.\n", client2Input);
                        }
                    }
                    else {
                        sprintf(resultbuff, "Client 1 chose an illegal move: %s. Round skipped.\n", client1Input);
                    }
                }

                write(to_client1, resultbuff, strlen(resultbuff));
                write(to_client2, resultbuff, strlen(resultbuff));
            }
            close(to_client1);
            close(from_client1);
            close(to_client2);
            close(from_client2);
            exit(0);
        }
    }
}