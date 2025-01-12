#include "server_util.h"

struct user *createUser(char username[], int rating, int gamesPlayed, int gamesWon, int gamesLost, char rank[], int connected) {
    struct user *newUser = malloc(sizeof(struct user));
    strcpy(newUser->username, username);
    newUser->rating = rating;
    newUser->gamesPlayed = gamesPlayed;
    newUser->gamesWon = gamesWon;
    newUser->gamesLost = gamesLost;
    strcpy(newUser->rank, rank);
    newUser->connected = connected;
    return newUser;
}

//returns a user specified by username, if the user doesn't exist returns NULL
struct user *loadUser(char *username, int dataFile) {
    struct user *output = malloc(sizeof(struct user));
    lseek(dataFile, 0, SEEK_SET);
    while (read(dataFile, output, sizeof(struct user))) {
        if (!strcmp(username, output->username)) {
            return output;
        }
    }
    return NULL;
}

void printUser(struct user *player) {
    printf("Username: %s\nRating: %d\nRank: %s\n", player->username, player->rating, player->rank);
}