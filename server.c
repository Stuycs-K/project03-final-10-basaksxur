#include "networking.h"
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

#define KEY 28964218


int to_client1 = -1;
int from_client1 = -1;
int to_client2 = -1;
int from_client2 = -1;
int connected = 0;

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
    } else if (signo == SIGPIPE) {
        connected = 0;
    }
}

int main(){
    srand(time(NULL));
    signal(SIGINT, sighandler);
    signal(SIGPIPE, sighandler);

    printf("Looking for client...\n");
    from_client1 = server_setup();
    printf("Client 1 found.\n");
    from_client2 = server_setup();
    printf("Client 2 found. Both clients connected.\n");
    connected = 1;
    pid_t pid1 = fork();
    int shmd;
    int *playercount; //WE SHOULD MAKE A SHARED MEMORY STRUCT TO STORE ALL INPUTS
    shmd = shmget(KEY, sizeof(int), IPC_CREAT | 0600);
    if (shmd == -1) {
        printerror();
    }
    playercount = (int *) shmat(shmid, 0, 0);
    if (playercount == (int *) -1) {
        printerror();
    }
    *playercount = 0;
    //printf("shmd: %d\n", shmd);
    pid_t pid1 = fork();
    if (pid1 == 0) {
        to_client1 = server_handshake_half(&to_client, from_client);
        while (connected) {
            
            /*
            char userinput[100];
            printf("Enter rock, paper, or scissor: ");
            fflush(stdout);
            fgets(userinput, sizeof(userinput), stdin);
            printf("You entered: %s\n", userinput);
            */

            //ABOVE NEEDS TO BE IMPLEMENTED ON CLIENT SIDE, NOT SERVER.
        
        }
        close(to_client1);
        exit(0);
    }
    if (pid2 == 0) {
        to_client2 = server_handshake_half(&to_client, from_client);
        while (connected) {
            
            /*
            char userinput[100];
            printf("Enter rock, paper, or scissor: ");
            fflush(stdout);
            fgets(userinput, sizeof(userinput), stdin);
            printf("You entered: %s\n", userinput);
            */

            //ABOVE NEEDS TO BE IMPLEMENTED ON CLIENT SIDE, NOT SERVER.
        
        }
        close(to_client2);
        exit(0);
    }
    while (connected) {
        //game logic
    }

    shmdt(shm);
    shmctl(shmid, IPC_RMID, NULL);
    close(from_client1);
    close(from_client2);
}