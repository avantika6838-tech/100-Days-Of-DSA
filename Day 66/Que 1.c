/*Problem: Detect cycle in directed graph using DFS and recursion stack.

Output:
- YES if cycle exists
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool dfs(int node, int** adj, int* adjSize, bool* visited, bool* recStack){
    if (recStack[node]) return true;
    if (visited[node]) return false;

    visited[node] = true;
    recStack[node] = true;

    for (int i = 0; i < adjSize[node]; i++){
        if (dfs(adj[node][i], adj, adjSize, visited, recStack))
            return true;
    }

    recStack[node] = false;
    return false;
}

int main(){
    int V, E;
    scanf("%d %d", &V, &E);

    int** adj = (int**)malloc(V * sizeof(int*));
    int* adjSize = (int*)calloc(V, sizeof(int));

    int u, v;

    int* tempCount = (int*)calloc(V, sizeof(int));
    int (*edges)[2] = malloc(E * sizeof *edges);

    for (int i = 0; i < E; i++) {
        scanf("%d %d", &u, &v);
        edges[i][0] = u;
        edges[i][1] = v;
        tempCount[u]++;
    }

    for(int i = 0; i < V; i++){
        adj[i] = (int*)malloc(tempCount[i] * sizeof(int));
    }

    for(int i = 0; i < E; i++){
        u = edges[i][0];
        v = edges[i][1];
        adj[u][adjSize[u]++] = v;
    }

    bool* visited = (bool*)calloc(V, sizeof(bool));
    bool* recStack = (bool*)calloc(V, sizeof(bool));

    for(int i = 0; i < V; i++){
        if(dfs(i, adj, adjSize, visited, recStack)){
            printf("YES");
            return 0;
        }
    }

    printf("NO");
    return 0;
}
