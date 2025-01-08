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

struct SharedMemory {
    char input1[100];
    char input2[100];
    int connectedready1;
    int connectedready2;
    int moveready1;
    int moveready2;
    char result[200];
};

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
        printf("A client has disconnected. The game is exiting...\n");
        exit(0);
    } else if (signo == SIGPIPE) {
        connectedready1 = 0;
        connectedready2 = 0;
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
    SharedMemory * database; //WE SHOULD MAKE A SHARED MEMORY STRUCT TO STORE ALL INPUTS
    shmd = shmget(KEY, sizeof(SharedMemory), IPC_CREAT | 0600);
    if (shmd == -1) {
        printerror();
    }
    database = (SharedMemory *) shmat(shmid, 0, 0);
    if (database == (SharedMemory *) -1) {
        printerror();
    }
    memset(database, 0, sizeof(SharedMemory));
    //printf("shmd: %d\n", shmd);
    pid_t pid1 = fork();
    if (pid1 == 0) {
        to_client1 = server_handshake_half(&to_client, from_client);
        connectedready1 = 1;
        while (connectedready2) {
            
        
        }
        close(to_client1);
        exit(0);
    }
    if (pid2 == 0) {
        to_client2 = server_handshake_half(&to_client, from_client);
        connectedready2 = 1;
        while (connectedready1) {
            
            
        
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