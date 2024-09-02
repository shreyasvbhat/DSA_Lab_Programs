/*
Develop a menu driven program to implement the following types of Queues by allocating memory dynamically. 
i) Circular Queue 
ii) Double ended Queue 
Note: Define Queue structure and implement the operation with array representation 
*/

#include <stdio.h>
#include <stdlib.h>

// Structure for Circular Queue
typedef struct {
    int front, rear, capacity;
    int *array;
} CircularQueue;

// Structure for Double Ended Queue
typedef struct {
    int front, rear, capacity;
    int *array;
} Deque;

// Function to create Circular Queue
CircularQueue* createCircularQueue(int capacity) {
    CircularQueue *queue = (CircularQueue*)malloc(sizeof(CircularQueue));
    if(queue == NULL){
        printf("Memory allocation failed.\n");
        exit(1);
    }
    queue->capacity = capacity;
    queue->front = queue->rear = -1;
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    if(queue->array == NULL){
        printf("Memory allocation failed.\n");
        exit(1);
    }
    return queue;
}

// Function to create Deque
Deque* createDeque(int capacity) {
    Deque *deque = (Deque*)malloc(sizeof(Deque));
    if(deque == NULL){
        printf("Memory allocation failed.\n");
        exit(1);
    }
    deque->capacity = capacity;
    deque->front = deque->rear = -1;
    deque->array = (int*)malloc(deque->capacity * sizeof(int));
    if(deque->array == NULL){
        printf("Memory allocation failed.\n");
        exit(1);
    }
    return deque;
}

void reallocate(CircularQueue *queue) { 
    int *newQueue = (int *)malloc(2 * queue->capacity * sizeof(int)); 
 
    if (newQueue == NULL) { 
        printf("\nMemory Allocation Failed...\n"); 
        exit(1); 
    } 
 
    for (int i = queue->front, j = 0; j < queue->capacity; i = (i + 1) % queue->capacity, j++) { 
        newQueue[j] = queue->array[i]; 
    } 
 
    queue->front = 0, queue->rear = queue->capacity - 1; 
    queue->capacity *= 2; 
    free(queue->array); 
    queue->array = newQueue; 
} 

