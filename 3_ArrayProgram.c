//Program to implement array using dynamic memory allocation and do the below opertations
//1. Insert by order
//2. Delete by position
//3. Search by key
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

void reverseArray(int arr[], int *size) {
    int temp;
    int size_temp = *size;
    for (i = 0; i < size_temp / 2; ++i) {
        temp = arr[i];
        arr[i] = arr[size_temp - 1 - i];
        arr[size_temp - 1 - i] = temp;
    }
}

void insertByOrder(int arr[], int *size, int element, int* capacity) {
    if(*size+1 > *capacity){
        printf("Array is full. Allocating more memory dynamically..\n");
        reallocation(&arr, capacity);
    }
    int flag = 0;
    if(arr[0]>=arr[1]){
        flag = 1;
        reverseArray(arr,size);
    }
    for (i = *size - 1; i >= 0 && arr[i] > element; --i) {
        arr[i + 1] = arr[i];
    }
    arr[i + 1] = element;
    *size += 1;

    if(flag == 1){
        reverseArray(arr,size);
    }

    printf("Element inserted successfully.\n");
    displayArray(arr,*size);
}

void deleteByPosition(int arr[], int *size, int position) {
    if(*size == 0){
        printf("Array is empty\n");
        return;
    }
    if (position < 1 || position > *size) {
        printf("Invalid position. Deletion failed.\n");
        return;
    }

    for (i = position - 1; i < *size - 1; ++i) {
        arr[i] = arr[i + 1];
    }
    *size -= 1;
    printf("Element deleted successfully.\n");
    displayArray(arr,*size);
}

int searchByKey(int arr[], int size, int key) {
    for (i = 0; i < size; ++i) {
        if (arr[i] == key) {
            return i+1;
        }
    }
    return -1;
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
        printf("1. Insert by order\n");
        printf("2. Delete by position\n");
        printf("3. Search by key\n");
        printf("4. Reverse the contents\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter element to insert by order: ");
                scanf("%d", &element);
                insertByOrder(arr, &size, element, &capacity);
                break;

            case 2:
                printf("Enter position to delete: ");
                scanf("%d", &position);
                deleteByPosition(arr, &size, position);
                break;

            case 3:
                printf("Enter key to search: ");
                scanf("%d", &key);
                position = searchByKey(arr, size, key);
                if (position != -1) {
                    printf("Key found at position %d.\n", position);
                } else {
                    printf("Key not found.\n");
                }
                break;

            case 4:
                printf("Array reversed successfully.\n");
                reverseArray(arr,&size);
                displayArray(arr,size);
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
