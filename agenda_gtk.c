#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct for storage
typedef struct Contact {
    char name[50];
    char telephone[20];
    char email[50];
} Contact;

typedef struct Agenda {
    Contact contacts[100];
    int numContacts;
} Agenda;

// Function prototypes
void addContact(Agenda *agenda);
void searchContact(Agenda *agenda);
void displayContact(Contact *contact);
void editContact(Agenda *agenda);
void removeContact(Agenda *agenda);
void listContacts(Agenda *agenda);
void saveContacts(Agenda *agenda);
void loadContacts(Agenda *agenda);
void sortContacts(Agenda *agenda);

int main() {
    Agenda agenda; // init agenda
    agenda.numContacts = 0;
    
    loadContacts(&agenda);

    int option;
    do {
        printf("\nMenu de Agenda:\n");
        printf("1. Add Contact\n");
        printf("2. Search Contact\n");
        printf("3. Display Contact\n");
        printf("4. Edit Contact\n");
        printf("5. Remove Contact\n");
        printf("6. List Contacts\n");
        printf("7. Save Contacts\n");
        printf("0. Exit\n");
        printf("Enter your option: ");
        scanf("%d", &option);
        getchar(); // consume newline character
        
        switch (option) {
            case 1:
                addContact(&agenda);
                break;
            case 2:
                searchContact(&agenda);
                break;
            case 3:
                printf("Enter the contact number to display: ");
                int index;
                scanf("%d", &index);
                if (index > 0 && index <= agenda.numContacts) {
                    displayContact(&agenda.contacts[index - 1]);
                } else {
                    printf("Invalid contact number.\n");
                }
                break;
            case 4:
                editContact(&agenda);
                break;
            case 5:
                removeContact(&agenda);
                break;
            case 6:
                listContacts(&agenda);
                break;
            case 7:
                saveContacts(&agenda);
                break;
            case 0:
                saveContacts(&agenda);
                printf("\nExiting the agenda..\n");
                break;
            default:
                printf("\nInvalid option! Try again.\n");
        }
    } while (option != 0);
    
    return 0;
}

void addContact(Agenda *agenda) {
    if (agenda->numContacts < 100) {
        Contact newContact;
        printf("Enter name: ");
        fgets(newContact.name, 50, stdin);
        newContact.name[strcspn(newContact.name, "\n")] = '\0'; // remove newline character
        printf("Enter telephone: ");
        fgets(newContact.telephone, 20, stdin);
        newContact.telephone[strcspn(newContact.telephone, "\n")] = '\0'; // remove newline character
        printf("Enter email: ");
        fgets(newContact.email, 50, stdin);
        newContact.email[strcspn(newContact.email, "\n")] = '\0'; // remove newline character
        
        agenda->contacts[agenda->numContacts++] = newContact;
        sortContacts(agenda);
        printf("Contact added successfully.\n");
    } else {
        printf("Agenda is full. Cannot add more contacts.\n");
    }
}

void searchContact(Agenda *agenda) {
    char searchName[50];
    printf("Enter name to search: ");
    fgets(searchName, 50, stdin);
    searchName[strcspn(searchName, "\n")] = '\0'; // remove newline character
    
    int found = 0;
    for (int i = 0; i < agenda->numContacts; i++) {
        if (strstr(agenda->contacts[i].name, searchName) != NULL) {
            displayContact(&agenda->contacts[i]);
            found = 1;
        }
    }
    if (!found) {
        printf("Contact not found.\n");
    }
}

void displayContact(Contact *contact) {
    printf("\nContact Details:\n");
    printf("Name: %s\n", contact->name);
    printf("Telephone: %s\n", contact->telephone);
    printf("Email: %s\n", contact->email);
}

