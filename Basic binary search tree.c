#include <stdio.h>
#include <stdlib.h>

// Structure for a node
struct Node 
{
    int data;
    struct Node *left;
    struct Node *right;
};

// Function to create a new node
struct Node *createNode(int value) 
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a new node
struct Node *insert(struct Node *root, int value) 
{
    if (root == NULL) 
    {
        return createNode(value);
    }

    if (value < root->data) 
    {
        root->left = insert(root->left, value);
    } else if (value > root->data) 
    {
        root->right = insert(root->right, value);
    }

    return root;
}

// Function to perform in-order traversal
void inOrderTraversal(struct Node *root) 
{
    if (root != NULL) 
    {
        inOrderTraversal(root->left);
        printf("%d ", root->data);
        inOrderTraversal(root->right);
    }
}

// Function to display the binary search tree
void display(struct Node *root, int level) 
{
    if (root == NULL)
        return;

    display(root->right, level + 1);
    printf("\n");

    for (int i = 0; i < level; i++)
    {
        printf("    ");
    }

    printf("%d\n", root->data);
    display(root->left, level + 1);
}

int main() 
{
    struct Node *root = NULL;
    int choice, value;

    while (1) 
    {
        printf("\nBinary Search Tree Operations:\n");
        printf("1. Insert\n");
        printf("2. In-order Traversal\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);
                break;
            case 2:
                printf("In-order Traversal: ");
                inOrderTraversal(root);
                printf("\n");
                break;
            case 3:
                printf("Displaying Binary Search Tree:\n");
                display(root, 0);
                break;
            case 4:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    }

    return 0;
}
