#include "server_util.h"

//returns a user specified by username, if the user doesn't exist returns NULL
struct user *loadUser(char *username, int dataFile) {
    struct user *output;
    char name[20];
    int offset = 0;
    while (read(dataFile, name, sizeof(name))) {
        if (!strcmp(username, name)) {
            read(dataFile, output, sizeof(struct user));
            return output;
        }
        offset += sizeof(struct user);
        lseek(dataFile, offset, SEEK_SET);
    }
    return NULL;
}

void printUser(struct user *player) {
    printf("Username: %s\nRating: %d\nRank: %s\n", player->username, player->rating, player->rank);
}