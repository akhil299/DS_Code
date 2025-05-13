#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Song {
    int id;
    char title[50];
    char artist[50];
    float duration;
    struct Song* next;
} Song;

typedef struct StackNode {
    Song* song;
    struct StackNode* next;
} StackNode;

typedef struct QueueNode {
    Song* song;
    struct QueueNode* next;
} QueueNode;

Song* head = NULL;
StackNode* historyTop = NULL;
QueueNode *front = NULL, *rear = NULL;

// Helper to remove newline
void trimNewline(char* str) {
    str[strcspn(str, "\n")] = '\0';
}

// Add a new song
void addSong(int id, char title[], char artist[], float duration) {
    Song* newSong = (Song*)malloc(sizeof(Song));
    newSong->id = id;
    strcpy(newSong->title, title);
    strcpy(newSong->artist, artist);
    newSong->duration = duration;
    newSong->next = head;
    head = newSong;
    printf("Song added successfully!\n");
}

// Display all songs
void displaySongs() {
    Song* temp = head;
    if (!temp) {
        printf("No songs in the library.\n");
        return;
    }
    printf("\n--- Song List ---\n");
    while (temp) {
        printf("ID: %d | Title: %s | Artist: %s | Duration: %.2f mins\n",
               temp->id, temp->title, temp->artist, temp->duration);
        temp = temp->next;
    }
}

// Find song by title
Song* findSongByTitle(char title[]) {
    Song* temp = head;
    while (temp) {
        if (strcmp(temp->title, title) == 0)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

// Search and display a song
void searchSong(char title[]) {
    Song* song = findSongByTitle(title);
    if (song)
        printf("Found: %s by %s (%.2f mins)\n", song->title, song->artist, song->duration);
    else
        printf("Song not found.\n");
}

// Add song to playback queue
void enqueue(Song* song) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->song = song;
    newNode->next = NULL;
    if (!rear) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
}

// Play the next song
void playNext() {
    if (!front) {
        printf("Playback queue is empty.\n");
        return;
    }
    QueueNode* temp = front;
    printf("Now Playing: %s by %s\n", temp->song->title, temp->song->artist);

    StackNode* newHist = (StackNode*)malloc(sizeof(StackNode));
    newHist->song = temp->song;
    newHist->next = historyTop;
    historyTop = newHist;

    front = front->next;
    if (!front) rear = NULL;
    free(temp);
}

// Show playback history
void showHistory() {
    StackNode* temp = historyTop;
    if (!temp) {
        printf("No playback history.\n");
        return;
    }
    printf("\n--- Playback History ---\n");
    while (temp) {
        printf("%s by %s\n", temp->song->title, temp->song->artist);
        temp = temp->next;
    }
}

int main() {
    int choice, id;
    char title[50], artist[50];
    float duration;

    while (1) {
        printf("\n\n=== Music Player Manager ===\n");
        printf("1. Add Song\n2. View Songs\n3. Search Song\n4. Add to Playback Queue\n5. Play Next\n6. Show History\nEnter choice: ");
        scanf("%d", &choice);
        getchar(); // clear newline

        switch (choice) {
            case 1:
                printf("Enter ID: ");
                scanf("%d", &id);
                getchar();

                printf("Enter Title: ");
                fgets(title, sizeof(title), stdin);
                trimNewline(title);

                printf("Enter Artist: ");
                fgets(artist, sizeof(artist), stdin);
                trimNewline(artist);

                printf("Enter Duration: ");
                scanf("%f", &duration);
                getchar();

                addSong(id, title, artist, duration);
                break;

            case 2:
                displaySongs();
                break;

            case 3:
                printf("Enter title to search: ");
                fgets(title, sizeof(title), stdin);
                trimNewline(title);
                searchSong(title);
                break;

            case 4:
                printf("Enter title to add to queue: ");
                fgets(title, sizeof(title), stdin);
                trimNewline(title);
                {
                    Song* found = findSongByTitle(title);
                    if (found) {
                        enqueue(found);
                        printf("Added to playback queue.\n");
                    } else {
                        printf("Song not found.\n");
                    }
                }
                break;

            case 5:
                playNext();
                break;

            case 6:
                showHistory();
                break;

            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}
