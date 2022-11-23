#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 6

int graph[MAX][MAX] = { {1, 1, 1, 1, 0, 1},
                        {1, 1, 0, 0, 1, 1},
                        {1, 0, 1, 0, 0, 1},
                        {1, 0, 0, 1, 1, 1},
                        {0, 1, 0, 1, 1, 1},
                        {1, 1, 1, 1, 1, 1} };
int visit[MAX];

bool promising(int i) {
    int j = 0;
    bool isprom = true;
    while(j < i && isprom) {
        if(graph[i][j] && visit[i] == visit[j])
            isprom = false;
        j++;
    }
    return isprom;
}

void coloring(int i) {
    int color;
    if(promising(i)) {
        if(i == MAX - 1) {
            for(int i = 0; i < MAX; i++)
                    printf("(%d, %d)\n", i + 1, visit[i] + 1);
            exit(0);
        }
        else{
            for(color = 0; color < MAX; color++) {
                    visit[i + 1] = color;
                    coloring(i + 1);
            }
        }
    }
}

int main() {
    coloring(0);
}
