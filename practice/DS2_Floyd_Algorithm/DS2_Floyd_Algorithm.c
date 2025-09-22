#include <stdio.h>
#include <stdlib.h>

#define MAX	100	
#define INF	1000000	/* 무한대 (연결이 없는 경우) */

int distance[MAX][MAX];
int path[MAX][MAX];


// Graph 구조체
typedef struct GraphType {
	int n;	// 정점의 개수
	int weight[MAX][MAX];
} GraphType;

// Graph 생성
GraphType* create_graph() {
	return (GraphType*)malloc(sizeof(GraphType));
}

// Graph 초기화
void init_g_m(GraphType* g) {
	g->n = 0;
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			g->weight[i][j] = 0;
		}
	}
}

// 최단 거리 출력
void print_distance(GraphType* g, int start, int end) {
	printf("Shortest Distance : %d\n", distance[start - 1][end - 1]);
}

// 최단 경로 출력
void print_path(int start, int end) {
	if (path[start][end] != -1) {
		print_path(start, path[start][end]);
		printf(" ");
		print_path(path[start][end], end);
	} else {
		printf("%d", end + 1);
	}
}

// 최단 경로 출력
void print_shortestpath(GraphType* g, int start, int end) {
	printf("Shortest path node : %d ", start);
	print_path(start - 1, end - 1);
	printf("\n");
}

// floyd 알고리즘
void floyd(GraphType* g) {
	int i, j, k;
	for (i = 0; i < g->n; i++) {
		for (j = 0; j < g->n; j++) {
			distance[i][j] = g->weight[i][j];
			path[i][j] = -1;
		}
	}
	for (k = 0; k < g->n; k++) {
		for (i = 0; i < g->n; i++) {
			for (j = 0; j < g->n; j++) {
				if (distance[i][j] > distance[i][k] + distance[k][j]) {
					distance[i][j] = distance[i][k] + distance[k][j];
					path[i][j] = k;
				}
			}
		}
	}
}

// 인접행렬을 사용한 실습 그래프 생성
GraphType* MakeGraph() {
	GraphType* g = create_graph();
	init_g_m(g);
	g->n = 10;
	int weight[10][10] = {
		{0, 3, INF, INF, INF, 11, 12, INF, INF, INF}, //1
		{3, 0, 5, 4, 1, 7, 8, INF, INF, INF}, // 2
		{INF, 5, 0, 2, INF, INF, 6, 5, INF, INF}, // 3
		{INF, 4, 2, 0, 13, INF, INF, 14, INF, 16}, // 4
		{INF, 1, INF, 13, 0, 9, INF, INF, 18, 17}, // 5
		{11, 7, INF, INF, 9, 0, INF, INF, INF, INF}, // 6
		{12, 8, 6, INF, INF, INF, 0, 13, INF, INF}, // 7
		{INF, INF, 5, 14, INF, INF, 13, 0, INF, 15}, // 8
		{INF, INF, INF, INF, 18, INF, INF, INF, 0, 10}, // 9
		{INF, INF, INF, 16, INF, INF, INF, 15, 10, 0} // 10
	};

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			g->weight[i][j] = weight[i][j];
		}
	}
	return g;
}


int main(int argc, char* argv[]) {
	GraphType* g = MakeGraph();
	int start, end;
	printf("Floyd-Warshall Algorithm\n");
	
	while (1) {
		printf("Start Node : ");
		scanf_s("%d", &start);

		if (start == -1) break;

		printf("End Node : ");
		scanf_s("%d", &end);

		floyd(g);
		print_distance(g, start, end);
		print_shortestpath(g, start, end);
	}

	free(g);

	return 0;
}