#ifndef SERVER_UTIL_H
#define SERVER_UTIL_H
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
struct user {
    char username[20];
    int rating;
    int gamesPlayed;
    int gamesWon;
    int gamesLost;
    char rank[10];
    int connected;
};
struct user *createUser(char username[], int dataFile);
struct user *loadUser(char *username, int dataFile);
void updateStats(struct user *player, int won);
char *printUser(struct user *player);
void printAllUsers(int dataFile);
#endif