//Program to implement array using dynamic memory allocation and do the below opertations
//1. Insert by position
//2. Delete by key
//3. Search by position
//4. Reverse the contents
#include<stdio.h>
#include<stdlib.h>

int i;

void create(int **arr, int *capacity) {
    *arr = (int *)malloc(*capacity * sizeof(int));
    if (*arr == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
}

void reallocation(int **arr, int *capacity) {
    *arr = (int *)realloc(*arr, (2 * (*capacity)) * sizeof(int));
    if (*arr == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    *capacity = *capacity * 2;
}

int searchByPosition(int arr[], int size, int position) {
    if (position >= 1 && position <= size) {
        return arr[position - 1];
    } else {
        return -1;
    }
}

void displayArray(int arr[], int size) {
    if(size == 0){
        printf("Array is empty\n");
        return;
    }
    printf("Array elements: ");
    for (i = 0; i < size; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int searchByKey(int arr[], int size, int key) {
    for (i = 0; i < size; ++i) {
        if (arr[i] == key) {
            return i+1;
        }
    }
    return -1;
}

void reverseArray(int arr[], int size) {
    int temp;
    for (i = 0; i < size / 2; ++i) {
        temp = arr[i];
        arr[i] = arr[size - 1 - i];
        arr[size - 1 - i] = temp;
    }
    displayArray(arr,size);
}

void deleteByKey(int arr[], int *size, int key) {
    if(*size == 0){
        printf("Array is empty\n");
        return;
    }
    int position = searchByKey(arr, *size, key);

    if (position != -1) {
        for(i = position-1; i< *size; i++){
            arr[i] = arr[i+1];
        }
        *size = *size - 1;
        printf("Element deleted successfully.\n");
        displayArray(arr,*size);
    } else {
        printf("Key not found. Deletion failed.\n");
    }
}

void insertByPosition(int arr[], int *size, int position, int element, int* cap) {
    if (position < 1 || position > *size + 1) {
        printf("Invalid position. Insertion failed.\n");
        return;
    }

    if(*size + 1 > *cap){
        printf("Array is full. Allocating more memory dynamically..\n");
        reallocation(&arr, cap);
    }

    *size += 1;

    for (i = *size - 1; i > position - 1; --i) {
        arr[i] = arr[i - 1];
    }

    arr[position - 1] = element;
    printf("Element inserted successfully.\n");
    displayArray(arr,*size);
}


int main() {
    int *arr, size, choice, position, element, key, capacity;

    printf("Enter the capacity of the array: ");
    scanf("%d", &capacity);

    create(&arr, &capacity); 

    printf("Enter the size of the array:\n");
    scanf("%d", &size);

    printf("Enter %d elements for the array:\n", size);
    for (i = 0; i < size; ++i) {
        scanf("%d", &arr[i]);
    }

    do {
        printf("\n--- MENU ---\n");
        printf("1. Insert by position\n");
        printf("2. Delete by key\n");
        printf("3. Search by position\n");
        printf("4. Reverse the contents\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter position and element to insert: ");
                scanf("%d %d", &position, &element);
                insertByPosition(arr, &size, position, element, &capacity);
                break;

            case 2:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                deleteByKey(arr, &size, key);
                break;

            case 3:
                printf("Enter position to search: ");
                scanf("%d", &position);
                key = searchByPosition(arr, size, position);
                if (key != -1) {
                    printf("Element at position %d is %d.\n", position, key);
                } else {
                    printf("Invalid position.\n");
                }
                displayArray(arr,size);
                break;

            case 4:
                printf("Array reversed successfully.\n");
                reverseArray(arr, size);
                break;

            case 5:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 5);

    free(arr);

    return 0;
}