// Function to enqueue data into Circular Queue
void enqueueCircular(CircularQueue *queue, int data) {
    if ((queue->rear + 1) % queue->capacity == queue->front) {
        // Queue is full, need to reallocate memory
        printf("Circular Queue is full. Reallocating more memory..\n");
        reallocate(queue);
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = data;
    if (queue->front == -1) {
        queue->front = queue->rear;
    }
    printf("Inserted %d into Circular Queue\n", data);
}

// Function to dequeue data from Circular Queue
void dequeueCircular(CircularQueue *queue) {
    if (queue->front == -1) {
        printf("Circular Queue is empty!\n");
        return;
    }
    int data = queue->array[queue->front];
    if (queue->front == queue->rear) {
        queue->front = queue->rear = -1;
    } else {
        queue->front = (queue->front + 1) % queue->capacity;
    }
    printf("Removed %d from Circular Queue.\n",data);
    return;
}

// Function to display Circular Queue
void displayCircularQueue(CircularQueue *queue) {
    if (queue->front == -1) {
        printf("Circular Queue is empty!\n");
        return;
    }
    int i;
    for (i = queue->front; i != queue->rear; i = (i + 1) % queue->capacity) {
        printf("%d ", queue->array[i]);
    }
    printf("%d\n", queue->array[i]);
}

// Function to enqueue data at rear end of Deque
void enqueueRear(Deque *deque, int data) {
    if (deque->rear == deque->capacity - 1) {
        // Queue is full, need to reallocate memory
        printf("Double Ended Queue is full. Reallocating more memory..\n");
        int newCapacity = deque->capacity * 2;
        deque->array = (int*)realloc(deque->array, newCapacity * sizeof(int));
        if(deque->array == NULL){
            printf("Reallocation failed.\n");
            exit(1);
        }
        deque->capacity = newCapacity;
    }
    deque->array[++deque->rear] = data;
    if (deque->front == -1) {
        deque->front = 0;
    }
    printf("Inserted %d into rear end of Doubly Ended Queue.\n",data);
}

// Function to enqueue data at front end of Deque
void enqueueFront(Deque *deque, int data) {
    if (deque->rear == deque->capacity - 1) {
        // Queue is full, need to reallocate memory
        printf("Double Ended Queue is full. Reallocating more memory..\n");
        int newCapacity = deque->capacity * 2;
        deque->array = (int*)realloc(deque->array, newCapacity * sizeof(int));
        if(deque->array == NULL){
            printf("Reallocation failed.\n");
            exit(1);
        }
        deque->capacity = newCapacity;
    }
    if (deque->front == 0) {
        int i;
        for (i = deque->rear + 1; i > 0; --i) {
            deque->array[i] = deque->array[i - 1];
        }
        deque->array[0] = data;
        deque->rear++;
    } else if(deque->front == -1){
        deque->front = deque->rear = 0;
        deque->array[deque->front] = data;
    }else{
        deque->array[--deque->front] = data;
    }
    printf("Inserted %d into front end of Doubly Ended Queue.\n",data);
}

// Function to dequeue data from front end of Deque
void dequeueFront(Deque *deque) {
    if (deque->front == -1) {
        printf("Doubly Ended Queue is empty!\n");
        return;
    }
    int data = deque->array[deque->front];
    if (deque->front == deque->rear) {
        deque->front = deque->rear = -1;
    } else {
        deque->front++;
    }
    printf("Removed %d from front of Doubly ended queue\n",data);
}

// Function to dequeue data from rear end of Deque
void dequeueRear(Deque *deque) {
    if (deque->rear == -1) {
        printf("Doubly Ended Queue is empty!\n");
        return;
    }
    int data = deque->array[deque->rear--];
    if (deque->front > deque->rear) {
        deque->front = -1;
        deque->rear = -1;
    }
    printf("Removed %d from rear of Doubly ended queue.\n", data);
    return;
}

// Function to display Deque
void displayDeque(Deque *deque) {
    if (deque->front == -1) {
        printf("Deque is empty!\n");
        return;
    }
    int i;
    for (i = deque->front; i < deque->rear; ++i) {
        printf("%d ", deque->array[i]);
    }
    printf("%d\n", deque->array[i]);
}

int main() {
    int choice, capacity, data;
    CircularQueue *circularQueue = NULL;
    Deque *deque = NULL;

    printf("Enter the capacity of the queue: ");
    scanf("%d", &capacity);

    // Create Circular Queue and Deque with user-defined capacity
    circularQueue = createCircularQueue(capacity);
    deque = createDeque(capacity);

    do {
        printf("\n------ MENU ------\n");
        printf("1. Enqueue in Circular Queue\n");
        printf("2. Dequeue from Circular Queue\n");
        printf("3. Display Circular Queue\n");
        printf("4. Enqueue at Rear in Doubly Ended Queue\n");
        printf("5. Enqueue at Front in Doubly Ended Queue\n");
        printf("6. Dequeue from Front in Doubly Ended Queue\n");
        printf("7. Dequeue from Rear in Doubly Ended Queue\n");
        printf("8. Display Doubly Ended Queue\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to enqueue in circular queue: ");
                scanf("%d", &data);
                enqueueCircular(circularQueue, data);
                break;
            case 2:
                dequeueCircular(circularQueue);
                break;
            case 3:
                printf("Circular Queue: ");
                displayCircularQueue(circularQueue);
                break;
            case 4:
                printf("Enter data to enqueue at rear in Doubly Ended Queue: ");
                scanf("%d", &data);
                enqueueRear(deque, data);
                break;
            case 5:
                printf("Enter data to enqueue at front in Doubly Ended Queue: ");
                scanf("%d", &data);
                enqueueFront(deque, data);
                break;
            case 6:
                dequeueFront(deque);
                break;
            case 7:
                dequeueRear(deque);
                break;
            case 8:
                printf("Doubly Ended Queue: ");
                displayDeque(deque);
                break;
            case 9:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    } while (choice != 9);

    // Free memory allocated for Circular Queue and Deque
    free(circularQueue->array);
    free(circularQueue);
    free(deque->array);
    free(deque);

    return 0;
}
