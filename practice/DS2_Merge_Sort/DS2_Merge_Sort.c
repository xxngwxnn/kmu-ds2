#include <stdio.h>
#include <stdlib.h>
#define MAX 20

int com = 0;
int mov = 0;
int sorted[MAX];

// �պ� ���Ŀ��� �պ����ִ� �Լ�
void merge(int list[], int left, int mid, int right) {
	int i, j, k, l;
	i = left; j = mid + 1; k = left;

	while (i <= mid && j <= right) {
		if (list[i] <= list[j]) sorted[k++] = list[i++];
		else sorted[k++] = list[j++];
	}
	if (i > mid) {
		for (l = j; l <= right; l++) {
			sorted[k++] = list[l];
		}
	}
	else {
		for (l = i; l <= mid; l++) {
			sorted[k++] = list[l];
		}
	}
	for (l = left; l <= right; l++) {
		list[l] = sorted[l];
	}
	for (int t = 0; t < MAX; t++)
		printf("%d ", list[t]);
	printf("\n");
}
// ����Ʈ�� �յ��ϰ� �����ؼ� ��ȯȣ��
void merge_sort(int list[], int left, int right) {
	int mid;
	if (left < right) {
		mid = (left + right) / 2;
		merge_sort(list, left, mid);
		merge_sort(list, mid + 1, right);
		merge(list, left, mid, right);
	}
}
// �̵�Ƚ���� ��Ƚ���� ���ϱ� ���� �Լ�
void merge_re(int list[], int left, int mid, int right) {
	int i, j, k, l;
	i = left; j = mid + 1; k = left;

	while (i <= mid && j <= right) {
		if (list[i] <= list[j]) sorted[k++] = list[i++];
		else sorted[k++] = list[j++];
		com++;
	}
	if (i > mid) {
		for (l = j; l <= right; l++) {
			sorted[k++] = list[l];
			mov++;
		}
	}
	else {
		for (l = i; l <= mid; l++) {
			sorted[k++] = list[l];
			mov++;
		}
	}
	for (l = left; l <= right; l++) {
		list[l] = sorted[l];
		mov++;
	}
}
// �̵�Ƚ���� ��Ƚ���� ���ϱ� ���� �Լ�
void merge_sort_re(int list[], int left, int right) {
	int mid;
	if (left < right) {
		mid = (left + right) / 2;
		merge_sort_re(list, left, mid);
		merge_sort_re(list, mid + 1, right);
		merge_re(list, left, mid, right);
	}
}
// �ݺ��� ������� ������ �պ�����
void merge_iter(int list[], int left, int mid, int right) {
	int i, j, k;
	int temp[MAX];
	i = left; j = mid + 1; k = left;

	while (i <= mid && j <= right) {
		if (list[i] <= list[j]) {
			temp[k++] = list[i++];
		}
		else {
			temp[k++] = list[j++];
		}
	}
	while (i <= mid) {
		temp[k++] = list[i++];
	}
	while (j <= right) {
		temp[k++] = list[j++];
	}

	for (int idx = left; idx <= right; idx++) {
		list[idx] = temp[idx];
	}
}
// �ݺ��� ������� ������ �պ�����
void merge_sort_iter(int list[], int n) {
	int size, left_start;

	for (size = 1; size < n; size *= 2) {
		for (left_start = 0; left_start < n - 1; left_start += 2 * size) {
			int mid = left_start + size - 1;
			int right_end = left_start + 2 * size - 1;
			if (right_end >= n) {
				right_end = n - 1;
			}
			merge_iter(list, left_start, mid, right_end);
			for (int i = 0; i < n; i++) {
				printf("%d ", list[i]);
			}
			printf("\n");
		}
	}
}

int main(int argc, char* argv[]) {
	int n = MAX;
	srand(time(NULL));
	int list[MAX];
	int list_t[MAX];
	int list_i[MAX];
	for (int i = 0; i < n; i++) 
		list[i] = rand() % 100;
	// �⺻ �պ�����
	printf("Original List \n");
	for (int i = 0; i < n; i++)
		printf("%d ", list[i]);
	printf("\n\nMerge Sort\n");
	merge_sort(list, 0, (n-1)); 
	// �̵�Ƚ���� ��Ƚ���� ���ϱ� ����
	for (int t = 0; t < n ; t++) {
		for (int i = 0; i < n; i++) {
			list_t[i] = rand() % 100;
		}
		merge_sort_re(list_t, 0, (n-1));
	}
	printf("Average Move Count : %d \n", (mov / n));
	printf("Average Compare Count : %d \n \n", (com / n));
	// �ݺ��� ���
	printf("Merge Sort Iteration\n");
	for (int i = 0; i < n; i++)
		list_i[i] = rand() % 100;
	printf("Original List \n");
	for (int i = 0; i < n; i++)
		printf("%d ", list_i[i]);
	printf("\n\nMerge Sort\n");
	merge_sort_iter(list_i, n);

	return 0;
}