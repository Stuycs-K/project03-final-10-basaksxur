#include "server_util.h"

//return new user and write it into userdata file
struct user *createUser(char username[], int dataFile) {
    struct user *newUser = malloc(sizeof(struct user));
    strcpy(newUser->username, username);
    newUser->rating = 100;
    newUser->gamesPlayed = 0;
    newUser->gamesWon = 0;
    newUser->gamesLost = 0;
    newUser->gamesTied = 0;
    strcpy(newUser->rank, "Silver");
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

void updateStats(struct user *player, int won, int dataFile) {
    player->gamesPlayed++;
    if (won == 1) {
        player->rating += 20;
        player->gamesWon++;
    } else if (won == 2){
        player->gamesTied++;
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

    struct user *temp = malloc(sizeof(struct user));
    lseek(dataFile, 0, SEEK_SET);
    while (read(dataFile, temp, sizeof(struct user))) {
        if (!strcmp(temp->username, player->username)) {
            lseek(dataFile, - sizeof(struct user), SEEK_CUR);
            write(dataFile, player, sizeof(struct user));
            break;
        }
    }
}

char *printUser(struct user *player) {
    char output[100];
    sprintf(output, "Username: %s\nRating: %d\nRank: %s\nGames Played: %d\nGames Won: %d\nGames Lost: %d\n", player->username, player->rating, player->rank, player->gamesPlayed, player->gamesWon, player->gamesLost);
    return strdup(output);
}

void printAllUsers(int dataFile) {
  struct user *player = malloc(sizeof(struct user));
  lseek(dataFile, 0, SEEK_SET);
  while (read(dataFile, player, sizeof(struct user))) {
    printUser(player);
  }
}
