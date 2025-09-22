#include <stdio.h>
#include <stdlib.h>
#define MAX 20
#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )

int com1, com2, com3;
int mov1, mov2, mov3;

void selection_sort(int list[], int n) {
	int i, j, least, temp;
	int com = 0;
	int mov = 0;
	for (i = 0; i < n - 1; i++) {
		least = i;
		for (j = i + 1; j < n; j++) {
			com++;
			if (list[j] < list[least]) least = j;
		}
		SWAP(list[i], list[least], temp);
		mov++;
		for (int k = 0; k < n; k++)
			printf("%d ", list[k]);
		printf("\n");
	}
	for (int i = 0; i < n; i++)
		printf("%d ", list[i]);
	printf("\n");
}

void selection_sort_re(int list[], int n) {
	int i, j, least, temp;
	for (i = 0; i < n - 1; i++) {
		least = i;
		for (j = i + 1; j < n; j++) {
			com1++;
			if (list[j] < list[least]) least = j;
		}
		SWAP(list[i], list[least], temp);
		mov1++;
	}
}

void insertion_sort(int list[], int n) {
	int i, j, key;
	int com = 0;
	int mov = 0;
	for (i = 1; i < n; i++) {
		key = list[i];
		for (j = i - 1; j >= 0 && list[j] > key; j--) {
			com++;
			list[j + 1] = list[j];
			mov++;
		}
		list[j + 1] = key;
		mov++;
		for (int k = 0; k < n; k++)
			printf("%d ", list[k]);
		printf("\n");
	}
	for (int i = 0; i < n; i++)
		printf("%d ", list[i]);
	printf("\n");
}

void insertion_sort_re(int list[], int n) {
	int i, j, key;
	for (i = 1; i < n; i++) {
		key = list[i];
		for (j = i - 1; j >= 0 && list[j] > key; j--) {
			com2++;
			list[j + 1] = list[j];
			mov2++;
		}
		list[j + 1] = key;
		mov2++;
	}
}

void bubble_sort(int list[], int n) {
	int i, j, temp;
	int com = 0;
	int mov = 0;
	for (i = n - 1; i > 0; i--) {
		for (j = 0; j < i; j++){
			com++;
			if (list[j] > list[j + 1]) {
				SWAP(list[j], list[j + 1], temp);
				mov++;
			}
		}
		for (int k = 0; k < n; k++)
			printf("%d ", list[k]);
		printf("\n");
	}
	for (int i = 0; i < n; i++)
		printf("%d ", list[i]);
	printf("\n");
}

void bubble_sort_re(int list[], int n) {
	int i, j, temp;
	for (i = n - 1; i > 0; i--) {
		for (j = 0; j < i; j++) {
			com3++;
			if (list[j] > list[j + 1]) {
				SWAP(list[j], list[j + 1], temp);
				mov3++;
			}
		}
	}
}

int main(void) {
	int n = MAX;
	srand(time(NULL));
	int list_s[MAX];
	int list_i[MAX];
	int list_b[MAX];

	for (int i = 0; i < n; i++) {
		list_s[i] = rand() % 100;
		list_i[i] = rand() % 100;
		list_b[i] = rand() % 100;
	}
	printf("1. Selection Sort \n");
	printf("Before sorting\n");
	for (int i = 0; i < n; i++)
		printf("%d ", list_s[i]);
	printf("\nAfter sorting \n");
	selection_sort(list_s, n);
	printf("\n");

	printf("2. Insertion Sort \n");
	printf("Before sorting\n");
	for (int i = 0; i < n; i++)
		printf("%d ", list_i[i]);
	printf("\nAfter sorting \n");
	insertion_sort(list_i, n);
	printf("\n");

	printf("3. Bubble Sort \n");
	printf("Before sorting\n");
	for (int i = 0; i < n; i++)
		printf("%d ", list_b[i]);
	printf("\nAfter sorting \n");
	bubble_sort(list_b, n);
	printf("\n");

	for (int t = 0; t < n-1 ; t++) {
		for (int i = 0; i < n; i++) {
			list_s[i] = rand() % 100;
			list_i[i] = rand() % 100;
			list_b[i] = rand() % 100;
		}
		selection_sort_re(list_s, n);
		insertion_sort_re(list_i, n);
		bubble_sort_re(list_b, n);
	}

	printf("1. Selection Sorting \nMove Count : %d \n", (mov1 / 19));
	printf("Compare Count : %d \n \n", (com1 / 19));


	printf("2. Insertion Sorting \nMove Count : %d \n", (mov2 / 19));
	printf("Compare Count : %d \n \n", (com2 / 19));


	printf("3. Bubble Sorting \nMove Count : %d \n", (mov3 / 19));
	printf("Compare Count : %d \n", (com3 / 19));

	return 0;
}
