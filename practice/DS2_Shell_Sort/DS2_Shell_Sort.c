#include <stdio.h>
#include <stdlib.h>
#define MAX 20
// 이동횟수와 비교횟수를 카운트 할 변수
int com, mov;
// 삽입 정렬
inc_insertion_sort(int list[], int first, int last, int gap) {
	int i, j, key;
	for (i = first + gap; i <= last; i = i + gap) {
		key = list[i];
		for (j = i - gap; j >= first && key < list[j]; j = j - gap) {
			list[j + gap] = list[j];
		}
		list[j + gap] = key;
	}
}
// 셸 정렬
void shell_sort(int list[], int n) {
	int i, gap;
	for (gap = n / 2; gap > 0; gap = gap / 2) {
		if ((gap % 2) == 0) gap++;
		for (i = 0; i < gap; i++)
			inc_insertion_sort(list, i, n - 1, gap);
		for (int k = 0; k < n; k++)
			printf("%d ", list[k]);
		printf("\n");
	}
}
// 카운트 할 때 쓸 함수
inc_insertion_sort_re(int list[], int first, int last, int gap) {
	int i, j, key;
	for (i = first + gap; i <= last; i = i + gap) {
		key = list[i];
		j = i - gap;
		while (j >= first && key < list[j]) {
			list[j + gap] = list[j];
			com++;
			j = j - gap;
		}
		list[j + gap] = key;
		mov++;
	}
}
// 카운트 할 때 쓸 함수
void shell_sort_re(int list[], int n) {
	int i, gap;
	for (gap = n / 2; gap > 0; gap = gap / 2) {
		if ((gap % 2) == 0) gap++;
		for (i = 0; i < gap; i++)
			inc_insertion_sort_re(list, i, n - 1, gap);
	}
}

int main(void) {
	int n = MAX;
	srand(time(NULL));
	int list[MAX];

	for (int i = 0; i < n; i++) {
		list[i] = rand() % 100;
	}
	printf("Shell Sort \n");
	printf("Before sorting\n");
	for (int i = 0; i < n; i++)
		printf("%d ", list[i]);
	printf("\nSorting... \n");
	shell_sort(list, n);
	printf("\n");

	mov = 0;
	com = 0;

	for (int t = 0; t < n - 1; t++) {
		for (int i = 0; i < n; i++) {
			list[i] = rand() % 100;
		}
		shell_sort_re(list, n);
	}

	printf("Shell Sorting \nAverage Move Count : %d \n", (mov / (n-1)));
	printf("Average Compare Count : %d \n \n", (com / (n - 1)));


	return 0;
}
