
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T>
bool cmin(T &x, T y) { return (y < x) ? x = y, 1 : 0; }

const int N = 250005;

int n, m;

set<int> s[N];

vector<int> z[N];

namespace UD {
vector<int> g[N], e[N];
int dfn[N], cnt, c[N], sz[N], low[N], s[N], top, dfncnt;

void add(int x, int y) {
  g[x].push_back(y), g[y].push_back(x);
}

void tarjan(int u) {
  dfn[u] = low[u] = ++dfncnt;
  s[++top] = u;
  for (int v : g[u]) {
    if (!dfn[v]) {
      tarjan(v);
      cmin(low[u], low[v]);
      if (low[v] >= dfn[u]) {
        int y;
        sz[++cnt] = 1;
        do {
          y = s[top--], e[cnt].push_back(y), sz[cnt]++;
        } while (y != v);
        e[cnt].push_back(u);
      }
    }
    else {
      cmin(low[u], dfn[v]);
    }
  }
}

void clear() {
  for (int i = 1; i <= n; i++)
    g[i].clear(), e[i].clear(), dfn[i] = low[i] = sz[i] = s[i] = 0;
  top = dfncnt = cnt = 0;
}
} // namespace UD

namespace D {
vector<int> g[N], e[N];

void add(int x, int y) {
  g[x].push_back(y);
}

int dfn[N], low[N], sz[N], dfncnt, c[N], cnt, s[N], top;
bool ins[N];

void tarjan(int u) {
  dfn[u] = low[u] = ++dfncnt;
  s[++top] = u;
  ins[u] = true;
  for (int v : g[u]) {
    if (!dfn[v]) {
      tarjan(v);
      cmin(low[u], low[v]);
    }
    else if (ins[v]) {
      cmin(low[u], dfn[v]);
    }
  }
  if (low[u] == dfn[u]) {
    int v;
    ++cnt;
    do {
      v = s[top--], ins[v] = false, c[v] = cnt, sz[cnt]++;
    } while (v != u);
  }
}

int in[N];
int q[N], w[N];

void clear() {
  for (int i = 1; i <= n; i++)
    in[i] = 0, e[i].clear(), w[i] = ins[i] = sz[i] = 0, c[i] = dfn[i] = low[i] = 0, g[i].clear();
  cnt = top = dfncnt = 0;
}

void addE(int x, int y) {
  in[y]++, e[x].push_back(y);
}

void work() {
  int hh = 1, tt = 0;
  for (int u = 1; u <= n; u++) {
    for (int v : g[u]) {
      if (c[u] != c[v])
        addE(c[v], c[u]); //, cout << u << "->" << v << "???" << c[u] << " " << c[v] << endl;
    }
  }
  for (int i = 1; i <= cnt; i++)
    w[i] = sz[i];
  for (int i = 1; i <= cnt; i++)
    if (!in[i])
      q[++tt] = i;
  while (hh <= tt) {
    int u = q[hh++];
    for (int v : z[u])
      w[u] -= w[v];
    for (int v : e[u]) {
      w[v] += w[u];
      if (--in[v] == 0)
        q[++tt] = v;
    }
  }
  ll ans = 0;
  for (int i = 1; i <= cnt; i++)
    ans += 1ll * sz[i] * w[i];
  printf("%lld\n", ans);
}
} // namespace D

void clear() {
  UD::clear();
  D::clear();
  for (int i = 1; i <= n; i++) {
    s[i].clear();
    z[i].clear();
  }
}

void upd() {
  for (int i = 1; i <= UD::cnt; i++) {
    int len = UD::e[i].size();
    if (len < 3)
      continue;
    int C = 0, R = 0;
    int cp = 0, cr = 0;
    for (int j = 0; j < len; j++) {
      int u = UD::e[i][j];
      int le = UD::e[i][(j - 1 + len) % len];
      int re = UD::e[i][(j + 1) % len];
      if (s[u].count(le) && s[u].count(re))
        C++, cp = u;
      if (s[le].count(u) && s[re].count(u))
        R++, cr = u;
    }
    if (C == 1 && R == 1)
      z[D::c[cp]].push_back(D::c[cr]);
  }
}

int main() {
  int T;
  scanf("%d", &T);
  int C = 0;
  while (T--) {
    ++C;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
      int u, v;
      scanf("%d%d", &u, &v);
      D::add(u, v);
      UD::add(u, v);
      s[u].insert(v);
    }
    UD::tarjan(1);
    for (int i = 1; i <= n; i++)
      if (!D::dfn[i])
        D::tarjan(i);
    upd();
    D::work();
    clear();
  }
  return 0;
}
