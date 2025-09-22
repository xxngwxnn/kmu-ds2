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

// heap ����
heapType* create() {
	return (heapType*)malloc( sizeof(heapType) );
}

// heap �ʱ�ȭ
void init(heapType* h) {
	h->heap_size = 0;
}

// heap�� ����ִ��� Ȯ��
int is_empty(heapType* h) {
	return (h->heap_size == 0);
}
// heap�� ���� �� �ִ��� Ȯ��
int is_full(heapType* h) {
	return (h->heap_size == MAX_ELEMENT - 1);
}

// ���� heap�� ���¸� ���
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

// heap�� ��� �߰�
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
// heap���� ��� ����
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

// ������ ���
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
	// heap �迭�� �� �Է�
	Element nodes[] = { {90}, {89}, {70}, {36}, {75}, {63}, {65}, {21}, {18}, {15} };
	int num_nodes = sizeof(nodes) / sizeof(nodes[0]);

	for (int i = 0; i < num_nodes; i++) {
		heap->heap[i + 1] = nodes[i];
		heap->heap_size++;
	}
	// �湮�� ����� ���� ����ϴ� ����
	int visitNodes = 0;

	// �޴� ����
    printf(" i : ��� �߰�\n d : ��� ����\n P : ������ ���\n c : ����\n");
    char item;

    while (1) {
        printf("�޴� �Է� : ");
        scanf_s(" %c", &item, sizeof(item));

        switch (item) {
        case 'i':
            printf("�߰��� �� �Է�: ");
            int key_i = 0;
            scanf_s("%d", &key_i);
			insert_heap(&heap, (Element){ key_i }, &visitNodes);
			printf("��尡 �̵��� Ƚ��: %d\n", visitNodes);
			visitNodes = 0;
			printf("\n");
            break;
        case 'd':
			delete_heap(&heap, &visitNodes);
			printf("��尡 �̵��� Ƚ��: %d\n", visitNodes);
            visitNodes = 0;
            printf("\n");
            break;
		 case 'P':
			 levelorder(&heap);
            break;
        case 'c':
            exit(0);
        default:
            printf("�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���.\n");
            break;
        }
    }
	free(heap);

	return 0;
	}