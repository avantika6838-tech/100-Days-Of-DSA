/*Problem Statement
Find shortest distances from source vertex in a weighted graph with non-negative weights.

Input Format
n m
u v w
source

Output Format
Distances to all vertices.

Sample Input
5 6
1 2 2
1 3 4
2 3 1
2 4 7
3 5 3
4 5 1
1

Sample Output
0 2 3 9 6

Explanation
Shortest distances computed via priority queue.
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 1005

typedef struct {
    int node;
    int dist;
} Pair;

Pair heap[MAX];
int size = 0;

// Swap
void swap(Pair *a, Pair *b) {
    Pair temp = *a;
    *a = *b;
    *b = temp;
}

// Push into Min Heap
void push(Pair val) {
    heap[++size] = val;
    int i = size;

    while (i > 1 && heap[i].dist < heap[i/2].dist) {
        swap(&heap[i], &heap[i/2]);
        i /= 2;
    }
}

// Pop from Min Heap
Pair pop() {
    Pair top = heap[1];
    heap[1] = heap[size--];

    int i = 1;
    while (1) {
        int left = 2*i, right = 2*i+1, smallest = i;

        if (left <= size && heap[left].dist < heap[smallest].dist)
            smallest = left;
        if (right <= size && heap[right].dist < heap[smallest].dist)
            smallest = right;

        if (smallest != i) {
            swap(&heap[i], &heap[smallest]);
            i = smallest;
        } else break;
    }
    return top;
}

// Graph
typedef struct Node {
    int v, w;
    struct Node* next;
} Node;

Node* adj[MAX];

// Add edge
void addEdge(int u, int v, int w) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->v = v;
    temp->w = w;
    temp->next = adj[u];
    adj[u] = temp;
}

// Dijkstra
void dijkstra(int n, int src) {
    int dist[MAX];

    for (int i = 1; i <= n; i++)
        dist[i] = INT_MAX;

    dist[src] = 0;
    push((Pair){src, 0});

    while (size > 0) {
        Pair p = pop();
        int node = p.node;
        int d = p.dist;

        if (d > dist[node]) continue;

        Node* temp = adj[node];
        while (temp) {
            int v = temp->v;
            int w = temp->w;

            if (dist[node] + w < dist[v]) {
                dist[v] = dist[node] + w;
                push((Pair){v, dist[v]});
            }
            temp = temp->next;
        }
    }

    // Print result
    for (int i = 1; i <= n; i++)
        printf("%d ", dist[i]);
}

// Main
int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < MAX; i++)
        adj[i] = NULL;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        addEdge(u, v, w);
        addEdge(v, u, w); // remove if directed
    }

    int src;
    scanf("%d", &src);

    dijkstra(n, src);

    return 0;
}
