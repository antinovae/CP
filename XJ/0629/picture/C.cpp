#include <array>
#include <bits/stdc++.h>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;
const int INF = 1e9;

int pid[41][41][5];
tuple<int, int, int> at[10001];

void pr(int i) {
  auto [x, y, z] = at[i];
  printf("(%d, %d, %d) ", x, y, z);
}

struct flow {
  struct edge {
    int u, v, val, nxt;
  };

  vector<edge> e;
  vector<int> dis, cur, head;
  int S, T;

  flow(int n, int m) {
    S = n * m * 4 + 1, T = n * m * 4 + 2;
    dis.resize(T + 1);
    head.resize(T + 1);
    fill(head.begin(), head.end(), -1);
    cur.resize(T + 1);
  }

  void add(int u, int v, int w) {
    e.push_back({u, v, w, head[u]});
    head[u] = (int)e.size() - 1;
    e.push_back({v, u, 0, head[v]});
    head[v] = (int)e.size() - 1;
  }

  int bfs() {
    fill(dis.begin(), dis.end(), INF);
    queue<int, list<int>> q;
    q.push(S);
    dis[S] = 0;
    while (!q.empty()) {
      int x = q.front();
      q.pop();
      for (int p = head[x]; p != -1; p = e[p].nxt) {
        if (e[p].val) {
          int v = e[p].v;
          if (dis[v] > dis[x] + 1) {
            dis[v] = dis[x] + 1;
            q.push(v);
            if (v == T)
              return 1;
          }
        }
      }
    }
    return 0;
  }

  int dfs(int x, int in) {
    if (x == T)
      return in;
    int out = 0;
    for (int &p = cur[x]; p != -1; p = e[p].nxt) {
      int v = e[p].v;
      if (e[p].val && dis[v] == dis[x] + 1) {
        int res = dfs(v, min(in, e[p].val));
        e[p].val -= res;
        e[p ^ 1].val += res;
        in -= res;
        out += res;
        if (!in)
          return out;
      }
    }
    return out;
  }

  int dinic() {
    int max_flow = 0;
    while (bfs()) {
      cur = vector<int>(head.begin(), head.end());
      max_flow += dfs(S, INF);
    }
    return max_flow;
  }
};

int id(int i, int j, int c) {
  return pid[i][j][c];
}

int col[41][41];

void _main() {

  int n, m, A, B, C;
  scanf("%d%d%d%d%d", &n, &m, &A, &B, &C);
  for (int i = 1; i <= n; i++) {
    static char s[41];
    scanf("%s", s + 1);
    for (int j = 1; j <= m; j++) {
      col[i][j] = s[j] == '1';
    }
  }
  flow F(n, m);
  int idx = 0;
  for (int k = 1; k <= 4; k++)
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m; j++)
        pid[i][j][k] = ++idx,
        at[idx] = {i, j, k};
  at[++idx] = {-1, -1, -1};
  at[++idx] = {-2, -2, -2};
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      F.add(id(i, j, 1), F.T, A);
      F.add(F.S, id(i, j, 2), A);
      F.add(F.S, id(i, j, 3), A);
      F.add(id(i, j, 4), F.T, A);
      if (j + 1 <= m) {
        F.add(id(i, j, 1), id(i, j + 1, 1), B);
        F.add(id(i, j + 1, 2), id(i, j, 2), B);
      }
      else{
        F.add(id(i, j, 1), F.T, B);
        F.add(F.S, id(i, j, 2), B);

      }
      if (i + 1 <= n) {
        F.add(id(i + 1, j, 3), id(i, j, 3), B);
        F.add(id(i, j, 4), id(i + 1, j, 4), B);
      }
      else{
        F.add(F.S, id(i, j, 3), B);
        F.add(id(i, j, 4), F.T, B);

      }
      if (col[i][j] == 1) {
        F.add(F.S, id(i, j, 2), INF);
        F.add(id(i, j, 4), F.T, INF);
        F.add(id(i, j, 3), id(i, j, 1), C);
      }
      else {
        F.add(id(i, j, 1), id(i, j, 3), INF);
        F.add(id(i, j, 1), id(i, j, 4), C);
        F.add(id(i, j, 2), id(i, j, 3), C);
      }
    }
  }
  printf("%d\n", F.dinic());
}

int main() {
  freopen("picture.in", "r", stdin);
  freopen("picture.out", "w", stdout);
  int T;
  scanf("%d", &T);
  while (T--)
    _main();
}
