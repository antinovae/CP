
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 3, K = 17;
bool fl[N];
int n, m, p, q, fa[N][K], son[N], k;
ll dis[N], h[N], s[N], ans[N];
vector<pair<int, int>> g[N];

struct lnk {
  int u;
  ll h;
} b[N];

void dfs0(int x, int fa) {
  if (dis[x] > dis[p])
    p = x;
  for (auto [v, c] : g[x])
    if (v != fa)
      dis[v] = dis[x] + c, dfs0(v, x);
}

void dfs1(int x) {
  son[x] = h[x] = 0;
  for (int j = 1; j < K; j++)
    fa[x][j] = fa[fa[x][j - 1]][j - 1];
  for (auto [v, c] : g[x])
    if (v != fa[x][0]) {
      dis[v] = dis[x] + c, fa[v][0] = x, dfs1(v);
      if (h[v] + c >= h[x]) {
        h[x] = h[v] + c;
        son[x] = v;
      }
    }
  for (auto [v, c] : g[x])
    if (v != fa[x][0] && v != son[x])
      b[++k] = {v, h[v] + c};
}

void Solve(int r) {
  int u, v;
  fa[r][0] = 0, k = 0, dis[r] = 0, std::fill(fl + 1, fl + 1 + n, 0);
  dfs1(r);
  b[++k] = {son[r], h[r]};
  sort(b + 1, b + 1 + k, [](lnk a, lnk b) { return a.h > b.h; });
  for (int i = 1; i <= k; i++) {
    s[i] = s[i - 1] + b[i].h;
    if (i <= m)
      for (u = b[i].u; u; u = son[u])
        fl[u] = 1;
  }
  fl[r] = 1;
  for (u = 1; u <= n; u++) {
    if (m > k) {
      ans[u] = std::max(ans[u], s[k]);
      continue;
    }
    if (u == r) {
      ans[u] = std::max(ans[u], s[m]);
      continue;
    }
    if (fl[u]) {
      ans[u] = std::max(ans[u], std::max(s[m - 1], s[m] - h[u]));
      continue;
    }
    v = u;
    for (int j = K - 1; ~j; j--)
      if (fa[v][j] && !fl[fa[v][j]])
        v = fa[v][j];
    v = fa[v][0];
    ans[u] = std::max(ans[u], std::max(s[m - 1], s[m] - h[v]) + dis[u] - dis[v]);
  }
}

int main() {
  int u, v, c;
  scanf("%d%d", &n, &m);
  for (int i = 1; i < n; i++)
    scanf("%d%d%d", &u, &v, &c), g[u].emplace_back(v, c), g[v].emplace_back(u, c);
  p = 1, dfs0(1, 0), dis[q = p] = 0, dfs0(q, 0);
  Solve(p), Solve(q);
  for (u = 1; u <= n; u++)
    printf("%lld\n", ans[u]);
  return 0;
}
