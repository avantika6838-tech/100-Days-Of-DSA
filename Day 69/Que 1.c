// Problem: Given weighted graph with non-negative edges, compute shortest path from source using priority queue.

#include <limits.h>
#include <stdlib.h>

typedef struct Node {
    int v, w;
    struct Node* next;
} Node;

typedef struct {
    int v, dist;
} HeapNode;

typedef struct {
    int size, capacity;
    HeapNode* arr;
} MinHeap;

Node* createNode(int v, int w) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->v = v;
    node->w = w;
    node->next = NULL;
    return node;
}

void addEdge(Node** adj, int u, int v, int w) {
    Node* node = createNode(v, w);
    node->next = adj[u];
    adj[u] = node;
}

MinHeap* createHeap(int cap) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->size = 0;
    heap->capacity = cap;
    heap->arr = (HeapNode*)malloc(cap * sizeof(HeapNode));
    return heap;
}

void swap(HeapNode* a, HeapNode* b) {
    HeapNode t = *a;
    *a = *b;
    *b = t;
}

void heapifyUp(MinHeap* heap, int i) {
    while (i && heap->arr[(i - 1) / 2].dist > heap->arr[i].dist) {
        swap(&heap->arr[i], &heap->arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void heapifyDown(MinHeap* heap, int i) {
    int smallest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < heap->size && heap->arr[l].dist < heap->arr[smallest].dist)
        smallest = l;
    if (r < heap->size && heap->arr[r].dist < heap->arr[smallest].dist)
        smallest = r;

    if (smallest != i) {
        swap(&heap->arr[i], &heap->arr[smallest]);
        heapifyDown(heap, smallest);
    }
}

void push(MinHeap* heap, int v, int dist) {
    heap->arr[heap->size].v = v;
    heap->arr[heap->size].dist = dist;
    heapifyUp(heap, heap->size);
    heap->size++;
}

HeapNode pop(MinHeap* heap) {
    HeapNode root = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;
    heapifyDown(heap, 0);
    return root;
}

int isEmpty(MinHeap* heap) {
    return heap->size == 0;
}

void dijkstra(Node** adj, int n, int src, int* dist) {
    MinHeap* heap = createHeap(n * n);

    for (int i = 0; i < n; i++)
        dist[i] = INT_MAX;

    dist[src] = 0;
    push(heap, src, 0);

    while (!isEmpty(heap)) {
        HeapNode node = pop(heap);
        int u = node.v;

        Node* temp = adj[u];
        while (temp) {
            int v = temp->v;
            int w = temp->w;

            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                push(heap, v, dist[v]);
            }
            temp = temp->next;
        }
    }
}
