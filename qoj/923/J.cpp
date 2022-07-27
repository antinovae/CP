#include <bits/stdc++.h>
#include <vector>
using namespace std;
const int N = 200001, mo = 998244353;
int n;
int a[N * 3];

int nxt(int x) {
  x++;
  if (x > 3 * n)
    x = 1;
  return x;
}

int prv(int x) {
  x--;
  if (x <= 0)
    x = 3 * n;
  return x;
}

vector<int> c[N * 3];

int solve(int beg, int ed) {
  static vector<int> cnt[N * 3];
  for (int i = 1; i <= n; i++)
    cnt[i].clear();
  for (int i = beg; i != ed; i = nxt(i)) {
    cnt[a[i]].push_back(i);
  }
  vector<pair<int, int>> q;
  for (int i = 1; i <= n; i++) {
    if (i != a[1]) {
      if (cnt[i].size() <= 1)
        return 0;
      else if (cnt[i].size() == 2) {
        q.emplace_back(cnt[i][0], cnt[i][1]);
      }
      else if (cnt[i].size() == 3) {
        q.emplace_back(cnt[i][0], cnt[i][1]);
        q.emplace_back(cnt[i][1], cnt[i][2]);
      }
      else
        assert(0);
    }
  }
  static int p[N * 3];
  memset(p, 0, sizeof(p));
  for (auto [x, y] : q) {
    p[y] = x;
  }
  static int f[N * 3], g[N * 3];
  memset(f, 0, sizeof(f));
  memset(g, 0, sizeof(g));
  g[prv(beg)] = 1;
  for (int i = beg; i != ed; i = nxt(i)) {
    if (!p[i]) {
      f[i] = f[prv(i)];
      g[i] = g[prv(i)];
    }
    else {
      int val1 = f[prv(i)];
      int val2 = f[prv(p[i])] + 1;
      if (val1 >= val2) {
        f[i] = val1;
        (g[i] += g[prv(i)]) %= mo;
      }
      if (val2 >= val1) {
        f[i] = val2;
        (g[i] += g[prv(p[i])]) %= mo;
      }
    }
  }
  int y = prv(ed);
  if (f[y] == n - 1) {
    return g[y];
  }
  else
    return 0;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= 3 * n; i++) {
    scanf("%d", &a[i]);
    c[a[i]].push_back(i);
  }
  int x = a[1], ans = 0;

  (ans += solve(c[x][1] + 1, c[x][0])) %= mo;
  (ans += solve(c[x][2] + 1, c[x][1])) %= mo;
  (ans += solve(c[x][0] + 1, c[x][2])) %= mo;
  cout << ans << endl;
}
