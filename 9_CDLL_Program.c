/*
Implement circular double linked list to perform the following operations 
i) Insert by order 
ii) Delete rear 
iii) Delete Front 
iv) Search for an item by position 
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
void insertByOrder(struct HeadNode* head, int data) {
    if (head->first == NULL) {
        head->first = createNode(data);
        head->first->next = head->first->prev = head->first;
    } else if (data <= head->first->data) {
        struct Node* newNode = createNode(data);
        newNode->next = head->first;
        newNode->prev = head->first->prev;
        newNode->prev->next = newNode;
        head->first->prev = newNode;
        head->first = newNode;
    } else {
        struct Node* tempNode = head->first;

        while (tempNode->next != head->first && tempNode->next->data < data) {
            tempNode = tempNode->next;
        }

        struct Node* nextNode = tempNode->next;
        struct Node* newNode = createNode(data);
        newNode->next = nextNode;
        newNode->prev = tempNode;
        tempNode->next = newNode;
        nextNode->prev = newNode;
        // tempNode->next = createNode(data, nextNode, tempNode);
        // nextNode->prev = tempNode->next;
    }

    printf("%d has been Inserted Succesfully...\n",data);
    head->size++;
    displayList(head);
}

// Function to delete a node from the front of the list
void deleteFront(struct HeadNode* head) {
    if (head->size == 0) {
        printf("List is empty. Nothing to delete.\n");
        return;
    }

    if (head->size == 1) {
        free(head->first);
        head->first = NULL;
    } else {
        struct Node* temp = head->first;
        head->first->prev->next = head->first->next;
        head->first->next->prev = head->first->prev;
        head->first = head->first->next;
        free(temp);
    }

    head->size--;
    displayList(head);
}

// Function to delete a node from the rear of the list
void deleteRear(struct HeadNode* head) {
    if (head->size == 0) {
        printf("List is empty. Nothing to delete.\n");
        return;
    }

    if (head->size == 1) {
        free(head->first);
        head->first = NULL;
    } else {
        struct Node* temp = head->first->prev;
        temp->prev->next = head->first;
        head->first->prev = temp->prev;
        free(temp);
    }

    head->size--;
    displayList(head);
}


void searchByPosition(struct HeadNode* head, int pos){
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
    struct HeadNode* head = initializeHead();
    int choice, data, position, key;

    do {
        printf("---MENU---\n");
        printf("1. Insert by Order\n");
        printf("2. Delete by Rear\n");
        printf("3. Delete by Front\n");
        printf("4. Search by Position\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                insertByOrder(head, data);
                break;
            case 2:
                deleteRear(head);
                break;
            case 3:
                deleteFront(head);
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
