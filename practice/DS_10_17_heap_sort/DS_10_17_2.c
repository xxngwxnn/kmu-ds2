#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200
#define SIZE 17

typedef struct element {
	int key;
} element;

typedef struct HeapType {
	element heap[MAX_ELEMENT];
	int heap_size;
} HeapType;


// ���� �Լ�
HeapType* create() {
	return (HeapType*)malloc(sizeof(HeapType));
}

// �ʱ�ȭ �Լ�
void init(HeapType* h) {
	h->heap_size = 0;
}

// ���� �Լ�
void insert_max_heap(HeapType* h, element item) {
	int i;
	i = ++(h->heap_size);

	//  Ʈ���� �Ž��� �ö󰡸鼭 �θ� ���� ���ϴ� ����
	while ((i != 1) && (item.key > h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item; 
}

// ���� �Լ�
element delete_max_heap(HeapType* h) {
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		// ���� ����� �ڽĳ�� �� �� ���� �ڽĳ�带 ã�´�.
		if ((child < h->heap_size) &&
			(h->heap[child].key) < h->heap[child + 1].key)
			child++;
		if (temp.key >= h->heap[child].key) break;
		// �� �ܰ� �Ʒ��� �̵�
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

// ���� �Լ�
void heap_sort(element a[], int n) {
	int i;
	HeapType* h;

	h = create();
	init(h);
	for (i = 0; i < n; i++) {
		insert_max_heap(h, a[i]);
		for (int j = 0; j < h->heap_size; j++) { // �߰����� ���
			printf("%d ", h->heap[j + 1].key);
		}
		printf("\n");
	}
	for (i = (n - 1); i >= 0; i--) {
		a[i] = delete_max_heap(h);
		for (int j = 0; j < h->heap_size; j++) { // �߰����� ���
			printf("%d ", h->heap[j + 1].key);
		}
		printf("\n");
	}
	free(h);
}

int main(int argc, char* argv[]) {
	element list[SIZE] = { 34, 12, 76, 59, 32, 55, 88, 26, 16, 79, 34, 85, 29, 78, 41, 56, 86 };
	heap_sort(list, SIZE);
	for (int i = 0; i < SIZE; i++) { // ���� ��� ���
		printf("%d ", list[i].key);
	}
	printf("\n");
	return 0;
}