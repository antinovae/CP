#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
typedef __int128 lll;
const int N = 5610, Q = 3000010;
ll px[N], py[N];
int tx, ty;

struct vip {
  ll xl, yl, xr, yr;
  int c;
} p[N];

ll f[N][N];
int gr[N][N], gd[N][N];
ll qx[Q], qy[Q], ans[Q];
vector<int> g[N][N];

struct node {
  ll x, y;

  node(ll x = 0, ll y = 0) : x(x), y(y) {}

  node operator-(const node a) const { return node(x - a.x, y - a.y); }

  lll operator*(const node a) const { return (lll)x * a.y - (lll)y * a.x; }

  ll calc(ll w) { return x * w + y; }
} ton[N];

int tp;

lll cross(node a, node o, node b) { return (a - o) * (b - o); }

ll get_max(ll x) {
  int l = 1, r = tp;
  ll res = 0;
  while (r - l > 3) {
    int mid = (l + r) >> 1;
    if (ton[mid].calc(x) < ton[mid + 1].calc(x))
      l = mid + 1;
    else
      r = mid;
  }
  for (int i = l; i <= r; i++)
    res = max(res, ton[i].calc(x));
  // cerr<<x<<":"<<res<<" ";
  return res;
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    ll t, a, b;
    scanf("%lld%lld%lld%d", &t, &a, &b, &p[i].c);
    p[i].xl = t + a, p[i].yl = t - a, p[i].xr = t + abs(a - b) + b, p[i].yr = t + abs(a - b) - b;
    px[++tx] = p[i].xl, px[++tx] = p[i].xr;
    py[++ty] = p[i].yl, py[++ty] = p[i].yr;
    p[i].c /= 2;
    // cerr<<p[i].xl<<" "<<p[i].yl<<" "<<p[i].xr<<" "<<p[i].yr<<endl;
  }
  sort(px + 1, px + tx + 1), sort(py + 1, py + ty + 1);
  tx = unique(px + 1, px + tx + 1) - px - 1, ty = unique(py + 1, py + ty + 1) - py - 1;
  for (int i = 1; i <= n; i++) {
    p[i].xl = lower_bound(px + 1, px + tx + 1, p[i].xl) - px;
    p[i].xr = lower_bound(px + 1, px + tx + 1, p[i].xr) - px;
  }
  for (int i = 1; i <= n; i++) {
    p[i].yl = lower_bound(py + 1, py + ty + 1, p[i].yl) - py;
    p[i].yr = lower_bound(py + 1, py + ty + 1, p[i].yr) - py;
  }
  for (int i = 1; i <= n; i++) {
    if (p[i].xl == p[i].xr)
      for (int j = p[i].yl; j < p[i].yr; j++)
        gr[p[i].xl][j] = max(gr[p[i].xl][j], p[i].c);
    else
      for (int j = p[i].xl; j < p[i].xr; j++)
        gd[j][p[i].yl] = max(gd[j][p[i].yl], p[i].c);
  }
  for (int i = tx; i; i--)
    for (int j = ty; j; j--) {
      if (i < tx)
        f[i][j] = max(f[i][j], (px[i + 1] - px[i]) * gd[i][j] + f[i + 1][j]);
      if (j < ty)
        f[i][j] = max(f[i][j], (py[j + 1] - py[j]) * gr[i][j] + f[i][j + 1]);
    }
  // for(int i=1;i<=tx;i++,cerr<<endl)
  // for(int j=1;j<=ty;j++) cerr<<f[i][j]<<" ";
  for (int i = 1; i <= m; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    qx[i] = x + y, qy[i] = x - y;
    x = lower_bound(px + 1, px + tx + 1, qx[i]) - px;
    y = lower_bound(py + 1, py + ty + 1, qy[i]) - py;
    qx[i] = px[x] - qx[i], qy[i] = py[y] - qy[i];
    ans[i] = f[x][y] + max(qx[i] * gd[x - 1][y], qy[i] * gr[x][y - 1]);
    g[x][y].push_back(i);
  }
  for (int i = 2; i <= tx; i++) {
    tp = 0;
    for (int j = ty; j; j--) {
      node p(gd[i - 1][j], f[i][j]);
      while (tp > 1 && cross(ton[tp - 1], ton[tp], p) >= 0)
        tp--;
      ton[++tp] = p;
      for (int v : g[i][j])
        ans[v] = max(ans[v], get_max(qx[v]));
    }
  }
  for (int j = 2; j <= ty; j++) {
    tp = 0;
    for (int i = tx; i; i--) {
      node p(gr[i][j - 1], f[i][j]);
      while (tp > 1 && cross(ton[tp - 1], ton[tp], p) >= 0)
        tp--;
      ton[++tp] = p;
      for (int v : g[i][j])
        ans[v] = max(ans[v], get_max(qy[v]));
    }
  }
  for (int i = 1; i <= m; i++)
    printf("%lld\n", ans[i]);
  return 0;
}
