#include <stdio.h>
#define INF 100
#define min(a, b) (a > b ? b : a)
#define max(a, b) (a < b ? a : b)


int main() {
	int d[5][5] = {{ 0, 4, 2, 5, INF }, { INF, 0, 1, INF, 4 }, { 1, 3, 0, 1, 2 }, { -2, INF, INF, 0, 2 }, { INF, -3, 3, 1, 0 }};

	for(int k = 0; k < 5; k++) {
		for(int i = 0; i < 5; i++) {
			for(int j = 0; j < 5; j++) {
				d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
			}
		}
	}

	for(int i = 0; i < 5; i++) {
		for(int j = 0; j < 5; j++) {
			printf("%3d ", d[i][j]);
		}
		printf("\n");
	}
}
