/*
Implement circular double linked list to perform the following operations 
i) Insert front 
ii) Insert rear 
iii) Delete by position 
iv) Search by key 
Display the list contents after each operation 
*/

#include <stdio.h>
#include <stdlib.h>

// Node structure for Circular Doubly Linked List
struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

// Head structure for the Circular Doubly Linked List
struct HeadNode {
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
    newNode->prev = NULL;
    return newNode;
}

// Function to initialize the head node
struct HeadNode* initializeHead() {
    struct HeadNode* head = (struct HeadNode*)malloc(sizeof(struct HeadNode));
    if (head == NULL) {
        printf("Memory allocation error!\n");
        exit(1);
    }
    head->size = 0;
    head->first = NULL;
    return head;
}

// Function to display the circular doubly linked list
void displayList(struct HeadNode* head) {
    if (head->first == NULL) {
        printf("List is empty.\n");
        return;
    }

    struct Node* current = head->first;
    printf("List: ");

    do {
        printf("%d <-> ", current->data);
        current = current->next;
    } while (current != head->first);

    printf("(head)\n");
    //printf("List Size: %d\n", head->size);
}

// Function to free the memory allocated for the circular doubly linked list
void freeList(struct HeadNode* head) {
    if (head->first == NULL) {
        free(head);
        return;
    }

    struct Node* current = head->first;
    struct Node* temp = NULL;

    do {
        temp = current;
        current = current->next;
        free(temp);
    } while (current != head->first);

    free(head);
}

// This Method Inserts the Value Such that the List is maintained in Sorted Order...
void insertFront(struct HeadNode* head, int data) {
    struct Node* newNode = createNode(data);

    if (head->first == NULL) {
        head->first = newNode;
        newNode->next = newNode;
        newNode->prev = newNode;
    } else {
        newNode->next = head->first;
        newNode->prev = head->first->prev;
        head->first->prev->next = newNode;
        head->first->prev = newNode;
        head->first = newNode;
    }

    head->size++;
    printf("Node with data %d inserted at the front.\n", data);
    displayList(head);

}

// Function to insert a node at the rear of the list
void insertRear(struct HeadNode* head, int data) {
    struct Node* newNode = createNode(data);

    if (head->first == NULL) {
        head->first = newNode;
        newNode->next = newNode;
        newNode->prev = newNode;
    } else {
        newNode->next = head->first;
        newNode->prev = head->first->prev;
        head->first->prev->next = newNode;
        head->first->prev = newNode;
    }

    head->size++;
    printf("Node with data %d inserted at the rear.\n", data);
    displayList(head);
}

// Function to delete a node from a specified position
void deleteAtPosition(struct HeadNode* head, int position) {
    if(head->size == 0){
        printf("List is empty.\n");
        return;
    }
    if (position < 1 || position > head->size) {
        printf("Invalid position.\n");
        return;
    }
    int data;
    if (position == 1) {
        data = head->first->data;
        if(head->size == 1){
            free(head->first);
            head->first = NULL;
        }else{
            struct Node* curr = head->first;
            curr->next->prev = curr->prev;
            curr->prev->next = curr->next;
            head->first = curr->next;
            free(curr);
        }
    } else if (position == head->size) {
        data = head->first->prev->data;
        struct Node* curr = head->first->prev;
        curr->prev->next = curr->next;
        head->first->prev = curr->prev;
        free(curr);
    } else {
        struct Node* current = head->first;
        for (int i = 1; i < position; i++) {
            current = current->next;
        }
        data = current->data;
        current->prev->next = current->next;
        current->next->prev = current->prev;
        free(current);
    }
    head->size--;
    printf("%d deleted from %d position\n",data,position);
    displayList(head);
}

// Function to search for a node by key
void searchByKey(struct HeadNode* head, int key) {
    if (head->first == NULL) {
        printf("List is empty.\n");
        return;
    }

    struct Node* current = head->first;
    int position = 1;
    do {
        if (current->data == key) {
            printf("Node with key %d found at position %d.\n", key, position);
            return;
        }
        current = current->next;
        position++;
    } while (current != head->first);

    printf("Node with key %d not found.\n", key);
}

int main() {
    struct HeadNode* head = initializeHead();
    int choice, data, position, key;

    do {
        printf("---MENU---\n");
        printf("1. Insert at Front\n");
        printf("2. Insert at Rear\n");
        printf("3. Delete at Position\n");
        printf("4. Search by key\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to insert at the front: ");
                scanf("%d", &data);
                insertFront(head, data);
                break;
            case 2:
                printf("Enter data to insert at the rear: ");
                scanf("%d", &data);
                insertRear(head, data);
                break;
            case 3:
                printf("Enter position to delete: ");
                scanf("%d", &position);
                deleteAtPosition(head, position);
                break;
            case 4:
                printf("Enter key to search: ");
                scanf("%d", &key);
                searchByKey(head, key);
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

