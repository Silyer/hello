#include <stdio.h>
#define INF 100
#define EDGE_NUM 12

typedef struct edge {
	int start;
	int end;
	int weight;
} edge;

void sort(edge *e, int l, int r) {
	int p = e[(l + r) / 2].weight, pl = l, pr = r;
	edge t;
	while(pl <= pr) {
		while(e[pl].weight < p) pl++;
		while(e[pr].weight > p) pr--;
		if(pl <= pr) {
			t = e[pl];
			e[pl] = e[pr];
			e[pr] = t;
			pl++;
			pr--;
		}
	}
	if(l < pr) sort(e, l, pr);
	if(pl < r) sort(e, pl, r);
}

int getParent(int *c, int n) {
	if(c[n] == n) return n;
	return c[n] = getParent(c, c[n]);
}
int isCycle(int *c, int a, int b) {
	a = getParent(c, a);
	b = getParent(c, b);
	if(a == b) return 1;
	else return 0;
}

void unionC(int *c, int a, int b) {
	a = getParent(c, a);
	b = getParent(c, b);
	if(a < b) c[b] = a;
	else c[a] = b;
	printf("%d, %d 연결, ", a, b);
}
void kruskal(edge *e) {
	int sum;
	int cycle[7];
	for(int i = 0; i < 7; i++) cycle[i] = i;
	sort(e, 0, EDGE_NUM - 1);
	for(int i = 0; i < EDGE_NUM; i++) { 
		if(!isCycle(cycle, e[i].start, e[i].end)) {
			unionC(cycle, e[i].start, e[i].end);
			printf("가중치 = %d\n", e[i].weight);
			sum += e[i].weight;
		}
	}
	printf("sum = %d\n", sum);
}

int main() {
	int graph[7][7] = { { 0, 7, INF, INF, 3, 10, INF }, { 7, 0, 4, 10, 2, 6, INF }, { INF, 4, 0, 2, INF, INF, INF }, { INF, 10, 2, 0, 11, 9, 4 }, { 3, 2, INF, 11, 0, INF, 5 }, { 10, 6, INF, 9, INF, 0, INF }, { INF, INF, INF, 4, 5, INF, 0} };
	edge e[EDGE_NUM];
	int n = 0;
	for(int i = 0; i < 7; i++) {
		for(int j = i + 1; j < 7; j++) {
			if(graph[i][j] != 0 && graph[i][j] != INF) {
				e[n].start = i;
				e[n].end = j;
				e[n].weight = graph[i][j];
				n++;
			}
		}
	}
	kruskal(e);
}
