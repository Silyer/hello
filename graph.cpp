/* 그래프 탐색 방법 (v = vertax 정점, e = edge 간선) */

/* dfs ..stack */

//인접 행렬을 이용한 구현  O(v^2)
void dfs(int x) {
  check[x] = true;
  for(int i = 1; i <= n; i++) {
    if(a[x][i] == 1 && check[i] == false) dfs(i);
  }
}

//인접 리스트를 이용한 구현  O(v + e)
void dfs(int x) {
  check[x] = true;
  for(int i = 0; i < a[x].size(); i++) {
    int y = a[x][i];
    if(check[y] == false) dfs(y);
  }
}


/* bfs ..queue */

//인접 행렬을 이용한 구현  O(v^2)
queue<int> q;
check[1] = true; q.push(1);  //큐에 넣을 때 방문함을 알림, 시작점
while(!q.empty()) {
  int x = q.front(); q.pop();
  for(int i = 1; i <= n; i++) {
    if(a[x][i] == 1 && check[i] == false) {
      check[i] = true;
      q.push(i);
    }
  }
}

//인접 리스트를 이용한 구현  O(v + e)
queue<int> q;
check[1] = true; q.push(1);  //큐에 넣을 때 방문함을 알림, 시작점
while(!q.empty()) {
  int x = q.front(); q.pop();
  for(int i = 0; i < a[x].size(); i++) {
    int y = a[x][i];
    if(check[y] == false) {
      check[y] = true;
      q.push(y);
    }
  }
}
