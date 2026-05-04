/*Problem: Perform DFS starting from a given source vertex using recursion.

Input:
- n
- adjacency list
- starting vertex s

Output:
- DFS traversal order
*/

#include <stdio.h>
#include <stdlib.h>

void dfs(int v, int n, int** adj, int* colSize, int* visited) {
    visited[v] = 1;
    printf("%d ", v);

    for (int i = 0; i < colSize[v]; i++) {
        int neighbor = adj[v][i];
        if (!visited[neighbor]) {
            dfs(neighbor, n, adj, colSize, visited);
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);

    int** adj = (int**)malloc(n * sizeof(int*));
    int* colSize = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        int m;
        scanf("%d", &m); // number of neighbors
        colSize[i] = m;

        adj[i] = (int*)malloc(m * sizeof(int));
        for (int j = 0; j < m; j++) {
            scanf("%d", &adj[i][j]);
        }
    }

    int s;
    scanf("%d", &s);

    int* visited = (int*)calloc(n, sizeof(int));

    dfs(s, n, adj, colSize, visited);

    return 0;
}