void editContact(Agenda *agenda) {
    char searchName[50];
    printf("Enter name of the contact to edit: ");
    fgets(searchName, 50, stdin);
    searchName[strcspn(searchName, "\n")] = '\0'; // remove newline character
    
    for (int i = 0; i < agenda->numContacts; i++) {
        if (strcmp(agenda->contacts[i].name, searchName) == 0) {
            printf("Editing contact:\n");
            displayContact(&agenda->contacts[i]);
            
            printf("Enter new name (leave empty to keep current): ");
            char newName[50];
            fgets(newName, 50, stdin);
            newName[strcspn(newName, "\n")] = '\0'; // remove newline character
            if (strlen(newName) > 0) {
                strcpy(agenda->contacts[i].name, newName);
            }
            
            printf("Enter new telephone (leave empty to keep current): ");
            char newTelephone[20];
            fgets(newTelephone, 20, stdin);
            newTelephone[strcspn(newTelephone, "\n")] = '\0'; // remove newline character
            if (strlen(newTelephone) > 0) {
                strcpy(agenda->contacts[i].telephone, newTelephone);
            }
            
            printf("Enter new email (leave empty to keep current): ");
            char newEmail[50];
            fgets(newEmail, 50, stdin);
            newEmail[strcspn(newEmail, "\n")] = '\0'; // remove newline character
            if (strlen(newEmail) > 0) {
                strcpy(agenda->contacts[i].email, newEmail);
            }
            
            sortContacts(agenda);
            printf("Contact updated successfully.\n");
            return;
        }
    }
    printf("Contact not found.\n");
}

void removeContact(Agenda *agenda) {
    char searchName[50];
    printf("Enter name of the contact to remove: ");
    fgets(searchName, 50, stdin);
    searchName[strcspn(searchName, "\n")] = '\0'; // remove newline character
    
    for (int i = 0; i < agenda->numContacts; i++) {
        if (strcmp(agenda->contacts[i].name, searchName) == 0) {
            for (int j = i; j < agenda->numContacts - 1; j++) {
                agenda->contacts[j] = agenda->contacts[j + 1];
            }
            agenda->numContacts--;
            printf("Contact removed successfully.\n");
            return;
        }
    }
    printf("Contact not found.\n");
}

void listContacts(Agenda *agenda) {
    if (agenda->numContacts == 0) {
        printf("No contacts to display.\n");
    } else {
        printf("\nList of Contacts:\n");
        for (int i = 0; i < agenda->numContacts; i++) {
            printf("%d. %s\n", i + 1, agenda->contacts[i].name);
        }
    }
}

void saveContacts(Agenda *agenda) {
    FILE *file = fopen("contacts.txt", "w");
    if (file == NULL) {
        printf("Failed to open file for writing.\n");
        return;
    }
    for (int i = 0; i < agenda->numContacts; i++) {
        fprintf(file, "%s,%s,%s\n", agenda->contacts[i].name, agenda->contacts[i].telephone, agenda->contacts[i].email);
    }
    fclose(file);
    printf("Contacts saved successfully.\n");
}

void loadContacts(Agenda *agenda) {
    FILE *file = fopen("contacts.txt", "r");
    if (file == NULL) {
        printf("No previous contacts found.\n");
        return;
    }
    char line[150];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0'; // remove newline character
        char *token = strtok(line, ",");
        if (token != NULL) strcpy(agenda->contacts[agenda->numContacts].name, token);
        token = strtok(NULL, ",");
        if (token != NULL) strcpy(agenda->contacts[agenda->numContacts].telephone, token);
        token = strtok(NULL, ",");
        if (token != NULL) strcpy(agenda->contacts[agenda->numContacts].email, token);
        agenda->numContacts++;
    }
    fclose(file);
    printf("Contacts loaded successfully.\n");
}

void sortContacts(Agenda *agenda) {
    for (int i = 0; i < agenda->numContacts - 1; i++) {
        for (int j = i + 1; j < agenda->numContacts; j++) {
            if (strcmp(agenda->contacts[i].name, agenda->contacts[j].name) > 0) {
                Contact temp = agenda->contacts[i];
                agenda->contacts[i] = agenda->contacts[j];
                agenda->contacts[j] = temp;
            }
        }
    }
}
