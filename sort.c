#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define NUM 10

int queue[10][NUM];
int front[10], rear[10];

bool IsFull(int n) {
	if ((rear[n] + 1) % NUM == front[n]) return true;
	return false;
}
bool IsEmpty(int n) {
	if (front[n] == rear[n]) return true;
	return false;
}
int Dequeue(int n) {
	if (IsEmpty(n)) return -1;
	front[n] = (front[n] + 1) % NUM;
	return queue[n][front[n]];
}
bool Enqueue(int n, int a) {
	if (IsFull(n)) return false;
	rear[n] = (rear[n] + 1) % NUM;
	queue[n][rear[n]] = a;
	return true;
}

void setArray(int* a) {
	srand(time(NULL));
	for (int i = 0; i < NUM; i++) {
		a[i] = rand() % 100;
		printf("%d ", a[i]);
	}
	printf("\n");
}

void InsertionSort(int* a, int n) {
	int temp, i, j;
	for (i = 1; i < n; i++) {
		temp = a[i];
		for (j = i - 1; j >= 0 && temp < a[j]; j--) {
			a[j + 1] = a[j];
		}
		a[j + 1] = temp;
	}

	for (int k = 0; k < n; k++)
		printf("%d ", a[k]);
	printf("\n\n");
}
void SelectionSort(int* a, int n) {
	int min, temp, i, j;
	for (int i = 0; i < n - 1; i++) {
		min = i;
		for (int j = i + 1; j < n; j++) {
			if (a[j] < a[min]) min = j;
		}
		temp = a[min];
		a[min] = a[i];
		a[i] = temp;
	}

	for (int k = 0; k < n; k++)
		printf("%d ", a[k]);
	printf("\n\n");
}

void BubbleSort(int* a, int n) {
	int temp, i, j;
	for (i = n - 1; i > 0; i--) {
		for (j = 0; j < i; j++) {
			if (a[j] > a[j + 1]) {
				temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
	}

	for (int k = 0; k < n; k++)
		printf("%d ", a[k]);
	printf("\n\n");
}

void ShellSort(int* a, int n) {
	int gap, temp, i, j;
	for (gap = n / 2; gap > 0; gap /= 2) {
		for (i = gap; i < n; i++) {
			temp = a[i];
			for (j = i - gap; j >= 0 && temp < a[j]; j -= gap)
				a[j + gap] = a[j];
			a[j + gap] = temp;
		}
	}

	for (int k = 0; k < n; k++)
		printf("%d ", a[k]);
	printf("\n\n");
}

void Merge(int* a, int l, int m, int r) {
	int aa[NUM], ll = l, rr = m + 1, i = 0;

	while (ll <= m && rr <= r) {
		if (a[ll] <= a[rr]) aa[i++] = a[ll++];
		else aa[i++] = a[rr++];
	}

	while (ll <= m) aa[i++] = a[ll++];
	while (rr <= r) aa[i++] = a[rr++];
	i--;

	while (i >= 0) {
		a[l + i] = aa[i];
		i--;
	}
}

void MergeSort(int* a, int l, int r) {
	int mid;
	if (l < r) {
		mid = (l + r) / 2;
		MergeSort(a, l, mid);
		MergeSort(a, mid + 1, r);
		Merge(a, l, mid, r);
	}
}

void QuickSort(int* a, int l, int r) {
	int temp, p = a[(l + r) / 2], ll = l, rr = r;
	while (ll <= rr) {
		while (a[ll] < p) ll++;
		while (a[rr] > p) rr--;

		if (ll <= rr) {
			temp = a[ll];
			a[ll] = a[rr];
			a[rr] = temp;

			ll++;
			rr--;
		}
	}

	if (l < rr) QuickSort(a, l, rr);
	if (ll < r) QuickSort(a, ll, r);
}

void RadixSort(int* a, int n) {
	int max = 100;
	for (int i = 1; i <= max; i *= 10) {
		for (int j = 0; j < n; j++) {
			int d = (a[j] / i) % (i * 10);
			Enqueue(d, a[j]);
		}
		int t = 0;
		for (int j = 0; j < 10; j++) {
			while (!IsEmpty(j)) {
				a[t++] = Dequeue(j);
			}
		}
	}
	for (int k = 0; k < n; k++)
		printf("%d ", a[k]);
	printf("\n\n");
}

int main() {
	int arr[NUM];

	setArray(arr);
	InsertionSort(arr, NUM);

	setArray(arr);
	SelectionSort(arr, NUM);

	setArray(arr);
	BubbleSort(arr, NUM);

	setArray(arr);
	ShellSort(arr, NUM);

	setArray(arr);
	MergeSort(arr, 0, NUM - 1);

	for (int k = 0; k < NUM; k++)
		printf("%d ", arr[k]);
	printf("\n\n");

	setArray(arr);
	QuickSort(arr, 0, NUM - 1);

	for (int k = 0; k < NUM; k++)
		printf("%d ", arr[k]);
	printf("\n\n");

	setArray(arr);
	RadixSort(arr,NUM);

	return 0;
}
