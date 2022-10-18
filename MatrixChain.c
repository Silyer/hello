#include <stdio.h>
#define INF 10000000
#define min(a, b) (a < b) ? a : b
#define NUM 6

void matrix(int *p) {
	int c[NUM][NUM];
	for(int i = 0; i < NUM; i++) c[i][i] = 0;
	for(int L = 1; L < NUM; L++){
		for(int i = 0; i < NUM - L; i++) {
			int j = i + L; 
			c[i][j] = INF;
			for(int k = i; k < j; k++) {
				c[i][j] = min(c[i][j], (c[i][k] + c[k + 1][j] + (p[i] * p[k + 1] * p[j + 1])));
			}
		}
	}
	
	for(int i = 0; i < NUM; i++) {
		for(int j = 0; j < NUM; j++) {
			if(j < i) printf("\t");
			else printf("%d\t", c[i][j]);
		}
		printf("\n");
	}
}
int main() {
	int m[NUM][2] = { { 5, 2 }, { 2, 3 }, { 3, 4 }, { 4, 6 }, { 6, 7 }, { 7, 8 } };
	int p[NUM + 1];
	for(int i = 0; i < NUM; i++) {
		p[i] = m[i][0];
		p[i + 1] = m[i][1];
	}
	matrix(p);
}
