/* Problem Statement:
Construct a binary tree from given inorder and postorder traversal arrays.

Input Format:
- First line contains integer N
- Second line contains inorder traversal
- Third line contains postorder traversal

Output Format:
- Print preorder traversal of constructed tree

Example:
Input:
5
4 2 5 1 3
4 5 2 3 1

Output:
1 2 4 5 3

Explanation:
Postorder gives root at end, inorder divides left and right subtrees.
*/

#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode* newNode(int val) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = node->right = NULL;
    return node;
}

int findIndex(int inorder[], int start, int end, int val) {
    for (int i = start; i <= end; i++) {
        if (inorder[i] == val)
            return i;
    }
    return -1;
}


struct TreeNode* build(int inorder[], int postorder[], int inStart, int inEnd, int *postIndex) {
    if (inStart > inEnd)
        return NULL;

    int val = postorder[*postIndex];
    (*postIndex)--;

    struct TreeNode* root = newNode(val);

    if (inStart == inEnd)
        return root;

    int index = findIndex(inorder, inStart, inEnd, val);

    root->right = build(inorder, postorder, index + 1, inEnd, postIndex);
    root->left  = build(inorder, postorder, inStart, index - 1, postIndex);

    return root;
}

void preorder(struct TreeNode* root) {
    if (root == NULL)
        return;

    printf("%d ", root->val);
    preorder(root->left);
    preorder(root->right);
}

int main() {
    int n;
    scanf("%d", &n);

    int inorder[n], postorder[n];

    for (int i = 0; i < n; i++)
        scanf("%d", &inorder[i]);

    for (int i = 0; i < n; i++)
        scanf("%d", &postorder[i]);

    int postIndex = n - 1;

    struct TreeNode* root = build(inorder, postorder, 0, n - 1, &postIndex);

    preorder(root);

    return 0;
}
