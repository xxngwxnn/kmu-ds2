#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000000
// 간선 구조체
typedef struct Edge {
    int vertex;
    int weight;
    struct Edge* link;
} Edge;
// 정점 구조체
typedef struct Vertex {
    int num;
    Edge* edge;
} Vertex;
// 노드 구조체
typedef struct Node {
    int vertex;
    int distance;
} Node;

Vertex graph[MAX_VERTICES];
int distance[MAX_VERTICES];
int found[MAX_VERTICES];
int visit_order[MAX_VERTICES];
Node heap[MAX_VERTICES];
int heap_size = 0;

// 정점에서 목적지 정점까지의 가중치를 갖는 간선 추가
void add_edge(int start, int end, int weight) {
    Edge* new_edge = (Edge*)malloc(sizeof(Edge));
    new_edge->vertex = end;
    new_edge->weight = weight;

    new_edge->link = graph[start].edge;
    graph[start].edge = new_edge;
}
// minheap에 삽입하는 함수
void insert_heap(int vertex, int distance) {
    int i = ++heap_size;
    while ((i != 1) && (distance < heap[i / 2].distance)) {
        heap[i] = heap[i / 2];
        i /= 2;
    }
    heap[i].vertex = vertex;
    heap[i].distance = distance;
}
// minheap 에서 삭제하고 반환하는 함수
Node delete_heap() {
    int parent, child;
    Node item, temp;
    item = heap[1];
    temp = heap[heap_size--];
    parent = 1;
    child = 2;
    while (child <= heap_size) {
        if ((child < heap_size) && (heap[child].distance > heap[child + 1].distance))
            child++;
        if (temp.distance <= heap[child].distance)
            break;
        heap[parent] = heap[child];
        parent = child;
        child *= 2;
    }
    heap[parent] = temp;
    return item;
}
// Distance, Found 출력
void print_status(int n) {
    int i;
    printf("Distance: ");
    for (i = 0; i < n; i++) {
        if (distance[i] == INF)
            printf(" *");
        else
            printf(" %d", distance[i]);
    }
    printf("\n");
        printf("Found:    ");
    for (i = 0; i < n; i++)
        printf(" %d", found[i]);
    printf("\n\n");
}
// 노드 방문 순서 출력
void print_visit_order(int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%d ", visit_order[i] + 1);
    }
    printf("\n");
}
// Dijkstra 알고리즘
void shortest_path(int start, int n) {
    int i, u, w;
    Edge* edge;
    int count = 0;

    for (i = 0; i < n; i++) {
        distance[i] = INF;
    }

    distance[start] = 0;
    insert_heap(start, 0);

    while (heap_size != 0) {
        Node min_node = delete_heap();
        u = min_node.vertex;

        if (found[u]) continue;

        edge = graph[u].edge;
        while (edge != NULL) {
            w = edge->vertex;
            if (!found[w] && distance[u] + edge->weight < distance[w]) {
                distance[w] = distance[u] + edge->weight;
                insert_heap(w, distance[w]);
            }
            edge = edge->link;
        }

        found[u] = TRUE;
        visit_order[count++] = u;
        print_status(n);
    }
    print_visit_order(n);
}


int main(int argc, char* argv[]) {
    int n = 10;

    add_edge(0, 1, 3);
    add_edge(0, 5, 11);
    add_edge(0, 6, 12);
    add_edge(1, 0, 3);
    add_edge(1, 2, 5);
    add_edge(1, 3, 4);
    add_edge(1, 4, 1);
    add_edge(1, 5, 7);
    add_edge(1, 6, 8);
    add_edge(2, 1, 5);
    add_edge(2, 3, 2);
    add_edge(2, 6, 6);
    add_edge(2, 7, 5);
    add_edge(3, 1, 4);
    add_edge(3, 2, 2);
    add_edge(3, 4, 13);
    add_edge(3, 7, 14);
    add_edge(3, 9, 16);
    add_edge(4, 1, 1);
    add_edge(4, 3, 13);
    add_edge(4, 5, 9);
    add_edge(4, 8, 18);
    add_edge(4, 9, 17);
    add_edge(5, 0, 11);
    add_edge(5, 1, 7);
    add_edge(5, 4, 9);
    add_edge(6, 0, 12);
    add_edge(6, 1, 8);
    add_edge(6, 2, 6);
    add_edge(6, 7, 13);
    add_edge(7, 2, 5);
    add_edge(7, 3, 14);
    add_edge(7, 6, 13);
    add_edge(7, 9, 15);
    add_edge(8, 4, 18);
    add_edge(8, 9, 10);
    add_edge(9, 3, 16);
    add_edge(9, 4, 17);
    add_edge(9, 7, 15);
    add_edge(9, 8, 10);

    printf("Dijkstra Algorithm \n");
        shortest_path(0, n);
    return 0;
}
