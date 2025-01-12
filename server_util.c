#include "server_util.h"

struct user *createUser(char username[]) {
    struct user *newUser = malloc(sizeof(struct user));
    strcpy(newUser->username, username);
    newUser->rating = 100;
    newUser->gamesPlayed = 0;
    newUser->gamesWon = 0;
    newUser->gamesLost = 0;
    strcpy(newUser->rank, "Silver");
    newUser->connected = 0;
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