#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <time.h>
#include <ctype.h>

#ifndef NETWORKING_H
#define NETWORKING_H
#define WKP "setuprps"

#define HANDSHAKE_BUFFER_SIZE 10
#define BUFFER_SIZE 1000
#define MAX_CLIENTS 2

int printerror();

int server_handshake(int *to_client);
int client_handshake(int *to_server);

//for basic & persistent servers
int server_handshake_half(int *to_client, int from_client);

//for forking server
int server_setup();

#endif
