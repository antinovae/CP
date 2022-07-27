#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
const int N = 1001;

namespace G2 {
int n;
using ll = long long;
vector<int> e[N];
vector<int> g[N], bcc[N], col[N];
array<int, N> dfn, low, ed, sz, cnt_ed;
stack<int, vector<int>> st;
int indec, cc;

void add(int x, int y) {
  cout << "add " << x << " " << y << endl;
  e[x].push_back(y);
  e[y].push_back(x);
  g[x].push_back(y);
}

void tarjan(int x, int fa) {
  dfn[x] = low[x] = ++indec;
  st.push(x);
  for (auto v : e[x]) {
    if (v != fa) {
      if (!dfn[v]) {
        tarjan(v, x);
        low[x] = min(low[x], low[v]);
        if (low[v] >= dfn[x]) {
          ++cc;
          while (st.top() != x) {
            int v = st.top();
            st.pop();
            bcc[cc].push_back(v);
            col[v].push_back(cc);
          }
          bcc[cc].push_back(x);
          col[x].push_back(cc);
        }
      }
      else if (dfn[v] < dfn[x])
        low[x] = min(low[x], dfn[v]);
    }
  }
}

ll f[N];

vector<int> per;

void topsort() {
  static array<int, N> ind;
  for (int i = 1; i <= n; i++) {
    ind[i] = (int)g[i].size();
  }
  stack<int, vector<int>> q;
  for (int i = 1; i <= n; i++) {
    if (!ind[i])
      q.push(i);
  }
  while (!q.empty()) {
    int x = q.top();
    q.pop();
    per.push_back(x);
    for (auto v : g[x]) {
      ind[v]--;
      if (ind[v] == 0) {
        q.push(v);
      }
    }
  }
}

ll solve() {
  for (int i = 1; i <= n; i++) {
    sort(e[i].begin(), e[i].end());
    e[i].erase(unique(e[i].begin(), e[i].end()), e[i].end());
    sort(g[i].begin(), g[i].end());
    g[i].erase(unique(g[i].begin(), g[i].end()), g[i].end());
  }
  for (int i = 1; i <= n; i++) {
    if (!dfn[i])
      tarjan(i, 0);
  }
  /* for (int i = 1; i <= n; i++) { */
  /*   if (e[i].size() == 0) { */
  /*     for (auto v : col[i]) { */
  /*       cnt_ed[col[i]]++; */
  /*     } */
  /*   } */
  /* } */
  /* for (int i = 1; i <= n; i++) { */
  /*   if (e[i].size() == 1) { */
  /*     if (cnt_ed[col[i]] == 1) */
  /*       ed[col[i]] = i; */
  /*   } */
  /* } */
  /* for (int i = 1; i <= n; i++) */
  /*   cout << col[i] << " "; */
  cout << endl;
  for (int i = 1; i <= cc; i++) {
    cout << i << ' ' << ed[i] << endl;
  }
  topsort();
  reverse(per.begin(), per.end());
  ll ans = 0;
  for (auto x : per) {
    unordered_map<int, int> cnt;
    for (auto v : g[x]) {
      f[x] += f[v];
      cnt[G2::col[v]]++;
    }
    for (auto [key, val] : cnt) {
      if (val >= 2 && ed[key])
        f[x] -= f[ed[key]];
    }
    f[x] = f[x] * sz[x];
    f[x] += 1ll * sz[x] * sz[x];
    ans += f[x];
  }
  return ans;
}

} // namespace G2

namespace G1 {
int n;
vector<int> e[N];
array<int, N> dfn, low, col, in;
stack<int, vector<int>> st;
int indec, cc;

void add(int x, int y) {
  e[x].push_back(y);
}

void tarjan(int x) {
  cout << "tar " << x << endl;
  dfn[x] = low[x] = ++indec;
  in[x] = 1;
  st.push(x);
  for (auto v : e[x]) {
    cout << v << endl;
    if (!dfn[v]) {
      tarjan(v);
      low[x] = min(low[x], low[v]);
    }
    else if (in[v])
      low[x] = min(low[x], low[v]);
  }
  cout << x << " " << dfn[x] << " " << low[x] << endl;
  if (dfn[x] == low[x]) {
    ++cc;
    while (st.top() != x) {
      int v = st.top();
      st.pop();
      in[v] = 0;
      G2::sz[cc]++;
      col[v] = cc;
    }
    st.pop();
    in[x] = 0;
    G2::sz[cc]++;
    col[x] = cc;
  }
}

void solve() {
  for (int i = 1; i <= n; i++) {
    if (!dfn[i])
      tarjan(i);
  }
  for (int i = 1; i <= n; i++) {
    cout << col[i] << " ";
  }
  cout << endl;
  for (int i = 1; i <= cc; i++) {
    cout << i << ' ' << G2::sz[i] << endl;
  }
  for (int i = 1; i <= n; i++) {
    for (auto j : e[i]) {
      if (col[i] != col[j]) {
        G2::add(col[i], col[j]);
      }
    }
  }
  G2::n = cc;
}
} // namespace G1

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    G1::add(x, y);
  }
  G1::n = n;
  G1::solve();
  printf("%lld\n", G2::solve());
}
