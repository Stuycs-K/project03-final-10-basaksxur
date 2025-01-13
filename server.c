#include "networking.h"
#include "server_util.h"

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
    int dataFile = open("userdata.dat", O_RDWR, 0);
    while (1) {
        printf("Looking for client 1\n");
        from_client1 = server_setup();
        printf("Client 1 found\n");
        printf("Looking for client 2\n");
        from_client2 = server_setup();
        printf("Client 2 found\n");

        if (fork() == 0) {
            int score1 = 0;
            int score2 = 0;
            //game logic, can communicate with 2 clients
            to_client1 = server_handshake_half(&to_client1, from_client1);
            to_client2 = server_handshake_half(&to_client2, from_client2);

            char client1User[100];
            char client2User[100];
            struct user * client1;
            struct user * client2;
            read(from_client1, client1User, sizeof(client1User));
            read(from_client2, client2User, sizeof(client2User));
            //USER 1
            char client1UserConf[200];
            if ((client1 = loadUser(client1User, dataFile))) {
                sprintf(client1UserConf, "Welcome back %s\n", printUser(client1));
            }
            else {
                client1 = createUser(client1User, dataFile);
                sprintf(client1UserConf, "Your new profile has been created:%s\n", printUser(client1));
            }
            write(to_client1, client1UserConf, strlen(client1UserConf)+1);
            //USER 2
            char client2UserConf[200];
            if ((client2 = loadUser(client2User, dataFile))) {
                sprintf(client2UserConf, "Welcome back %s\n", printUser(client2));
            }
            else {
                client2 = createUser(client2User, dataFile);
                sprintf(client2UserConf, "Your new profile has been created:%s\n", printUser(client2));
            }
            write(to_client2, client2UserConf, strlen(client2UserConf)+1);
            for (int i = 0; i < 3; i++) {
                char client1Input[10];
                char client2Input[10];
                printf("New round\n"); //DEBUG
                //printf("got past write\n"); //DEBUG
                read(from_client1, client1Input, sizeof(client1Input));
                read(from_client2, client2Input, sizeof(client2Input));
                //printf("got past read inputs\n"); //DEBUG
                if (client1Input[strlen(client1Input) - 1] == '\n') { //to make comparison smoother
                    client1Input[strlen(client1Input) - 1] = '\0';
                }
                if (client2Input[strlen(client2Input) - 1] == '\n') { //to make comparison smoother
                    client2Input[strlen(client2Input) - 1] = '\0';
                }

                printf("Client 1 played %s, client 2 played %s.\n", client1Input, client2Input);
                char resultbuff[200];
                if (!strcmp(client1Input, client2Input)) {
                    sprintf(resultbuff, "Both clients chose %s. Round skipped.\n", client1Input);
                }
                else {
                    if (!strcmp(client1Input, "rock")) {
                        if (!strcmp(client2Input, "paper")) { //client 2 wins
                            score2++;
                            sprintf(resultbuff, "%s chose %s. %s chose %s. %s wins.\n", client1User, client1Input, client2User, client2Input, client2User);
                        }
                        else if (!strcmp(client2Input, "scissors")) { //client 1 wins
                            score1++;
                            sprintf(resultbuff, "%s chose %s. %s chose %s. %s wins.\n", client1User, client1Input, client2User, client2Input, client1User);
                        }
                        else {
                            sprintf(resultbuff, "%s chose an illegal move: %s. Round skipped.\n", client2User, client2Input);
                        }
                    }
                    else if (!strcmp(client1Input, "paper")) {
                        if (!strcmp(client2Input, "rock")) { //client 1 wins
                            score1++;
                            sprintf(resultbuff, "%s chose %s. %s chose %s. %s wins.\n", client1User, client1Input, client2User, client2Input, client1User);
                        }
                        else if (!strcmp(client2Input, "scissors")) { //client 2 wins
                            score2++;
                            sprintf(resultbuff, "%s chose %s. %s chose %s. %s wins.\n", client1User, client1Input, client2User, client2Input, client2User);
                        }
                        else {
                            sprintf(resultbuff, "%s chose an illegal move: %s. Round skipped.\n", client2User, client2Input);
                        }
                    }
                    else if (!strcmp(client1Input, "scissors")) {
                        if (!strcmp(client2Input, "paper")) { //client 1 wins
                            score1++;
                            sprintf(resultbuff, "%s chose %s. %s chose %s. %s wins.\n", client1User, client1Input, client2User, client2Input, client1User);
                        }
                        else if (!strcmp(client2Input, "rock")) { //client 2 wins
                            score2++;
                            sprintf(resultbuff, "%s chose %s. %s chose %s. %s wins.\n", client1User, client1Input, client2User, client2Input, client2User);
                        }
                        else {
                            sprintf(resultbuff, "%s chose an illegal move: %s. Round skipped.\n", client2User, client2Input);
                        }
                    }
                    else {
                        sprintf(resultbuff, "%s chose an illegal move: %s. Round skipped.\n", client1User, client1Input);
                    }
                }

                write(to_client1, resultbuff, strlen(resultbuff)+1);
                write(to_client2, resultbuff, strlen(resultbuff)+1);
            }
            char winbuff[30];
            sprintf(winbuff, "You win.\n");
            char losebuff[30];
            sprintf(losebuff, "You lose.\n");
            if (score1>score2) { //Client 1 wins
                write(to_client1, winbuff, strlen(winbuff)+1);
                write(to_client2, losebuff, strlen(losebuff)+1);
                updateStats(client1, 1);
                updateStats(client2, 0);
            }
            else if (score2>score1) { //Client 2 wins
                write(to_client1, losebuff, strlen(losebuff)+1);
                write(to_client2, winbuff, strlen(winbuff)+1);
                updateStats(client2, 1);
                updateStats(client1, 0);
            }
            else { //neither wins
                char neitherbuff[30];
                sprintf(neitherbuff, "Neither player won.\n");
                write(to_client1, neitherbuff, strlen(neitherbuff)+1);
                write(to_client2, neitherbuff, strlen(neitherbuff)+1);
                updateStats(client2, 0);
                updateStats(client2, 0);
            }
            close(to_client1);
            close(from_client1);
            close(to_client2);
            close(from_client2);
            exit(0);
        }
    }
}
