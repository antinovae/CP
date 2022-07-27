#include <bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5;
vector<int> ed[N];
array<int, N> dep, dfn, sz;
array<array<int, 20>, N> fa;

void dfs_bas(int x, int f) {
  dep[x] = dep[f] + 1;
  fa[x][0] = f;
  dfn[x] = ++dfn[0];
  sz[x] = 1;
  for (int i = 1; i < 20; i++)
    fa[x][i] = fa[fa[x][i - 1]][i - 1];
  for (int i = 0; i < ed[x].size(); i++)
    if (ed[x][i] != f) {
      dfs_bas(ed[x][i], x);
      sz[x] += sz[ed[x][i]];
    }
}

#define ID(i, j) (((i)-1) * 20 + (j) + 1)

int anc(int x, int d) {
  for (int i = 19; i >= 0; i--)
    if (d & (1 << i))
      x = fa[x][i];
  return x;
}

vector<int> fnd_anc(int x, int d) {
  vector<int> P;
  for (int i = 19; i >= 0; i--) {
    if (d & (1 << i)) {
      P.push_back(ID(x, i));
      x = fa[x][i];
    }
  }
  return P;
}

int LCA(int x, int y) {
  if (dep[x] < dep[y])
    swap(x, y);
  for (int i = 19; i >= 0; i--)
    if (dep[fa[x][i]] >= dep[y])
      x = fa[x][i];
  if (x == y)
    return x;
  for (int i = 19; i >= 0; i--)
    if (fa[x][i] != fa[y][i])
      x = fa[x][i], y = fa[y][i];
  return fa[x][0];
}

vector<int> fnd_pth(int x, int v) {
  int l = LCA(x, v);
  vector<int> U = fnd_anc(x, dep[x] - dep[l] + 1), V = fnd_anc(v, dep[v] - dep[l] + 1);
  for (int i = 0; i < V.size(); i++)
    U.push_back(V[i]);
  return U;
}

int nxt_node(int u, int v) {
  if (!(dfn[v] > dfn[u] && dfn[v] < dfn[u] + sz[u]))
    return fa[u][0];
  return anc(v, dep[v] - dep[u] - 1);
}

vector<int> r[8000000];
int deg[8000000];

bool topo(int n) {
  for (int i = 1; i <= n; i++)
    for (int j = 0; j < r[i].size(); j++)
      deg[r[i][j]]++;
  queue<int> q;
  for (int i = 1; i <= n; i++)
    if (!deg[i])
      q.push(i);
  int cnt = 0;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    cnt++;
    for (int i = 0; i < r[u].size(); i++) {
      deg[r[u][i]]--;
      if (!deg[r[u][i]])
        q.push(r[u][i]);
    }
  }
  for (int i = 1; i <= n; i++)
    deg[i] = 0;
  return cnt == n;
}

int main() {
  int TT = 0;
  scanf("%d", &TT);
  while (TT--) {
    int n = 0;
    scanf("%d", &n);
    for (int i = 1, u = 0, v = 0; i < n; i++) {
      scanf("%d%d", &u, &v);
      ed[u].push_back(v), ed[v].push_back(u);
    }
    dfs_bas(1, 0);
    int tot = ID(n, 19);
    // printf("%d\n",tot);
    int m = 0;
    scanf("%d", &m);
    for (int i = 1, s = 0, t = 0; i <= m; i++) {
      scanf("%d%d", &s, &t);
      int p = nxt_node(s, t), q = nxt_node(t, s);
      // printf("%d %d\n",p,q);
      vector<int> P = fnd_pth(p, t), Q = fnd_pth(s, q);
      // for(int j=0;j<P.size();j++)printf("%d ",P[j]);puts("");
      // for(int j=0;j<Q.size();j++)printf("%d ",Q[j]);puts("");
      for (int j = 0; j < P.size(); j++)
        r[P[j] + m].push_back(i);
      r[i].push_back(ID(s, 0) + m);
      for (int j = 0; j < Q.size(); j++)
        r[i].push_back(Q[j] + m + tot);
      r[ID(t, 0) + m + tot].push_back(i);
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= 19; j++) {
        r[m + ID(i, j - 1)].push_back(m + ID(i, j));
        if (fa[i][j - 1])
          r[m + ID(fa[i][j - 1], j - 1)].push_back(m + ID(i, j));
        r[m + tot + ID(i, j)].push_back(m + tot + ID(i, j - 1));
        if (fa[i][j - 1])
          r[m + tot + ID(i, j)].push_back(m + tot + ID(fa[i][j - 1], j - 1));
      }
    }

    /*for(int i=1;i<=2*tot+m;i++)
    {
            for(int j=0;j<r[i].size();j++)printf("%d %d\n",i,r[i][j]);
    }*/

    puts(topo(2 * tot + m) ? "Yes" : "No");

    for (int i = 1; i <= n; i++)
      ed[i].clear(), sz[i] = dfn[i] = dep[i] = 0;
    for (int i = 1; i <= n; i++)
      for (int j = 0; j < 20; j++)
        fa[i][j] = 0;
    for (int i = 1; i <= 2 * tot + m; i++)
      r[i].clear();
  }
}
