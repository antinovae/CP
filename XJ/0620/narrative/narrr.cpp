#include <bits/stdc++.h>
const int maxn = 1e5 + 5;
using namespace std;
using int128 = __int128;
using ll = long long;
using ull = unsigned long long;
int T, n, m;
ll k, a[maxn], b[maxn];
int128 c[maxn];
ull seed;

ll Get() {
  seed = (seed << 43) ^ (seed >> 15) ^ (seed << 27) ^ seed;
  return seed >> 4;
}

void write(int128 x) {
  if (x >= 10)
    write(x / 10);
  putchar('0' + x % 10);
}

int128 f(ll x, ll y) {
  return ((((int128)x * y >> 60) * (x + y) >> 60) * (x >> 30) * (y >> 30) >> 60) * (x + y);
}

struct seg {
  /* int a[M]; */
  int l, r, pos, mid, id, hv;

  int get() {
    pos = (l + r) / 2;
    if (l > r) {
      hv = 0;
      return 0;
    }
    return f(id, pos);
    /* if(!a[pos])a[pos]=query(id,pos); */
    /* return a[pos]; */
  }
} t[maxn];

void init() {
  for (int i = 1; i <= n; i++) {
    t[i].l = 1, t[i].r = m, t[i].id = i, t[i].hv = 1;
    t[i].get();
  }
}

int128 vis[maxn][maxn];

int128 query(ll x, ll y) {
  if (!vis[x][y])
    vis[x][y] = f(x, y);
  return vis[x][y];
}

bool check(int128 mid) {
  int j = 1, cnt = 0;
  for (int i = n; i >= 1; i--) {
    while (query(i, j) <= mid)
      ++j;
    cnt += (j - 1);
  }
  return cnt <= k;
}

int128 work() {
  int128 L = 1, R = query(n, m), res = -1;
  while (L < R) {
    int128 mid = (L + R) / 2;
    if (check(mid)) {
      res = mid;
      L = mid + 1;
    }
    else {
      R = mid - 1;
    }
  }
  return res;
}

void solve() {
  cin >> n >> m >> k >> seed;
  for (int i = 1; i <= n; i++)
    a[i] = Get();
  for (int i = 1; i <= m; i++)
    b[i] = Get();
  write(work());
  putchar('\n');
}

#include <bits/stdc++.h>
using namespace std;
const int N = 51, M = 1010;
int query(int x, int y);

int main() {
  cin >> T;
  while (T--)
    solve();
  return 0;
}
