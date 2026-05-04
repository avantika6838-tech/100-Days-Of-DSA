/*Problem Statement:
Check whether a given binary tree satisfies the Min-Heap property.

Input Format:
- First line contains integer N
- Second line contains level-order traversal

Output Format:
- Print YES if valid Min-Heap, otherwise NO

Example:
Input:
7
1 3 5 7 9 8 10

Output:
YES

Explanation:
Each parent node must be smaller than its children.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

bool isComplete(struct TreeNode* root, int index, int totalNodes) {
    if (root == NULL)
        return true;

    if (index >= totalNodes)
        return false;

    return isComplete(root->left, 2 * index + 1, totalNodes) &&
           isComplete(root->right, 2 * index + 2, totalNodes);
}

bool isMinHeap(struct TreeNode* root) {
    if (root == NULL)
        return true;

    if (root->left == NULL && root->right == NULL)
        return true;

    if (root->right == NULL) {
        return (root->val <= root->left->val) &&
               isMinHeap(root->left);
    }

    if (root->val <= root->left->val &&
        root->val <= root->right->val) {
        return isMinHeap(root->left) &&
               isMinHeap(root->right);
    }

    return false;
}

int main() {
    int n;
    scanf("%d", &n);

    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    struct TreeNode* nodes[n];
    for (int i = 0; i < n; i++) {
        nodes[i] = newNode(arr[i]);
    }

    for (int i = 0; i < n; i++) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n)
            nodes[i]->left = nodes[left];
        if (right < n)
            nodes[i]->right = nodes[right];
    }

    struct TreeNode* root = nodes[0];

    if (isComplete(root, 0, n) && isMinHeap(root))
        printf("YES\n");
    else
        printf("NO\n");

    return 0;
}
