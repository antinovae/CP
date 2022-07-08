
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

typedef long long i64;

const int N = 500005;
int ls, lt;
int n, q, a[N];
i64 sum[N], l[N], r[N];
i64 v[N << 1], d[N << 1];
int preans[N], pos[N];
int lcp[N];
char s[N], t[N];

namespace tr {
vector<int> to[N];
vector<pair<int, int>> qy[N];
int v[N][19][2], d[N];

void dfs1(int i) {
  if (d[i] > 1) {
    int l = __lg(d[i]);
    for (int j = 1; j <= l; j++) {
      v[i][j][0] = v[v[i][j - 1][0]][j - 1][0];
      v[i][j][1] = max(v[i][j - 1][1], v[v[i][j - 1][0]][j - 1][1]);
    }
  }

  for (int j : to[i]) {
    d[j] = d[i] + 1, v[j][0][0] = i, v[j][0][1] = lcp[j + 1];
    dfs1(j);
  }
}

int find(int x, int l) {
  if (x)
    for (int i = __lg(d[x]); i != -1; i--)
      if ((1 << i) <= d[x] && v[x][i][1] < l)
        x = v[x][i][0];
  return lcp[x + 1] >= l ? x : -1;
}

namespace bits {
int s[N];

void add(int x, int v) {
  while (x <= lt)
    s[x] += v, x += x & (-x);
}
int query(int x) {
  int ans = 0;
  x = min(x, lt);
  while (x)
    ans += s[x], x &= x - 1;
  return ans;
}
} // namespace bits

void dfs(int i) {
  bool ok = 0;
  if (i != 0 && i != lt && i + lcp[i + 1] >= lt)
    bits::add(lt - i, 1), ok = 1;
  for (auto tp : qy[i]) {
    int x = bits::query(tp.first), y = tp.second;
    if (y > 0)
      ::d[y] += x, ::d[y + 1] -= x;
    else
      ::d[-y] += x;
  }
  for (int j : to[i])
    dfs(j);
  if (ok)
    bits::add(lt - i, -1);
}
} // namespace tr

void kmp() {
  static int kmp[N];
  tr::to[0].push_back(1);
  for (int i = 2, j = 0; i <= lt; i++) {
    while (j && t[j + 1] != t[i])
      j = kmp[j];
    if (t[j + 1] == t[i])
      j++;
    kmp[i] = j, tr::to[j].push_back(i);
  }

  for (int i = 1, j = 0; i <= ls; i++) {
    while (j && t[j + 1] != s[i])
      j = kmp[j];
    if (t[j + 1] == s[i])
      j++;
    preans[i] = preans[i - 1];
    if (j == lt)
      preans[i]++, j = kmp[j];
    pos[i] = j;
  }
}

void exkmp() {
  static int z[N];
  for (int i = 2, j = 0; i <= ls; i++) {
    if (j + z[j] > i)
      z[i] = min(z[i - j + 1], j + z[j] - i);
    while (s[i + z[i]] == s[1 + z[i]])
      z[i]++;
    if (i + z[i] > j + z[j])
      j = i;
  }

  for (int i = 1, j = 0; i <= lt; i++) {
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
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

  cin >> (s + 1) >> (t + 1);
  ls = strlen(s + 1), lt = strlen(t + 1);

  kmp(), exkmp();
  tr::dfs1(0);

  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> a[i], sum[i] = sum[i - 1] + a[i];

  cin >> q;
  int m = 0;
  for (int i = 1; i <= q; i++) {
    cin >> l[i] >> r[i], l[i] += lt - 1;
    if (l[i] <= r[i]) {
      if (l[i] != 1)
        v[++m] = l[i] - 1;
      v[++m] = r[i];
    }
  }
  sort(v + 1, v + m + 1), m = unique(v + 1, v + m + 1) - v;

  for (int i = 1, j = 1, x = 0; i <= n; i++) {
    while (j != m && v[j] <= sum[i]) {
      int l = v[j] - sum[i - 1];
      tr::qy[x].push_back({l, j});
      d[j] += preans[l], d[j + 1] -= preans[l];
      j++;
    }
    tr::qy[x].push_back({a[i], -j});
    d[j] += preans[a[i]];
    int y = a[i] < lt ? tr::find(x, a[i]) : -1;
    if (y == -1)
      x = pos[a[i]];
    else
      x = y + a[i];
  }

  tr::dfs(0);
  for (int i = 1; i <= m; i++)
    d[i] += d[i - 1];
  for (int i = 1; i <= q; i++) {
    if (l[i] > r[i])
      cout << 0 << '\n';
    else {
      int pl = lower_bound(v + 1, v + m, l[i] - 1) - v;
      if (l[i] == 1)
        pl = 0;
      int pr = lower_bound(v + 1, v + m, r[i]) - v;
      cout << d[pr] - d[pl] << '\n';
    }
  }
}

