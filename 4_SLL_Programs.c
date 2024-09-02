/*
Implement circular single linked list to perform the following operations 
i) Insert by order 
ii) Delete by position 
iii) Search for an item by key 
iv) Delete by key Display the list contents after each operation 
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

// This Method Inserts the Value Such that the List is maintained in Sorted Order...
void insertByOrder(struct Head* list, int data) {
    if (list->first == NULL) {
        list->first = createNode(data);
        list->first->next = list->first;
    } else if (data <= list->first->data) {
        struct Node* tempNode = list->first;

        while (tempNode->next != list->first) {
            tempNode = tempNode->next;
        }

        tempNode->next = createNode(data);
        tempNode->next->next = list->first;
        list->first = tempNode->next;
    } else {
        struct Node* tempNode = list->first;

        while (tempNode->next != list->first && tempNode->next->data < data) {
            tempNode = tempNode->next;
        }
        struct Node* temp = tempNode->next;
        tempNode->next = createNode(data);
        tempNode->next->next = temp;
    }

    printf("%d has been Inserted Succesfully...\n ",data);
    list->size++;
    displayList(list);
}

// Function to delete a node at a specified position
void deleteAtPosition(struct Head* head, int position) {
    if (head->size == 0) {
        printf("List is empty.\n");
        return;
    }

    if (position < 1 || position > head->size) {
        printf("Invalid position.\n");
        return;
    }

    if (position == 1) {
        struct Node* current = head->first;
        struct Node* temp = head->first;
        if(head->size == 1){
            free(current);
            head->first = NULL;
        }else{
            while (temp->next != head->first) {
                temp = temp->next;
            }
            head->first = current->next;
            temp->next = head->first;
            free(current);
        }
    } else {
        struct Node* current = head->first;
        struct Node* temp;

        for (int i = 1; i < position - 1; ++i) {
            current = current->next;
        }

        temp = current->next;
        current->next = temp->next;
        free(temp);
    }
    head->size--;
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
        deleteAtPosition(head,1);   
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

// Function to search a node by key
void searchByKey(struct Head* head, int key) {
    if (head->size == 0) {
        printf("List is empty.\n");
        return;
    }

    struct Node* current = head->first;
    int position = 1;

    do {
        if (current->data == key) {
            printf("%d found at position %d.\n",key, position);
            return;
        }
        current = current->next;
        position++;
    } while (current != head->first);

    printf("%d not found.\n",key);
}

int main() {
    struct Head* head = initializeHead();
    int choice, data, position, key;

    do {
        printf("---MENU---\n");
        printf("1. Insert by Order\n");
        printf("2. Delete by Position\n");
        printf("3. Search by Key\n");
        printf("4. Delete by Key\n");
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
                printf("Enter position to delete: ");
                scanf("%d", &position);
                deleteAtPosition(head, position);
                break;
            case 3:
                printf("Enter key to search: ");
                scanf("%d", &key);
                searchByKey(head, key);
                break;
            case 4:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                deleteByKey(head, key);
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
