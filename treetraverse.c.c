#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Define the syntax tree node structure
typedef struct Node {
    char data;
    struct Node *left;
    struct Node *right;
} Node;

// Function to create a new syntax tree node
Node *createNode(char data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to traverse syntax tree and perform arithmetic operations
int evaluateSyntaxTree(Node *root) {
    if (root == NULL) {
        return 0;
    }

    if (isdigit(root->data)) {
        return root->data - '0';
    }

    int leftVal = evaluateSyntaxTree(root->left);
    int rightVal = evaluateSyntaxTree(root->right);

    switch (root->data) {
        case '+':
            return leftVal + rightVal;
        case '-':
            return leftVal - rightVal;
        case '*':
            return leftVal * rightVal;
        case '/':
            if (rightVal != 0) {
                return leftVal / rightVal;
            } else {
                printf("Error: Division by zero\n");
                exit(EXIT_FAILURE);
            }
        default:
            printf("Error: Invalid operator\n");
            exit(EXIT_FAILURE);
    }
}

int main() {
    // Constructing a simple syntax tree for expression: (5 + 3) * 2
    Node *root = createNode('*');
    root->left = createNode('+');
    root->right = createNode('2');
    root->left->left = createNode('5');
    root->left->right = createNode('3');

    // Evaluate the syntax tree
    int result = evaluateSyntaxTree(root);
    printf("Result: %d\n", result);

    return 0;
}
