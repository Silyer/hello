#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 5

typedef struct element {
	char ch;
	int freq;
} element;

typedef struct Htree {
	element node;
	struct Htree *left;
	struct Htree *right;
} Htree;

typedef struct Heap {
	element HeapNode[MAX_SIZE];
	int size;
} Heap;

void init_ele(element *n) {
	n->ch = '\0';
	n->freq = 0;
}

void init_tree(Htree *tree) {
	tree->node.ch = '\0';
	tree->node.freq = 0;
}

void init_heap(Heap *h) {
	for (int i = 0; i < MAX_SIZE; i++) {
		h->HeapNode[i].ch = '\0';
		h->HeapNode[i].freq = 0;
	}
	h->size = 0;
}

void upheap(Heap *h, element item) {
	int size = ++(h->size);
	h->HeapNode[size] = item;
	while (size != 1 && h->HeapNode[size].freq < h->HeapNode[size / 2].freq) {
		element t = h->HeapNode[size / 2];
		h->HeapNode[size / 2] = h->HeapNode[size];
		h->HeapNode[size] = t;
		size /= 2;
	}
}

element downheap(Heap* h) {
	element root = h->HeapNode[1];
	element end = h->HeapNode[h->size];
	int size = --(h->size);
	int parent = 1, child = 2;
	h->HeapNode[1] = end;
	while (child <= size) {
		if (h->HeapNode[child].freq > h->HeapNode[child + 1].freq) child++;
		if (h->HeapNode[parent].freq > h->HeapNode[child].freq) {
			element t = h->HeapNode[child];
			h->HeapNode[child] = h->HeapNode[parent];
			h->HeapNode[parent] = t;
		}
		parent = child;
		child *= 2;
	}
	return root;
}

Htree makeNode(element left, element right) {
	Htree tree;
	init_tree(&tree);
	tree.node.ch = '\0';
	tree.node.freq = left.freq + right.freq;
	tree.left->node = left;
	tree.right->node = right;
	return tree;
}

element makeElement(element a, element b) {
	element n;
	n.ch = '\0';
	n.freq = a.freq + b.freq;
	return n;
}

Htree HuffmanTree(Heap *h) {
	Htree tree;
	element a, b;
	init_ele(&a);
	init_ele(&b);
	for (int i = 0; i < MAX_SIZE; i++) {
		tree = makeNode(a, b);
	}
	while (h->size >= 2) {
		element a, b, n;
		a = downheap(&h);
		b = downheap(&h);
		n = makeElement(a, b);
		tree = makeNode(a, b);
		upheap(&h, n);
		printf("가중치 %d인 %c와 가중치 %d인 %c가 결합\n", a.freq, a.ch, b.freq, b.ch);
	}
	return tree;
}

int main() {
	element node;
	Heap h;
	Htree huff;
	char a;
	int n;
	init_heap(&h);
	for (int i = 0; i < MAX_SIZE; i++) {
		printf("%d 번째 문자 : ", i + 1);
		if (i != 0) getchar();
		scanf_s("%c", &a);	
		getchar();
		printf("빈도 : ");
		scanf_s("%d", &n);

		node.ch = a;
		node.freq = n;
		printf("입력받은 문자 : %c, 입력받은 빈도 : %d\n", node.ch, n);
		upheap(&h, node);
	}
	huff = HuffmanTree(&h);
}
