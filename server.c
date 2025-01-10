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
                write(to_client1, "e", 1);
                write(to_client2, "e", 1);

                read(from_client1, client1Input, sizeof(client1Input));
                read(from_client2, client2Input, sizeof(client2Input));
                printf("Client 1 played %s, client 2 played %s\n", client1Input, client2Input);

                if (client1Input[strlen(client1Input) - 1] == '\n') { //to make comparison smoother
                    client1Input[strlen(client1Input) - 1] = '\0';
                }
                if (client2Input[strlen(client2Input) - 1] == '\n') { //to make comparison smoother
                    client2Input[strlen(client2Input) - 1] = '\0';
                }

                if (!strcmp(client1Input, client2Input)) {
                    char resultbuff[100];
                    sprintf(resultbuff, "Both clients chose %s. Round not counted.", client1Input);
                    write(to_client1, resultbuff, strlen(resultbuff));
                    write(to_client2, resultbuff, strlen(resultbuff));
                }

                if ()
                char loserbuff[100];
                sprintf(loserbuff, "Client %d ", age, height);
            }
            close(from_client1);
            close(from_client2);
            close(to_client1);
            close(to_client2);
            exit(0);
        }
    }
}