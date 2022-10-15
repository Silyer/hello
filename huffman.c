#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_SIZE 100

typedef struct element {
	char ch;
	int size;
} element;

typedef struct Htree {
	element treeNode;
	struct Htree* left;
	struct Htree* right;
} Htree;

typedef struct Heap {
	element HeapNode[MAX_SIZE];
	int size;
} Heap;

void init_Heap(Heap *h) {
	for(int i = 0; i < MAX_SIZE; i++) {
		h->HeapNode[i].ch = '\0';
		h->HeapNode[i].size = 0;
	}
	h->size = 0;
}

void insert_Heap(Heap *h, element e) {
	int size = ++(h->size);
	int temp = size;
	element t;
	h->HeapNode[size] = e;
	while(size != 1 && h->HeapNode[size].size < h->HeapNode[size / 2].size) {
		t = h->HeapNode[size];
		h->HeapNode[size] = h->HeapNode[size / 2];
		h->HeapNode[size / 2] = t;
		size /= 2;
	}
}

element delete_Heap(Heap *h) {
	element min = h->HeapNode[1], temp = h->HeapNode[h->size];
	int size = --(h->size), parent = 1, child = 2;
	h->HeapNode[1] = temp;
	while(child <= size)  {
		if(h->HeapNode[child].size > h->HeapNode[child + 1].size) child++;
		if(h->HeapNode[parent].size > h->HeapNode[child].size) {	
			element t = h->HeapNode[child];
			h->HeapNode[child] = h->HeapNode[parent];
			h->HeapNode[parent] = t;
		}
		parent = child;
		child *= 2;
	}
	return min;
}
void getFreq(char *a, int *f) {
	for(int i = 0; i < MAX_SIZE; i++){
		if(a[i] >= 'A' && a[i] <= 'Z') tolower(a[i]);
		for(int j = 0; j < 26; j++) {
			if(a[i] == 'a' + j) f[j]++;
		}
	}
}

int main() {
	Heap h;
	char a[MAX_SIZE];
	int freq[26];
	init_Heap(&h);

	for(int i = 0; i < 26; i++) freq[i] = 0;
	for(int i = 0; i < MAX_SIZE; i++) a[i] = '\0';
	scanf("%s", a);
	getFreq(a, freq);

	for(int i = 0; i < 26; i++) {
		if(freq[i] != 0) {
			element e;
			e.ch = 'a' + i;
			e.size = freq[i];
			insert_Heap(&h, e);
		}
	}
	int size = h.size, n = 0;
	while(size) {
		element e = delete_Heap(&h);
		printf("%d번째로 작은 가중치가 %d인 %c\n", ++n, e.size, e.ch);
		size--;
	}
	return 0;
}
