#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TABLE_SIZE 100
#define WORD_SIZE 50
#define TEXT_SIZE 1000  // Max input text length

typedef struct Node {
    char word[WORD_SIZE];
    int count;
    struct Node* next;
} Node;

Node* hashTable[TABLE_SIZE];

// Hash function (djb2)
unsigned int hash(const char* str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + tolower(c);
    return hash % TABLE_SIZE;
}

void clean_word(char* word) {
    int i, j = 0;
    for (i = 0; word[i]; i++) {
        if (isalnum(word[i])) {
            word[j++] = tolower(word[i]);
        }
    }
    word[j] = '\0';
}

void insert_word(const char* word_raw) {
    char word[WORD_SIZE];
    strncpy(word, word_raw, WORD_SIZE - 1);
    word[WORD_SIZE - 1] = '\0';

    clean_word(word);
    if (strlen(word) == 0) return;

    int index = hash(word);
    Node* current = hashTable[index];

    while (current != NULL) {
        if (strcmp(current->word, word) == 0) {
            current->count++;
            return;
        }
        current = current->next;
    }

    Node* new_node = (Node*)malloc(sizeof(Node));
    strcpy(new_node->word, word);
    new_node->count = 1;
    new_node->next = hashTable[index];
    hashTable[index] = new_node;
}

void print_table() {
    printf("\nWord Frequencies:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* current = hashTable[i];
        while (current != NULL) {
            printf("%s: %d\n", current->word, current->count);
            current = current->next;
        }
    }
}

void free_table() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* current = hashTable[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
}

int main() {
    char text[TEXT_SIZE];

    printf("Enter a line of text:\n");
    fgets(text, TEXT_SIZE, stdin);
    text[strcspn(text, "\n")] = '\0'; // Remove newline character

    char* token = strtok(text, " ");
    while (token != NULL) {
        insert_word(token);
        token = strtok(NULL, " ");
    }

    print_table();
    free_table();

    return 0;
}
