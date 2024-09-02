/**
 * Problem Statement:
 *  Develop a menu driven program to implement Binary Search tree with the following operations. 
i)Construction
ii) Traversals (Pre, In and Post Order)
iii) Searching a node by key and displaying its information along with its parent if exists, otherwise a suitable message. 
iv) Counting all nodes. 
v)  Finding height.
vi) Finding node with the Maximum key value and printing the node details along with the parent. 
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

void searchBykey(TreeNode root, int key){
    TreeNode temp = root;
    TreeNode prev = NULL;
    while(temp != NULL){
        if(temp->data == key){
            if(prev == NULL){
                printf("%d is present as root in the Binary Search Tree\n", key);
                return;
            }
            printf("%d found in Binary Search Tree as child of element %d ", key, prev->data);
            return;
        }else{
            prev = temp;
            if(temp->data > key){
                temp = temp->left;
            }else{
                temp = temp->right;
            }
        }
    }
    printf("element %d not found\n", key);
}

int countNode(TreeNode root){
    if(root == NULL){
        //printf("%d Nodes present\n",cnt);
        return 0;
    }
    int rcnt = countNode(root->left);
    //cnt++;
    int lcnt = countNode(root->right);
    return 1+lcnt+rcnt;
}

void Maximum(TreeNode root){
    TreeNode temp = root;
    TreeNode prev = NULL;

    while(temp!=NULL){
        if(temp->right == NULL && prev == NULL){
            printf("%d is the root node which is the maximum element in the BST\n", temp->data );
            return;
        }
        if(temp->right == NULL){
            printf("%d is the node with maximum value with %d being parent node\n", temp->data, prev->data);
            return;
        }else{
            prev = temp;
            temp = temp->right;
        }
    }
}

int depth(TreeNode root){
    if(root == NULL){
        return 0;
    }else{
        int lDepth = depth(root->left);
        int rDepth = depth(root->right);

        if(lDepth > rDepth){
            return lDepth+1;
        }else{
            return rDepth+1;
        }
    }
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
    int data, choice, el, count = 0, height = 0;

    do {
        printf("\n******* MENU *******\n");
        printf("1. Insert a Node into the Tree.\n");
        printf("2. Get the Preorder Traversal.\n");
        printf("3. Get the Inorder Traversal.\n");
        printf("4. Get the Postorder Traversal.\n");
        printf("5. Search by key\n");
        printf("6. Count the number of nodes\n");
        printf("7. Height of the tree\n");
        printf("8. Finding node with maximum key value.\n");
        printf("9. Exit\n");
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
                preorderTraversal(root);
                break;

            case 3:
                printf("\nInorder Traversal: ");
                inorderTraversal(root);
                break;

            case 4:
                printf("\nPostorder Traversal: ");
                postorderTraversal(root);
                break;

            case 5: 
                printf("Enter an element to search: ");
                scanf("%d", &el);
                searchBykey(root, el);
                break;
            
            case 6: 
                count = countNode(root);
                printf("%d Nodes present in BST\n", count);
                break;
            
            case 7: 
                height = depth(root);
                printf("Height of the tree is %d", height);
                break;

            case 8: 
                Maximum(root);
                break;

            case 9:
                printf("\nThank You...");
                break;

            default:
                printf("\nInvalid Choice...");
        }

        printf("\n");
    } while (choice != 9);

    freeTree(root);
}