/* Problem: Perform BFS from a given source using queue.

Input:
- n
- adjacency list
- source s

Output:
- BFS traversal order
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int queue[MAX];
int front = 0, rear = 0;

void enqueue(int x) {
    queue[rear++] = x;
}

int dequeue() {
    return queue[front++];
}

int isEmpty() {
    return front == rear;
}

void bfs(int n, int adj[MAX][MAX], int s) {
    int visited[MAX] = {0};
    
    enqueue(s);
    visited[s] = 1;
    
    while(!isEmpty()) {
        int node = dequeue();
        printf("%d ", node);
        
        for(int i = 0; i < n; i++) {
            if(adj[node][i] == 1 && !visited[i]) {
                enqueue(i);
                visited[i] = 1;
            }
        }
    }
}

int main() {
    int n, m;
    scanf("%d", &n);   
    scanf("%d", &m);   
    
    int adj[MAX][MAX] = {0};
    
    for(int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u][v] = 1;
        adj[v][u] = 1; 
    }
    
    int s;
    scanf("%d", &s);
    
    bfs(n, adj, s);
    
    return 0;
}
