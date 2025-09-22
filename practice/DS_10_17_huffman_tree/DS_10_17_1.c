#include <stdio.h>
#include <stdlib.h>
#define MAX 200

typedef struct TreeNode {
	int weight;
	char ch;
	struct TreeNode* left;
	struct TreeNode* right;
} TreeNode;

typedef struct Element {
	TreeNode* ptree;
	char* ch;
	int key;
}Element;

typedef struct HeapType {
	Element heap[MAX];
	int heap_size;
} HeapType;

// ���� �Լ�
HeapType* create_heap() {
	return (HeapType*)malloc(sizeof(HeapType));
}

// �ʱ�ȭ �Լ�
void init(HeapType* h) {
	h->heap_size = 0;
}
// ���� ����� ������ heap_size�� ���� h�� item�� �����Ѵ�.


// ���� �Լ�
void insert_min_heap(HeapType* h, Element item) {
	int i;
	i = ++(h->heap_size);

	//  Ʈ���� �Ž��� �ö󰡸鼭 �θ� ���� ���ϴ� ����
	while ((i != 1) && (item.key < h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;     // ���ο� ��带 ����
}

// ���� �Լ�
Element delete_min_heap(HeapType* h) {
	int parent, child;
	Element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		// ���� ����� �ڽĳ���� �� ���� �ڽĳ�带 ã�´�.
		if ((child < h->heap_size) &&
			(h->heap[child].key) > h->heap[child + 1].key)
			child++;
		if (temp.key < h->heap[child].key) break;
		// �� �ܰ� �Ʒ��� �̵�
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

// ���� Ʈ�� ���� �Լ�
void destroy_tree(TreeNode* root) {
	if (root == NULL) return;
	destroy_tree(root->left);
	destroy_tree(root->right);
	free(root);
}

// �ܸ� ������� Ȯ�� �Լ�
int is_leaf(TreeNode* root) {
	return !(root->left) && !(root->right);
}

// Ʈ�� ���
void print_array(int codes[], int n) {
	for (int i = 0; i < n; i++)
		printf("%d", codes[i]);
	printf("\n");
}

void print_codes(TreeNode* root, int codes[], int top) {
	// 1�� �����ϰ� ��ȯȣ���Ѵ�. 
	if (root->left) {
		codes[top] = 1;
		print_codes(root->left, codes, top + 1);
	}
	// 0�� �����ϰ� ��ȯȣ���Ѵ�. 
	if (root->right) {
		codes[top] = 0;
		print_codes(root->right, codes, top + 1);
	}
	// �ܸ�����̸� �ڵ带 ����Ѵ�. 
	if (is_leaf(root)) {
		printf("%c: ", root->ch);
		print_array(codes, top);
	}
}

// Ʈ�� ����
TreeNode* make_tree(TreeNode* left, TreeNode* right) {
	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
	node->left = left;
	node->right = right;
	return node;
}

// �߰����� ��� �Լ�
void print_heap(HeapType* h) {
	for (int i = 1; i <= h->heap_size; i++) {
		printf("%d ", h->heap[i].key);
	}
	printf("\n");
}

// ������ Ʈ�� ����
void huffman_tree(int freq[], char ch_list[], int n) {
	HeapType* heap;
	TreeNode* node, *x;
	Element e, e1, e2;
	int codes[100];
	int top = 0;

	heap = create_heap();
	init(heap);
	for (int i = 0; i < n; i++) {
		node = make_tree(NULL, NULL);
		e.ch = node->ch = ch_list[i];
		e.key = node->weight = freq[i];
		e.ptree = node;
		insert_min_heap(heap, e);
	}
	for (int i = 1; i < n; i++) {
		// �ּҰ��� ������ �ΰ��� ��带 ����
		e1 = delete_min_heap(heap);
		e2 = delete_min_heap(heap);
		// �ΰ��� ��带 ��ģ��.
		x = make_tree(e1.ptree, e2.ptree);
		e.key = x->weight = e1.key + e2.key;
		e.ptree = x;

		printf("/// %d+%d->%d \n", e1.key, e2.key, e.key);
		printf("%d ", e.key);
		print_heap(heap);
		insert_min_heap(heap, e);
	}
	e = delete_min_heap(heap); // ���� Ʈ��
	print_codes(e.ptree, codes, top);
	destroy_tree(e.ptree);
	free(heap);

}

int main(int argc, char* argv[]) {
	char ch_list[] = { 'a', 'e', 'i', 'o', 'u', 's', 't'};
	int freq[] = { 10, 15, 12, 3, 4, 13, 1 };
	huffman_tree(freq, ch_list, 7);
	return 0;
}