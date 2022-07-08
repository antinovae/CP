#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/* #ifdef CLANGD */
/* const int N = 101; */
/* #else */
const int N = 1000001;
/* #endif */

int len_s, len_t, n, Q, a[N];
int pre[N], pos[N], lcp[N];
ll sum[N], l[N], r[N], v[N << 1], d[N << 1];

vector<int> e[N];
vector<pair<int, int>> que[N];
int fa[N][19], mx[N][19], dep[N];

void pre_dfs(int x) {
  if (dep[x] > 1) {
    for (int j = 1; j < 19; j++) {
      fa[x][j] = fa[fa[x][j - 1]][j - 1];
      mx[x][j] = max(mx[x][j - 1], mx[fa[x][j - 1]][j - 1]);
    }
  }
  for (int v : e[x]) {
    dep[v] = dep[x] + 1;
    fa[v][0] = x;
    mx[v][0] = lcp[v + 1];
    pre_dfs(v);
  }
}

int find(int x, int l) {
  if (x) {
    for (int i = 18; i != -1; i--)
      if ((1 << i) <= dep[x] && mx[x][i] < l)
        x = fa[x][i];
  }
  return lcp[x + 1] >= l ? x : -1;
}

struct bits {
  int s[N];

  void add(int x, int v) {
    for (; x <= len_t; x += x & (-x))
      s[x] += v;
  }

  int query(int x) {
    int ans = 0;
    x = min(x, len_t);
    while (x)
      ans += s[x], x &= x - 1;
    return ans;
  }
} B;

void dfs(int x) {
  bool ok = false;
  if (x != 0 && x != len_t && x + lcp[x + 1] >= len_t)
    B.add(len_t - x, 1), ok = true;
  for (auto [v, y] : que[x]) {
    int x = B.query(v);
    if (y > 0)
      d[y] += x, d[y + 1] -= x;
    else
      d[-y] += x;
  }
  for (int v : e[x])
    dfs(v);
  if (ok)
    B.add(len_t - x, -1);
}

char s[N], t[N];

void kmp() {
  static int nxt[N];
  e[0].push_back(1);
  for (int i = 2, j = 0; i <= len_t; i++) {
    while (j && t[j + 1] != t[i])
      j = nxt[j];
    if (t[j + 1] == t[i])
      j++;
    nxt[i] = j, e[j].push_back(i);
  }

  for (int i = 1, j = 0; i <= len_s; i++) {
    while (j && t[j + 1] != s[i])
      j = nxt[j];
    if (t[j + 1] == s[i])
      j++;
    pre[i] = pre[i - 1];
    if (j == len_t)
      pre[i]++, j = nxt[j];
    pos[i] = j;
  }
}

void Z() {
  static int z[N];
  for (int i = 2, j = 0; i <= len_s; i++) {
    if (j + z[j] > i)
      z[i] = min(z[i - j + 1], j + z[j] - i);
    while (s[i + z[i]] == s[1 + z[i]])
      z[i]++;
    if (i + z[i] > j + z[j])
      j = i;
  }

  for (int i = 1, j = 0; i <= len_t; i++) {
    if (j + lcp[j] > i)
      lcp[i] = min(z[i - j + 1], j + lcp[j] - i);
    while (t[i + lcp[i]] == s[1 + lcp[i]])
      lcp[i]++;
    if (i + lcp[i] > j + lcp[j])
      j = i;
  }
}

int main() {
  freopen("youl.in", "r", stdin);
  freopen("youl.out", "w", stdout);
  scanf("%s%s", s + 1, t + 1);
  len_s = (int)strlen(s + 1), len_t = (int)strlen(t + 1);
  kmp(), Z();
  pre_dfs(0);
  scanf("%d", &n);
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]), sum[i] = sum[i - 1] + a[i];
  scanf("%d", &Q);

  int m = 0;
  for (int i = 1; i <= Q; i++) {
    scanf("%lld%lld", &l[i], &r[i]);
    assert(l[i] <= r[i]);
    l[i] += len_t - 1;
    if (l[i] != 1)
      v[++m] = l[i] - 1;
    v[++m] = r[i];
  }
  sort(v + 1, v + m + 1);
  m = (int)(unique(v + 1, v + m + 1) - v);

  for (int i = 1, j = 1, x = 0; i <= n; i++) {
    while (j != m && v[j] <= sum[i]) {
      int l = (int)(v[j] - sum[i - 1]);
      que[x].emplace_back(l, j);
      d[j] += pre[l], d[j + 1] -= pre[l];
      j++;
    }
    que[x].emplace_back(a[i], -j);
    d[j] += pre[a[i]];
    int y = a[i] < len_t ? find(x, a[i]) : -1;
    if (y == -1)
      x = pos[a[i]];
    else
      x = y + a[i];
  }

  dfs(0);
  for (int i = 1; i <= m; i++)
    d[i] += d[i - 1];

  for (int i = 1; i <= Q; i++) {
    int pl = (int)(lower_bound(v + 1, v + m, l[i] - 1) - v);
    int pr = (int)(lower_bound(v + 1, v + m, r[i]) - v);
    if (l[i] == 1)
      pl = 0;
    if (d[pr] - d[pl] >= 0)
      printf("%lld\n", d[pr] - d[pl]);
    else
      puts("0");
  }
}
