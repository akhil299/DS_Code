#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Player {
    char name[50];
    struct Player *left;
    struct Player *right;
} Player;

// Create a new player node
Player* createPlayer(char* name) {
    Player* newPlayer = (Player*)malloc(sizeof(Player));
    strcpy(newPlayer->name, name);
    newPlayer->left = newPlayer->right = NULL;
    return newPlayer;
}

// Create a match node (parent) with two players (children)
Player* createMatch(Player* left, Player* right) {
    Player* match = (Player*)malloc(sizeof(Player));
    match->left = left;
    match->right = right;

    printf("\nMatch: %s vs %s\n", left->name, right->name);
    printf("Enter winner: ");
    scanf(" %[^\n]", match->name);

    return match;
}

// Recursively build the tournament tree
Player* buildTournament(Player* players[], int start, int end) {
    if (start == end)
        return players[start];
    int mid = (start + end) / 2;
    Player* leftWinner = buildTournament(players, start, mid);
    Player* rightWinner = buildTournament(players, mid + 1, end);
    return createMatch(leftWinner, rightWinner);
}

// Display the final winner
void printWinner(Player* root) {
    if (root)
        printf("\n Tournament Winner: %s \n", root->name);
}

int main() {
    int n;
    printf("Enter number of players (must be power of 2): ");
    scanf("%d", &n);

    if (n <= 1 || (n & (n - 1)) != 0) {
        printf("Number of players must be a power of 2.\n");
        return 1;
    }

    Player* players[n];
    char name[50];

    for (int i = 0; i < n; i++) {
        printf("Enter player %d name: ", i + 1);
        scanf(" %[^\n]", name);
        players[i] = createPlayer(name);
    }

    Player* root = buildTournament(players, 0, n - 1);
    printWinner(root);

    return 0;
}
