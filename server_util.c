#include "server_util.h"

//return new user and write it into userdata file
struct user *createUser(char username[], int dataFile) {
    struct user *newUser = malloc(sizeof(struct user));
    strcpy(newUser->username, username);
    newUser->rating = 100;
    newUser->gamesPlayed = 0;
    newUser->gamesWon = 0;
    newUser->gamesLost = 0;
    strcpy(newUser->rank, "Silver");
    newUser->connected = 0;
    write(dataFile, newUser, sizeof(struct user));
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

void updateStats(struct user *player, int won) {
    player->gamesPlayed++;
    if (won) {
        player->rating += 20;
        player->gamesWon++;
    } else {
        player->rating -= 20;
        player->gamesLost++;
    }
    if (player->rating <= 60) {
        strcpy(player->rank, "Plastic");
    } else if (player->rating <= 140) {
        strcpy(player->rank, "Silver");
    } else if (player->rating <= 200) {
        strcpy(player->rank, "Gold");
    } else if (player->rating <= 270) {
        strcpy(player->rank, "Platinum");
    } else {
        strcpy(player->rank, "Diamond");
    }
}

void printUser(struct user *player) {
    printf("Username: %s\nRating: %d\nRank: %s\n", player->username, player->rating, player->rank);
}