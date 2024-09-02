/**
* Problem Statement:
*  Develop a menu driven program to implement Binary Search tree with the following operations. 
i) Construction 
ii) Traversals (Pre, In and Post Order) 
iii) Searching a node by key and deleting if exists(node to be deleted may be leaf or non- leaf with one child or two children)
 */
#include<stdio.h>
#include<stdlib.h>

typedef struct node {
    int data;
    struct node *left, *right;
} *TreeNode;

TreeNode createNode(int data, TreeNode left, TreeNode right) {
    TreeNode newNode = (TreeNode)malloc(sizeof(struct node));

    if (newNode == NULL) {
        printf("\nMemory Alloaction Failed...\n");
        exit(1);
    } else {
        newNode->data = data, newNode->left = left, newNode->right = right;
        return newNode;
    }
}

TreeNode insertNode(TreeNode root, int data) {
    if (root == NULL) {
        return createNode(data, NULL, NULL);
    } else {
        if (root->data <= data) {
            root->right = insertNode(root->right, data);
        } else if (root->data > data) {
            root->left = insertNode(root->left, data);
        }

        return root;
    }
}

// Function to search for a key in BST
struct node* search(struct node* root, int key) {
    if (root == NULL || root->data == key)
        return root;
    
    if (root->data < key)
        return search(root->right, key);
    
    return search(root->left, key);
}

// Function to find the minimum value node in a BST
struct node* minValueNode(struct node* node) {
    struct node* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

// Function to delete a node with given key from BST
struct node* deleteNode(struct node* root, int key) {
    if (root == NULL)
        return root;

    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            struct node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct node* temp = root->left;
            free(root);
            return temp;
        }

        struct node* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

void preorderTraversal(TreeNode root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

void inorderTraversal(TreeNode root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

void postorderTraversal(TreeNode root) {
    if (root != NULL) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%d ", root->data);
    }
}

void freeTree(TreeNode root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

void main() {
    TreeNode root = NULL;
    int data, choice, key;

    do {
        printf("\n******* MENU *******\n");
        printf("1. Insert a Node into the Tree.\n");
        printf("2. Get the Preorder Traversal.\n");
        printf("3. Get the Inorder Traversal.\n");
        printf("4. Get the Postorder Traversal.\n");
        printf("5. Delete by key\n");
        printf("6. Exit\n");
        printf("\nEnter Your Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nEnter the data to be inserted: ");
                scanf("%d", &data);
                root = insertNode(root, data);
                printf("\nSuccessfully Inserted a Node...");
                break;
            
            case 2:
                printf("\nPreorder Traversal: ");
                if(root == NULL){
                    printf("Tree is empty\n");
                }else{
                    preorderTraversal(root);
                }
                break;

            case 3:
                printf("\nInorder Traversal: ");
                if(root == NULL){
                    printf("Tree is empty\n");
                }else{
                    inorderTraversal(root);
                }

            case 4:
                printf("\nPostorder Traversal: ");
                if(root == NULL){
                    printf("Tree is empty\n");
                }else{
                    postorderTraversal(root);
                }

            case 5: 
                printf("Enter the key to delete: ");
                scanf("%d", &key);
                if (search(root, key) != NULL){
                    root = deleteNode(root, key);
                    printf("Node with %d data deleted\n", key);
                }else{
                    printf("Node with %d value not found\n", key);
                }
                break;

            case 6:
                printf("\nThank You...");
                break;

            default:
                printf("\nInvalid Choice...");
        }

        printf("\n");
    } while (choice != 6);

    freeTree(root);
}