/*
Develop a menu driven program to implement the following types of Queues by allocating memory dynamically. 
i) Circular Queue 
ii) Priority Queue 
Note: Define Queue structure and implement the operation with array representation
*/

#include <stdio.h>
#include <stdlib.h>

// Structure for Circular Queue
typedef struct {
    int front, rear, capacity;
    int *array;
} CircularQueue;

// Structure for Priority Queue
typedef struct {
    int front, rear, capacity;
    int *array;
} PriorityQ;

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
PriorityQ* createPriorityque(int capacity) {
    PriorityQ *pq = (PriorityQ*)malloc(sizeof(PriorityQ));
    if(pq == NULL){
        printf("Memory allocation failed.\n");
        exit(1);
    }
    pq->capacity = capacity;
    pq->front = pq->rear = -1;
    pq->array = (int*)malloc(pq->capacity * sizeof(int));
    if(pq->array == NULL){
        printf("Memory allocation failed.\n");
        exit(1);
    }
    return pq;
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

// Function to enqueue data at rear end of Priority Queue
void enqueuePriority(PriorityQ *pq, int data) {
    if (pq->rear == pq->capacity - 1) {
        // Queue is full, need to reallocate memory
        printf("Priority Queue is full. Reallocating more memory..\n");
        int newCapacity = pq->capacity * 2;
        pq->array = (int*)realloc(pq->array, newCapacity * sizeof(int));
        if(pq->array == NULL){
            printf("Reallocation failed.\n");
            exit(1);
        }
        pq->capacity = newCapacity;
    }
    int i;
    if (pq->front == -1) {
        pq->front = pq->rear = 0;
        pq->array[pq->rear] = data;
    }else{
        ++pq->rear;
        for(i=pq->rear-1; i>=pq->front && pq->array[i]>data; i--){
            pq->array[i+1] = pq->array[i];
        }
        pq->array[i+1] = data;
    }
    printf("Inserted %d into Priority Queue.\n", data);
}


// Function to dequeue data from front end of Deque
void dequeuePriority(PriorityQ *pq) {
    if (pq->front == -1) {
        printf("Priority Queue is empty!\n");
        return;
    }
    int data = pq->array[pq->front];
    if (pq->front == pq->rear) {
        pq->front = pq->rear = -1;
    } else {
        pq->front++;
    }
    printf("Removed %d from front of Priority queue\n",data);
}

// Function to display Deque
void displayPriorityque(PriorityQ *pq) {
    if (pq->front == -1) {
        printf("Priority Queue is empty!\n");
        return;
    }
    int i;
    for (i = pq->front; i < pq->rear; ++i) {
        printf("%d ", pq->array[i]);
    }
    printf("%d\n", pq->array[i]);
}

int main() {
    int choice, capacity, data;
    CircularQueue *circularQueue = NULL;
    PriorityQ *pq = NULL;

    printf("Enter the capacity of the queue: ");
    scanf("%d", &capacity);

    // Create Circular Queue and Deque with user-defined capacity
    circularQueue = createCircularQueue(capacity);
    pq = createPriorityque(capacity);

    do {
        printf("\n------ MENU ------\n");
        printf("1. Enqueue in Circular Queue\n");
        printf("2. Dequeue from Circular Queue\n");
        printf("3. Display Circular Queue\n");
        printf("4. Enqueue in Priority Queue\n");
        printf("5. Dequeue from Priority Queue\n");
        printf("6. Display Priority Queue\n");
        printf("7. Exit\n");
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
                printf("Enter data to enqueue in Priority Queue: ");
                scanf("%d", &data);
                enqueuePriority(pq, data);
                break;
            case 5:
                dequeuePriority(pq);
                break;
            case 6:
                printf("Priority Queue: ");
                displayPriorityque(pq);
                break;
            case 7:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    } while (choice != 7);

    // Free memory allocated for Circular Queue and Deque
    free(circularQueue->array);
    free(circularQueue);
    free(pq->array);
    free(pq);

    return 0;
}
