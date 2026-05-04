/ Problem: Print topological ordering of a Directed Acyclic Graph (DAG) using DFS.

#include <stdio.h>
#include <stdlib.h>

void dfs(int node, int** graph, int* graphSize, int* visited, int* stack, int* top) {
    visited[node] = 1;

    for(int i = 0; i < graphSize[node]; i++) {
        int neighbor = graph[node][i];
        if(!visited[neighbor]) {
            dfs(neighbor, graph, graphSize, visited, stack, top);
        }
    }

    stack[(*top)++] = node;
}

void topoSort(int V, int** graph, int* graphSize) {
    int* visited = (int*)calloc(V, sizeof(int));
    int* stack = (int*)malloc(V * sizeof(int));
    int top = 0;

    for(int i = 0; i < V; i++) {
        if(!visited[i]) {
            dfs(i, graph, graphSize, visited, stack, &top);
        }
    }

    for(int i = top - 1; i >= 0; i--) {
        printf("%d ", stack[i]);
    }
}

int main() {
    int V = 6;

    int** graph = (int**)malloc(V * sizeof(int*));
    int* graphSize = (int*)calloc(V, sizeof(int));

    for(int i = 0; i < V; i++) {
        graph[i] = (int*)malloc(V * sizeof(int));
    }

    graph[5][graphSize[5]++] = 2;
    graph[5][graphSize[5]++] = 0;
    graph[4][graphSize[4]++] = 0;
    graph[4][graphSize[4]++] = 1;
    graph[2][graphSize[2]++] = 3;
    graph[3][graphSize[3]++] = 1;

    topoSort(V, graph, graphSize);

    return 0;
}
