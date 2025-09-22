#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200


typedef struct Element{
	int key;
}Element;

typedef struct heapType {
	Element heap[MAX_ELEMENT];
	int heap_size;
}heapType;

// heap 생성
heapType* create() {
	return (heapType*)malloc( sizeof(heapType) );
}

// heap 초기화
void init(heapType* h) {
	h->heap_size = 0;
}

// heap이 비어있는지 확인
int is_empty(heapType* h) {
	return (h->heap_size == 0);
}
// heap이 가득 차 있는지 확인
int is_full(heapType* h) {
	return (h->heap_size == MAX_ELEMENT - 1);
}

// 현재 heap의 상태를 출력
void print_heap(heapType* h) {
	if (is_empty(h)) {
		printf("Heap is empty\n");
		return;
	}
	for (int i = 1; i <= h->heap_size ; i++) {
		printf("%d ", h->heap[i]);
	}
	printf("\n");
}

// heap에 노드 추가
void insert_heap(heapType** heap, Element item, int* visitNodes) {
	heapType* h = *heap;

	if (is_full(heap)) {
		printf("Heap is full\n");
		return;
	}
	int curr = ++(h->heap_size);
	while (curr > 1 && item.key > h->heap[curr / 2].key) {
		h->heap[curr] = item;
		print_heap(*heap);
		h->heap[curr] = h->heap[curr / 2];
		curr = curr / 2;
		(*visitNodes)++;
	}
	h->heap[curr] = item;
	print_heap(*heap);
}
// heap에서 노드 삭제
Element delete_heap(heapType** heap, int* visitNodes) {
	heapType* h = *heap;
	int parent, child;
	if (is_empty(h)) {
		printf("Heap is empty\n");
		return;
	}
	Element item = h->heap[1];
	Element temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child < h->heap_size) {
		(*visitNodes)++;
		print_heap(*heap);
		if (child < h->heap_size && h->heap[child].key < h->heap[child + 1].key) {
			child++;
		}
		if (temp.key >= h->heap[child].key)
			break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child = child * 2;

	}
	h->heap[parent] = temp;
	print_heap(*heap);
	return item;
}

// 레벨별 출력
void levelorder(heapType** heap) {
	heapType* h = *heap;
	if (is_empty(h)) {
		printf("Heap is empty\n");
	}
	else {
		int level = 1; 
		int count = 0; 
		int elementsInLevel = 1;  

		for (int i = 1; i <= h->heap_size; i++) {
			if (count == 0) { 
				printf("[%d] ", level);
			}
			printf("%d ", h->heap[i]);
			count++;
			if (count == elementsInLevel) {
				printf("\n");  
				level++; 
				elementsInLevel *= 2;  
				count = 0;  
			}
		}
		if (count != 0) printf("\n"); 
	}
}

int main(int argc, char* argv[]) {
	heapType* heap;
	heap = create();
	init(heap);
	// heap 배열에 값 입력
	Element nodes[] = { {90}, {89}, {70}, {36}, {75}, {63}, {65}, {21}, {18}, {15} };
	int num_nodes = sizeof(nodes) / sizeof(nodes[0]);

	for (int i = 0; i < num_nodes; i++) {
		heap->heap[i + 1] = nodes[i];
		heap->heap_size++;
	}
	// 방문한 노드의 수를 계산하는 변수
	int visitNodes = 0;

	// 메뉴 생성
    printf(" i : 노드 추가\n d : 노드 삭제\n P : 레벨별 출력\n c : 종료\n");
    char item;

    while (1) {
        printf("메뉴 입력 : ");
        scanf_s(" %c", &item, sizeof(item));

        switch (item) {
        case 'i':
            printf("추가할 값 입력: ");
            int key_i = 0;
            scanf_s("%d", &key_i);
			insert_heap(&heap, (Element){ key_i }, &visitNodes);
			printf("노드가 이동된 횟수: %d\n", visitNodes);
			visitNodes = 0;
			printf("\n");
            break;
        case 'd':
			delete_heap(&heap, &visitNodes);
			printf("노드가 이동된 횟수: %d\n", visitNodes);
            visitNodes = 0;
            printf("\n");
            break;
		 case 'P':
			 levelorder(&heap);
            break;
        case 'c':
            exit(0);
        default:
            printf("잘못된 입력입니다. 다시 시도하세요.\n");
            break;
        }
    }
	free(heap);

	return 0;
	}