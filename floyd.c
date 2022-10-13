#include <stdio.h>
#define INF 100
#define max(a, b) ((a > b) ? a : b)
#define min(a, b) ((a < b) ? a : b)
int floyd(int x, int y) {
	int i, j, k;
	int d[5][5] = {
		{0, 4, 2, 5, INF}, 
		{INF, 0, 1, INF, 4},
		{1, 3, 0, 1, 2},
		{-2, INF, INF, 0, 2},
		{INF, -3, 3, 1, 0}
	};
	for(k = 0;  k < 5; k++) {
		for(i = 0; i < 5; i++) {
			for(j = 0; j < 5; j++) {
				d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
			}
		}
	}
	return d[x][y];
}
int main(void) {
	for(int i = 0; i < 5; i++) {
		for(int j = 0; j < 5; j++) {
			printf("%2d", floyd(i, j));
		}
		printf("\n");
	}
	return 0;
}
