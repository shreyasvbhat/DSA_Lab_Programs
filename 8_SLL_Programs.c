/*
Implement circular single linked list to perform the following operations 
i) Insert by position 
ii) Delete rear 
iii) Delete Front 
iv) Search for an item by value 
Display the list contents after each operation 
*/
#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
    struct Node* next;
};

// Head structure
struct Head {
    int size;
    struct Node* first;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation error!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to free the memory allocated for the list
void freeList(struct Head* head) {
    if (head->size == 0) {
        free(head);
        return;
    }

    struct Node* current = head->first;
    struct Node* temp;

    for (int i = 0; i < head->size; ++i) {
        temp = current;
        current = current->next;
        free(temp);
    }

    free(head);
}

// Function to initialize the head node
struct Head* initializeHead() {
    struct Head* head = (struct Head*)malloc(sizeof(struct Head));
    if (head == NULL) {
        printf("Memory allocation error!\n");
        exit(1);
    }
    head->size = 0;
    head->first = NULL;
    return head;
}

// Function to print the circular linked list
void displayList(struct Head* head) {
    if (head->size == 0) {
        printf("List is empty.\n");
        return;
    }
    printf("Current List: ");
    struct Node* current = head->first;
    for (int i = 0; i < head->size; ++i) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("(head)\n");
}

// Function to insert a node at a specified position
void insertAtPosition(struct Head* head, int data, int position) {
    if (position < 1 || position > head->size + 1) {
        printf("Invalid position.\n");
        return;
    }

    struct Node* newNode = createNode(data);

    if (position == 1) {
        //insertFront(head, data);
        if (head->size == 0) {
            newNode->next = newNode;
            head->first = newNode;
        } else {
            newNode->next = head->first;
            struct Node* last = head->first;
            while (last->next != head->first) {
                last = last->next;
            }
            last->next = newNode;
            head->first = newNode;
        }
    } else {
        struct Node* current = head->first;
        for (int i = 1; i < position - 1; ++i) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    head->size++;
    displayList(head);
}

// Function to delete a node at the front
void deleteFront(struct Head* head) {
    if (head->size == 0) {
        printf("List is empty.\n");
        return;
    }

    struct Node* temp = head->first;
    if (head->size == 1) {
        free(temp);
        head->first = NULL;
    } else {
        struct Node* last = head->first;
        while (last->next != head->first) {
            last = last->next;
        }
        head->first = temp->next;
        last->next = head->first;
        free(temp);
    }

    head->size--;
    displayList(head);
}

// Function to delete a node at the rear
void deleteRear(struct Head* head) {
    if (head->size == 0) {
        printf("List is empty.\n");
        return;
    }

    if (head->size == 1) {
        free(head->first);
        head->first = NULL;
    } else {
        struct Node* last = head->first;
        struct Node* secondLast = NULL;

        while (last->next != head->first) {
            secondLast = last;
            last = last->next;
        }

        secondLast->next = head->first;
        free(last);
    }

    head->size--;
    displayList(head);
}


// Function to search a node by value
void searchByValue(struct Head* head, int value) {
    if (head->size == 0) {
        printf("List is empty.\n");
        return;
    }

    struct Node* current = head->first;
    int position = 1;

    do {
        if (current->data == value) {
            printf("%d found at position %d.\n",value, position);
            return;
        }
        current = current->next;
        position++;
    } while (current != head->first);

    printf("%d not found.\n",value);
}

int main() {
    struct Head* head = initializeHead();
    int choice, data, position, value;

    do {
        printf("---MENU---\n");
        printf("1. Insert by Position\n");
        printf("2. Delete at Rear\n");
        printf("3. Delete at Front\n");
        printf("4. Search by Value\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                printf("Enter position to insert at: ");
                scanf("%d", &position);
                insertAtPosition(head, data, position);
                break;
            case 2:
                deleteRear(head);
                break;
            case 3:
                deleteFront(head);
                break;
            case 4:
                printf("Enter value to search: ");
                scanf("%d", &value);
                searchByValue(head, value);
                break;
            case 5:
                printf("Exiting...\n");
                freeList(head);
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 5);

    return 0;
}
