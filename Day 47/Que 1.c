/*Problem: Height of Binary Tree

Implement the solution for this problem.

Input:
- Input specifications

Output:
- Output specifications
*/

#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* newNode(int val) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = node->right = NULL;
    return node;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(struct TreeNode* root) {
    if (root == NULL)
        return 0;

    int left = height(root->left);
    int right = height(root->right);

    return 1 + max(left, right);
}

int main() {
    struct TreeNode* root = newNode(3);
    root->left = newNode(9);
    root->right = newNode(20);
    root->right->left = newNode(15);
    root->right->right = newNode(7);

    printf("%d", height(root));

    return 0;
}
