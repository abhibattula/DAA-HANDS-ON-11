#include <stdio.h>
#include <stdlib.h>

// Define color constants
#define RED   0
#define BLACK 1

// Define a structure for tree node
struct TreeNode 
{
    int key;
    int color;
    struct TreeNode *left;
    struct TreeNode *right;
    struct TreeNode *parent;
};

// Function to create a new node
struct TreeNode* createNode(int key) 
{
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->key = key;
    newNode->color = RED; // New nodes are always RED
    newNode->left = newNode->right = newNode->parent = NULL;
    return newNode;
}

// Function to perform left rotation
void leftRotate(struct TreeNode** root, struct TreeNode* x) 
{
    struct TreeNode* y = x->right;
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

// Function to perform right rotation
void rightRotate(struct TreeNode** root, struct TreeNode* y) 
{
    struct TreeNode* x = y->left;
    y->left = x->right;
    if (x->right != NULL)
        x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == NULL)
        *root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
    x->right = y;
    y->parent = x;
}

// Function to fix violations caused by insertion
void fixViolation(struct TreeNode** root, struct TreeNode* z) 
{
    while (z != *root && z->parent->color == RED) 
    {
        if (z->parent == z->parent->parent->left) 
        {
            struct TreeNode* y = z->parent->parent->right;
            if (y != NULL && y->color == RED) 
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else 
            {
                if (z == z->parent->right) 
                {
                    z = z->parent;
                    leftRotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(root, z->parent->parent);
            }
        } else 
        {
            struct TreeNode* y = z->parent->parent->left;
            if (y != NULL && y->color == RED) 
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else 
            {
                if (z == z->parent->left) 
                {
                    z = z->parent;
                    rightRotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(root, z->parent->parent);
            }
        }
    }
    (*root)->color = BLACK;
}

// Function to insert a key into RBT
void insert(struct TreeNode** root, int key) 
{
    struct TreeNode* z = createNode(key);
    struct TreeNode* y = NULL;
    struct TreeNode* x = *root;
    while (x != NULL) 
    {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if (y == NULL)
        *root = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;
    fixViolation(root, z);
}

// Function to perform inorder traversal of RBT
void inorderTraversal(struct TreeNode* root) 
{
    if (root != NULL) 
    {
        inorderTraversal(root->left);
        printf("%d(%s) ", root->key, root->color == RED ? "RED" : "BLACK");
        inorderTraversal(root->right);
    }
}

// Function to search for a key in RBT
struct TreeNode* search(struct TreeNode* root, int key) {
    // Base Cases: root is null or key is present at root
    if (root == NULL || root->key == key)
        return root;

    // Key is greater than root's key
    if (root->key < key)
        return search(root->right, key);

    // Key is smaller than root's key
    return search(root->left, key);
}

int main() {
    struct TreeNode* root = NULL;
    int choice, key;
    do {
        printf("\nRed-Black Tree Operations:\n");
        printf("1. Insert\n");
        printf("2. Display (Inorder Traversal)\n");
        printf("3. Search\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                insert(&root, key);
                printf("Key %d inserted into the Red-Black Tree.\n", key);
                break;
            case 2:
                printf("Inorder traversal of the Red-Black Tree: ");
                inorderTraversal(root);
                printf("\n");
                break;
            case 3:
                printf("Enter key to search: ");
                scanf("%d", &key);
                struct TreeNode* result = search(root, key);
                if (result)
                    printf("%d found in the Red-Black Tree\n", key);
                else
                    printf("%d not found in the Red-Black Tree\n", key);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid choice.\n");
        }
    } while (choice != 4);

    return 0;
}
