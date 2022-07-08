#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 100010;
using ll = long long;

struct node {
  int x, y;

  node(int x = 0, int y = 0) : x(x), y(y) {}
} a[N], b[N];

node operator-(node a, node b) { return node(a.x - b.x, a.y - b.y); }

ll operator*(node a, node b) { return 1ll * a.x * b.y - 1ll * a.y * b.x; }

ll cross(node a, node o, node b) { return (a - o) * (b - o); }

int main() {
  int n = 0, m = 0, n0, m0;
  scanf("%d%d", &n0, &m0);
  for (int i = 1; i <= n0; i++) {
    node p;
    p.x = i, scanf("%d", &p.y);
    while (n > 1 && cross(a[n - 1], a[n], p) >= 0)
      n--;
    a[++n] = p;
  }
  for (int i = 1; i <= m0; i++) {
    node p;
    p.x = i, scanf("%d", &p.y);
    while (m > 1 && cross(b[m - 1], b[m], p) >= 0)
      m--;
    b[++m] = p;
  }
  long long ans = 0;
  int p = 1, q = 1;
  while (p < n || q < m) {
    if (q == m || (p < n && (a[p + 1] - a[p]) * (b[q + 1] - b[q]) >= 0))
      ans += 1ll * b[q].y * (a[p + 1].x - a[p].x), ++p;
    else
      ans += 1ll * a[p].y * (b[q + 1].x - b[q].x), ++q;
  }
  printf("%lld\n", ans);
  return 0;
}
