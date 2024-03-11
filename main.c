#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct contact {
    char name[50];
    char phone[20];
    char email[50];
    struct contact *next;
} Contact;

Contact *head = NULL;

void read_contacts() {
    FILE *file = fopen("phone.txt", "r");
    if (file == NULL) {
        return;
    }
    while (!feof(file)) {
        Contact *c = malloc(sizeof(Contact));
        fscanf(file, "%[^,],%[^,],%[^\n]\n", c->name, c->phone, c->email);
        c->next = head;
        head = c;
    }
    fclose(file);
}

void save_contacts() {
    FILE *file = fopen("phone.txt", "w");
    if (file == NULL) {
        printf("Error saving contacts.\n");
        return;
    }
    Contact *current = head;
    while (current != NULL) {
        fprintf(file, "%s,%s,%s\n", current->name, current->phone, current->email);
        current = current->next;
    }
    fclose(file);
}

void print_contacts() {
    printf("Contacts:\n");
    Contact *current = head;
    while (current != NULL) {
        printf("%s | %s | %s\n", current->name, current->phone, current->email);
        current = current->next;
    }
}

void add_contact() {
    Contact *c = malloc(sizeof(Contact));
    printf("Enter contact name: ");
    scanf("%s", c->name);
    printf("Enter phone number: ");
    scanf("%s", c->phone);
    printf("Enter email address: ");
    scanf("%s", c->email);
    c->next = head;
    head = c;
    printf("Contact added.\n");
}

void delete_contact() {
    char name[50];
    printf("Enter the name of the contact to delete: ");
    scanf("%s", name);
    Contact *current = head;
    Contact *previous = NULL;
    while (current != NULL) {
        if (strcasecmp(name, current->name) == 0) {
            if (previous == NULL) {
                head = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);
            printf("Contact deleted.\n");
            return;
        }
        previous = current;
        current = current->next;
    }
    printf("Contact not found.\n");
}

void search_contact() {
    printf("Enter contact name to search: ");
    char name[50];
    scanf("%s", name);
    Contact *current = head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            printf("Contact found.\n");
            printf("%s | %s | %s\n", current->name, current->phone, current->email);
            return;
        }
        current = current->next;
    }
    printf("Contact not found.\n");
}

void update_contact() {
    char name[50];
    printf("Enter the name of the contact to update: ");
    scanf("%s", name);
    Contact *current = head;
    while (current != NULL) {
        if (strcasecmp(name, current->name) == 0) {
            printf("Enter the new phone number: ");
            scanf("%s", current->phone);
            printf("Enter the new email address: ");
            scanf("%s", current->email);
            printf("Contact updated.\n");
            return;
        }
        current = current->next;
    }
    printf("Contact not found.\n");
}


int main() {
    read_contacts();
    int choice = 0;
    while (choice != 5) {
        printf("\nPhone Contact Manager\n");
        printf("1. View contacts\n");
        printf("2. Add contact\n");
        printf("3. Update contact\n");
        printf("4. Delete contact\n");
        printf("5. Search contact\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                print_contacts();
                break;
            case 2:
                add_contact();
                save_contacts();
                break;
            case 3:
                update_contact();
                save_contacts();
                break;
            case 4:
                delete_contact();
                save_contacts();
                break;
            case 5:
                search_contact();
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }
    }

    return 0;
}

