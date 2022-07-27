#include <bits/stdc++.h>
#define LL long long
#define uLL unsigned long long
#define db double

using namespace std;
const int N = 2e5 + 10;

int rd() {
  int x = 0, w = 1;
  char ch = 0;
  while (ch < '0' || ch > '9') {
    if (ch == '-')
      w = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + (ch ^ 48);
    ch = getchar();
  }
  return x * w;
}

int to[N << 1], nt[N << 1], hd[N], tot = 1;

void adde(int x, int y) {
  ++tot, to[tot] = y, nt[tot] = hd[x], hd[x] = tot;
  ++tot, to[tot] = x, nt[tot] = hd[y], hd[y] = tot;
}

int n, k, ans, c[N], sm[N], vc[N], tc, vs[N], ti, fa[N], mx, rt, nsz, sz[N];
bool ban[N];
vector<int> sb[N];

void fdrt(int x, int ffa) {
  sz[x] = 1;
  int nz = 0;
  for (int i = hd[x]; i; i = nt[i]) {
    int y = to[i];
    if (ban[y] || y == ffa)
      continue;
    fdrt(y, x), sz[x] += sz[y], nz = max(nz, sz[y]);
  }
  nz = max(nz, nsz - sz[x]);
  if (mx > nz)
    mx = nz, rt = x;
}

void d1(int x, int ffa) {
  if (vc[c[x]] < tc)
    vc[c[x]] = tc, sb[c[x]].clear();
  sb[c[x]].push_back(x);
  for (int i = hd[x]; i; i = nt[i]) {
    int y = to[i];
    if (ban[y] || y == ffa)
      continue;
    fa[y] = x, d1(y, x);
  }
}

queue<int> q;

void wk(int x) {
  mx = nsz, fdrt(x, 0), x = rt;
  ban[x] = 1, fdrt(x, 0);
  ++tc, fa[x] = 0, d1(x, 0);
  while (!q.empty())
    q.pop();
  ++tc, ++ti, vc[c[x]] = tc, q.push(c[x]);
  int na = -1;
  while (!q.empty()) {
    int z = q.front();
    q.pop();
    ++na;
    int nn = sb[z].size();
    if (nn < sm[z]) {
      na += n;
      break;
    }
    for (int i = 0; i < nn; ++i) {
      int y = sb[z][i];
      while (y && vs[y] < ti) {
        if (vc[c[y]] < tc)
          vc[c[y]] = tc, q.push(c[y]);
        vs[y] = ti, y = fa[y];
      }
    }
  }
  ans = min(ans, na);
  for (int i = hd[x]; i; i = nt[i]) {
    int y = to[i];
    if (ban[y])
      continue;
    nsz = sz[y], wk(y);
  }
}

int main() {
  n = rd(), k = rd(), ans = k - 1;
  for (int i = 1; i < n; ++i)
    adde(rd(), rd());
  for (int i = 1; i <= n; ++i)
    c[i] = rd(), ++sm[c[i]];
  nsz = n, wk(1);
  printf("%d\n", ans);
}
