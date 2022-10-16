#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_SIZE 100

typedef struct element {	// 노드에 들어갈 요소 ch = 문자, size = 빈도
	char ch;
	int size;
} element;

typedef struct Htree {		// 트리 노드, 노드 요소와 left, right 트리로 구성
	element treeNode;
	struct Htree* left;
	struct Htree* right;
} Htree;

typedef struct Heap {		// 우선 순위 큐를 구현하기 위한 힙, 큐 내에 트리 노드와 큐의 개수로 구성
	Htree* HeapNode[MAX_SIZE];
	int size;
} Heap;


Htree* makeNode(char ch, int size, Htree *left, Htree *right) {		// 트리 노드 생성
	Htree* node = (Htree*)malloc(sizeof(Htree));
	node->treeNode.ch = ch;
	node->treeNode.size = size;
	node->left = left;
	node->right = right;
	return node;
}

void destroyTree(Htree* tree){	// 동적 할당된 트리 삭제
	if(NULL == tree) return;
	destroyTree(tree->left);
	destroyTree(tree->right);
	free(tree);
}

int isLeaf(Htree* tree) {	// 해당 트리 노드가 말단 노드인지?
	if((tree->left == NULL) && (tree->right == NULL)) return 1;
	else return 0;
}
void init_Heap(Heap* h) {	// 힙 초기화, 힙 노드가 트리형이므로 노드마다 초기화
	for (int i = 0; i < MAX_SIZE; i++) {
		makeNode('\0', 0, NULL, NULL);
	}
	h->size = 0;
}

void insert_Heap(Heap* h, Htree* e) {	// 힙 노드 삽입, e : 힙에 넣을 트리 노드
	int size = ++(h->size);
	int temp = size;
	Htree* t;
	h->HeapNode[size] = e;	// 말단에 넣고 가장 가중치가 적은 순서대로 힙 정렬(min heap)
	while (size != 1 && h->HeapNode[size]->treeNode.size < h->HeapNode[size / 2]->treeNode.size) {
		t = h->HeapNode[size];
		h->HeapNode[size] = h->HeapNode[size / 2];
		h->HeapNode[size / 2] = t;
		size /= 2;
	}
}

Htree* delete_Heap(Heap* h) {	// 힙 노드 제거, 힙에 있던 가장 가중치가 낮은 노드 반환
	Htree* min = h->HeapNode[1];
	Htree* temp = h->HeapNode[h->size];
	int size = --(h->size), parent = 1, child = 2;
	h->HeapNode[1] = temp;
	while (child <= size) {	// 왼, 오른쪽 노드 중 더 작은 노드를 부모 노드와 교환
		if (h->HeapNode[child]->treeNode.size > h->HeapNode[child + 1]->treeNode.size) child++;
		if (h->HeapNode[parent]->treeNode.size > h->HeapNode[child]->treeNode.size) {
			Htree* t = h->HeapNode[child];
			h->HeapNode[child] = h->HeapNode[parent];
			h->HeapNode[parent] = t;
		}
		parent = child;
		child *= 2;
	}
	return min;
}


void getFreq(char* a, int* f) {		// 입력받은 문자열에서 알파벳당 빈도수를 구함
	for (int i = 0; i < MAX_SIZE; i++) {
		if (a[i] >= 'A' && a[i] <= 'Z') tolower(a[i]);	// 대문자는 소문자로 치환
		for (int j = 0; j < 26; j++) {
			if (a[i] == 'a' + j) f[j]++;
		}
	}
}

Htree* huffman(char *a) {	// 허프만 트리 생성 함수
	int freq[26];
	Htree* left;	// left, right 각 트리의 자식 노드
	Htree* right;
	Htree* n;		// 루트 노드
	Htree* temp;	// temp, element e 둘 다 임시용
	Heap h;
	element e;

	for(int i = 0; i < 26; i++) freq[i] = 0;	//초기화 구문
	init_Heap(&h);
	getFreq(a, freq);

	for (int i = 0; i < 26; i++) {	// 처음에 정렬된 알파벳들을 자식 노드가 없는 트리 노드, 힙에 삽입
		if (freq[i] != 0) {
			e.ch = 'a' + i;
			e.size = freq[i];
			printf("%c : %d\n", e.ch, e.size);
			temp = makeNode(e.ch, e.size, NULL, NULL);
			insert_Heap(&h, temp);
		}
	}
	printf("\n");

	while(h.size >= 2) {	// 큐에 노드가 2개 남을때까지 (끝에 같은 루트 노드가 2개 남기 때문)
		left = delete_Heap(&h);		// 큐 제거 후 각 left right 노드에 반환
		right = delete_Heap(&h);
		int sum = left->treeNode.size + right->treeNode.size;
		n = makeNode('*', sum, left, right);	// left, right 가중치를 합한 문자 없는 노드 생성
		insert_Heap(&h, n);
	}
	return n;
}

void printCode(int *code, int idx, char ch, int size) {	// 문자를 압축한 정수 코드 출력
	printf("%d 개를 갖고있는 문자 %c : ", size, ch);
	for(int i = 0; i < idx; i++){
		printf("%d", code[i]);
	}
	printf("\n");
}

void decodeHuff(Htree *tree, int *code, int i) {	// 허프만 트리 변환
	if(tree->left != NULL) {	// 왼쪽 자식 노드로 가면 0을 붙임
		code[i] = 0;
		decodeHuff(tree->left, code, i + 1);
	}

	if(tree->right != NULL) {	// 오른쪽 자식 노드로 가면 1을 붙임
		code[i] = 1;
		decodeHuff(tree->right, code, i + 1);
	}
		//말단 노드이면 알파벳이 들어있는 노드이므로 해당 위치에서 기록된 코드와 위치 반환
	if(isLeaf(tree)) printCode(code, i, tree->treeNode.ch, tree->treeNode.size);
}

int main() {
	Htree *tree;
	int code[MAX_SIZE];
	char a[MAX_SIZE];
	for (int i = 0; i < MAX_SIZE; i++){
		a[i] = '\0';
		code[i] = 0;
	}
	printf("Input str : ");
	scanf("%s", a);

	tree = huffman(a);
	decodeHuff(tree, code, 0);

	destroyTree(tree);
	return 0;
}
