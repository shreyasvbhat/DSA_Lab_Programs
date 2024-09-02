/*
Implement circular single linked list to perform the following operations 
i) Insert front 
ii) Insert rear 
iii) Delete a node with the given key
iv) Search for an item by position 
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

// Function to insert a node at the front
void insertFront(struct Head* head, int data) {
    struct Node* newNode = createNode(data);

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

    head->size++;
    displayList(head);
}

// Function to insert a node at the rear
void insertRear(struct Head* head, int data) {
    struct Node* newNode = createNode(data);

    if (head->size == 0) {
        newNode->next = newNode;
        head->first = newNode;
    } else {
        struct Node* last = head->first;
        while (last->next != head->first) {
            last = last->next;
        }
        newNode->next = head->first;
        last->next = newNode;
    }

    head->size++;
    displayList(head);
}

// Function to delete a node by key
void deleteByKey(struct Head* head, int key) {
    if (head->size == 0) {
        printf("List is empty.\n");
        return;
    }

    struct Node* current = head->first;
    struct Node* temp = NULL;

    if (current->data == key) {
        printf("%d deleted from the list\n", key);
        temp = current;
        while(current->next != head->first){
            current = current->next;
        }
        head->first = temp->next;
        current->next = head->first;
        free(temp);  
        if(head->size == 1){
            head->first = NULL;
        }
        head->size--;
        displayList(head);
        return;
    }

    while (current->next != head->first) {
        if (current->next->data == key) {
            temp = current->next;
            current->next = temp->next;
            free(temp);
            head->size--;
            printf("%d deleted from the list\n", key);
            displayList(head);
            return;
        }
        current = current->next;
    }

    printf("Key not found.\n");
}

void searchByPosition(struct Head* head, int pos){
    if(head->size == 0){
        printf("List is empty.\n");
        return;
    }
    if(pos<1 || pos> head->size){
        printf("Invalid position.\n");
        return;
    }
    struct Node* current = head->first;
    int i=1;
    do
    {
        if(i==pos){
            printf("Element at %d position is %d\n",pos, current->data);
            return;
        }
        current = current->next;
        i++;
    } while (current!=head->first);    
}

int main() {
    struct Head* head = initializeHead();
    int choice, data, position, key;

    do {
        printf("---MENU---\n");
        printf("1. Insert at Front\n");
        printf("2. Insert at Rear\n");
        printf("3. Delete by Key\n");
        printf("4. Search by Position\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to insert at front: ");
                scanf("%d", &data);
                insertFront(head, data);
                break;
            case 2:
                printf("Enter data to insert at rear: ");
                scanf("%d", &data);
                insertRear(head, data);
                break;
            case 3:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                deleteByKey(head, key);
                break;
            case 4:
                printf("Enter position to search: ");
                scanf("%d", &position);
                searchByPosition(head, position);
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
