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

// 생성 함수
HeapType* create_heap() {
	return (HeapType*)malloc(sizeof(HeapType));
}

// 초기화 함수
void init(HeapType* h) {
	h->heap_size = 0;
}
// 현재 요소의 개수가 heap_size인 히프 h에 item을 삽입한다.


// 삽입 함수
void insert_min_heap(HeapType* h, Element item) {
	int i;
	i = ++(h->heap_size);

	//  트리를 거슬러 올라가면서 부모 노드와 비교하는 과정
	while ((i != 1) && (item.key < h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;     // 새로운 노드를 삽입
}

// 삭제 함수
Element delete_min_heap(HeapType* h) {
	int parent, child;
	Element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		// 현재 노드의 자식노드중 더 작은 자식노드를 찾는다.
		if ((child < h->heap_size) &&
			(h->heap[child].key) > h->heap[child + 1].key)
			child++;
		if (temp.key < h->heap[child].key) break;
		// 한 단계 아래로 이동
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

// 이진 트리 제거 함수
void destroy_tree(TreeNode* root) {
	if (root == NULL) return;
	destroy_tree(root->left);
	destroy_tree(root->right);
	free(root);
}

// 단말 노드인지 확인 함수
int is_leaf(TreeNode* root) {
	return !(root->left) && !(root->right);
}

// 트리 출력
void print_array(int codes[], int n) {
	for (int i = 0; i < n; i++)
		printf("%d", codes[i]);
	printf("\n");
}

void print_codes(TreeNode* root, int codes[], int top) {
	// 1을 저장하고 순환호출한다. 
	if (root->left) {
		codes[top] = 1;
		print_codes(root->left, codes, top + 1);
	}
	// 0을 저장하고 순환호출한다. 
	if (root->right) {
		codes[top] = 0;
		print_codes(root->right, codes, top + 1);
	}
	// 단말노드이면 코드를 출력한다. 
	if (is_leaf(root)) {
		printf("%c: ", root->ch);
		print_array(codes, top);
	}
}

// 트리 생성
TreeNode* make_tree(TreeNode* left, TreeNode* right) {
	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
	node->left = left;
	node->right = right;
	return node;
}

// 중간과정 출력 함수
void print_heap(HeapType* h) {
	for (int i = 1; i <= h->heap_size; i++) {
		printf("%d ", h->heap[i].key);
	}
	printf("\n");
}

// 허프만 트리 생성
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
		// 최소값을 가지는 두개의 노드를 삭제
		e1 = delete_min_heap(heap);
		e2 = delete_min_heap(heap);
		// 두개의 노드를 합친다.
		x = make_tree(e1.ptree, e2.ptree);
		e.key = x->weight = e1.key + e2.key;
		e.ptree = x;

		printf("/// %d+%d->%d \n", e1.key, e2.key, e.key);
		printf("%d ", e.key);
		print_heap(heap);
		insert_min_heap(heap, e);
	}
	e = delete_min_heap(heap); // 최종 트리
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