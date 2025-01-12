#ifndef SERVER_UTIL_H
#define SERVER_UTIL_H
#include <stdio.h>
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
struct user *loadUser(char *username, int dataFile);
void printUser(struct user *player);
#endif