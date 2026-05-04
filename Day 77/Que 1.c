/* Problem Statement
Using BFS or DFS, check if the entire graph is connected.

Input Format
n m
edges

Output Format
CONNECTED
NOT CONNECTED

Sample Input
4 2
1 2
3 4

Sample Output
NOT CONNECTED
*/

#include <stdio.h>
#include <stdlib.h>

void dfs(int node, int* visited, int** graph, int* graphSize) {
    visited[node] = 1;

    for (int i = 0; i < graphSize[node]; i++) {
        int neighbor = graph[node][i];
        if (!visited[neighbor]) {
            dfs(neighbor, visited, graph, graphSize);
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int* graphSize = (int*)calloc(n + 1, sizeof(int));
    int u, v;

    int edges[m][2];

    for (int i = 0; i < m; i++) {
        scanf("%d %d", &u, &v);
        edges[i][0] = u;
        edges[i][1] = v;
        graphSize[u]++;
        graphSize[v]++;
    }

    int** graph = (int**)malloc((n + 1) * sizeof(int*));
    for (int i = 1; i <= n; i++) {
        graph[i] = (int*)malloc(graphSize[i] * sizeof(int));
        graphSize[i] = 0;
    }

    for (int i = 0; i < m; i++) {
        u = edges[i][0];
        v = edges[i][1];

        graph[u][graphSize[u]++] = v;
        graph[v][graphSize[v]++] = u;
    }

    int* visited = (int*)calloc(n + 1, sizeof(int));

    dfs(1, visited, graph, graphSize);

    int connected = 1;
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            connected = 0;
            break;
        }
    }

    if (connected)
        printf("CONNECTED\n");
    else
        printf("NOT CONNECTED\n");

    return 0;
}
