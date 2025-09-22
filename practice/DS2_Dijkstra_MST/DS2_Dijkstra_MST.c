#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES	100	
#define INF	1000000	/* 무한대 (연결이 없는 경우) */

// Graph 구조체
typedef struct GraphType {
	int n;	// 정점의 개수
	int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int distance[MAX_VERTICES];/* 시작정점으로부터의 최단경로 거리 */
int found[MAX_VERTICES];		/* 방문한 정점 표시 */
int visit_order[MAX_VERTICES]; /* 방문 순서 기록 */

// 가장 짧은 거리의 노드를 찾아 리턴
int choose(int distance[], int n, int found[]) {
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for (i = 0; i < n; i++)
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			minpos = i;
		}
	return minpos;
}

// distance, found 배열 출력
void print_status(GraphType* g) {
	int i;
	printf("Distance: ");
	for (i = 0; i < g->n; i++) {
		if (distance[i] == INF)
			printf(" *");
		else
			printf(" %d", distance[i]);
	}
	printf("\n");
	printf("Found:    ");
	for (i = 0; i < g->n; i++)
		printf(" %d", found[i]);
	printf("\n\n");
}

// 방문한 노드 순서 출력
void print_visit_order(GraphType* g) {
	int i;
	for (i = 0; i < g->n; i++) {
		printf("%d ", visit_order[i] + 1); // 노드 번호는 1부터 시작
	}
	printf("\n");
}

// Dijkstra 알고리즘
void shortest_path(GraphType* g, int start) {
	int i, u, w;
	int count = 0; // 방문 순서를 세기 위한 카운터
	for (i = 0; i < g->n; i++) /* 초기화 */
	{
		distance[i] = g->weight[start][i];
		found[i] = FALSE;
	}
	found[start] = TRUE;    /* 시작 정점 방문 표시 */
	distance[start] = 0;
	visit_order[count++] = start; // 시작 노드 방문 순서 기록
	for (i = 0; i < g->n - 1; i++) {
		print_status(g);
		u = choose(distance, g->n, found);
		found[u] = TRUE;
		visit_order[count++] = u; // 방문 노드 순서 기록
		for (w = 0; w < g->n; w++)
			if (!found[w])
				if (distance[u] + g->weight[u][w] < distance[w])
					distance[w] = distance[u] + g->weight[u][w];
	}
	print_visit_order(g); // 방문 순서 출력
}

int main(int argc, char* argv[]) {
	GraphType g = { 10,
		{{ 0, 3, INF, INF, INF, 11, 12, INF, INF, INF },
		{ 3, 0, 5, 4, 1, 7, 8, INF, INF, INF },
		{ INF, 5, 0, 2, INF, INF, 6, 5, INF, INF },
		{ INF, 4, 2, 0, 13, INF, INF, 14, INF, 16 },
		{ INF, 1, INF, 13, 0, 9, INF, INF, 18, 17 },
		{ 11, 7, INF, INF, 9, 0, INF, INF, INF, INF },
		{ 12, 8, 6, INF, INF, INF, 0, 13, INF, INF },
		{ INF, INF, 5, 14, INF, INF, 13, 0, INF, 15 },
		{ INF, INF, INF, INF, 18, INF, INF, INF, 0, 10 },
		{ INF, INF, INF, 16, 17, INF, INF, INF, 15, 10, 0 }}
	};
	printf("Dijkstra Algorithm \n");
	shortest_path(&g, 0);
	return 0;
}
