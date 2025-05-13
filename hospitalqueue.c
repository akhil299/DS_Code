#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100

typedef struct Patient {
    int id;
    char name[50];
    int severity;  // 1 = Critical, 0 = Non-Critical
    struct Patient* next;
} Patient;

Patient *criticalFront = NULL, *criticalRear = NULL;
Patient *normalFront = NULL, *normalRear = NULL;

void enqueue(Patient** front, Patient** rear, int id, char name[], int severity) {
    Patient* newPatient = (Patient*)malloc(sizeof(Patient));
    newPatient->id = id;
    strcpy(newPatient->name, name);
    newPatient->severity = severity;
    newPatient->next = NULL;

    if (*rear == NULL) {
        *front = *rear = newPatient;
    } else {
        (*rear)->next = newPatient;
        *rear = newPatient;
    }
    printf("Patient '%s' added to %s queue.\n", name, severity == 1 ? "CRITICAL" : "NORMAL");
}

void dequeue() {
    Patient* temp = NULL;

    if (criticalFront != NULL) {
        temp = criticalFront;
        criticalFront = criticalFront->next;
        if (criticalFront == NULL) criticalRear = NULL;
    } else if (normalFront != NULL) {
        temp = normalFront;
        normalFront = normalFront->next;
        if (normalFront == NULL) normalRear = NULL;
    } else {
        printf("No patients in queue.\n");
        return;
    }

    printf("Treating Patient: ID=%d, Name=%s, Severity=%s\n", temp->id, temp->name, temp->severity == 1 ? "CRITICAL" : "NORMAL");
    free(temp);
}

void displayQueue() {
    printf("\n--- CRITICAL Queue ---\n");
    Patient* temp = criticalFront;
    while (temp != NULL) {
        printf("ID=%d, Name=%s\n", temp->id, temp->name);
        temp = temp->next;
    }

    printf("\n--- NORMAL Queue ---\n");
    temp = normalFront;
    while (temp != NULL) {
        printf("ID=%d, Name=%s\n", temp->id, temp->name);
        temp = temp->next;
    }
}

int main() {
    int choice, id, severity;
    char name[50];

    while (1) {
        printf("\nHospital Emergency Room System\n");
        printf("1. Add Patient\n2. Treat Patient\n3. Display Queue\n4. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        getchar();  // Clear newline

        switch (choice) {
            case 1:
                printf("Enter Patient ID: ");
                scanf("%d", &id);
                getchar();
                printf("Enter Patient Name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                printf("Enter Severity (1 = Critical, 0 = Normal): ");
                scanf("%d", &severity);
                enqueue(severity == 1 ? &criticalFront : &normalFront,
                        severity == 1 ? &criticalRear : &normalRear,
                        id, name, severity);
                break;

            case 2:
                dequeue();
                break;

            case 3:
                displayQueue();
                break;

            case 4:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}
