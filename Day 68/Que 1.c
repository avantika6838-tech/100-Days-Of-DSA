// Problem: Implement topological sorting using in-degree array and queue (Kahnâ€™s Algorithm).

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int* topoSort(int V, int adj[MAX][MAX], int* returnSize) {
    int indegree[MAX] = {0};

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (adj[i][j]) {
                indegree[j]++;
            }
        }
    }

    int queue[MAX];
    int front = 0, rear = 0;

    for (int i = 0; i < V; i++) {
        if (indegree[i] == 0) {
            queue[rear++] = i;
        }
    }

    int* result = (int*)malloc(V * sizeof(int));
    int count = 0;

    while (front < rear) {
        int node = queue[front++];
        result[count++] = node;

        for (int j = 0; j < V; j++) {
            if (adj[node][j]) {
                indegree[j]--;
                if (indegree[j] == 0) {
                    queue[rear++] = j;
                }
            }
        }
    }

    if (count != V) {
        *returnSize = 0;
        return result;
    }

    *returnSize = count;
    return result;
}
