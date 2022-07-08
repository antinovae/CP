#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 100001;
struct node {
  int a[2][2];
  int tag, tag2;
} t[maxn << 2];
#define ls (x << 1)
#define rs (x << 1 | 1)
#define mid ((l + r) >> 1)
void pushup(int x) {
  t[x].a[0][0] = max(t[ls].a[0][0] + t[rs].a[0][0], t[ls].a[0][1] + t[rs].a[1][0]);
  t[x].a[0][1] = max(t[ls].a[0][0] + t[rs].a[0][1], t[ls].a[0][1] + t[rs].a[1][1]);
  t[x].a[1][0] = max(t[ls].a[1][0] + t[rs].a[0][0], t[ls].a[1][1] + t[rs].a[1][0]);
  t[x].a[1][1] = max(t[ls].a[1][0] + t[rs].a[0][1], t[ls].a[1][1] + t[rs].a[1][1]);
  cout << "up " << x << " " << t[x].a[0][0] << " " << t[x].a[0][1] << " "
       << t[x].a[1][0] << " " << t[x].a[1][1] << endl;
}
void add(int x, int k) {
  t[x].tag += k;
  t[x].a[0][1] -= k;
  t[x].a[1][0] += k;
}
void add2(int x, int k) {
  t[x].tag2 += k;
  t[x].a[0][0] = max(0ll, t[x].a[0][0] + k);
  t[x].a[1][0] += k;
}
void pushdown(int x) {
  if (t[x].tag) {
    add(ls, t[x].tag);
    add(rs, t[x].tag);
    t[x].tag = 0;
  }
  if (t[x].tag2) {
    add(ls, t[x].tag2);
    add(rs, t[x].tag2);
    t[x].tag2 = 0;
  }
}
void add(int x, int l, int r, int L, int R, int k) {
  if (L > R || L > r)
    return;
  cout << "add " << x << " " << L << " " << R << " " << k << endl;
  if (L <= l && r <= R) {
    add(x, k);
  } else {

    pushdown(x);
    if (L <= mid)
      add(ls, l, mid, L, R, k);
    if (R > mid)
      add(rs, mid + 1, r, L, R, k);
    pushup(x);
  }
}
void add2(int x, int l, int r, int L, int R, int k) {
  if (L > R || L > r)
    return;
  cout << "add2 " << x << " " << L << " " << R << " " << k << endl;
  if (L <= l && r <= R) {
    add2(x, k);
  } else {
    pushdown(x);
    if (L <= mid)
      add2(ls, l, mid, L, R, k);
    if (R > mid)
      add2(rs, mid + 1, r, L, R, k);
    pushup(x);
  }
}
void modify(int x, int l, int r, int k, int v) {
  if (l == r) {
    t[x].a[0][0] = max(0ll, t[x].tag2 += v);
    t[x].a[1][0] += v;
  } else {
    pushdown(x);
    if (k <= mid)
      modify(ls, l, mid, k, v);
    else
      modify(rs, mid + 1, r, k, v);
    pushup(x);
  }
}
int opt[maxn], a[maxn], c[maxn];
pair<int, int> b[maxn];
signed main() {
  int Q, len, n = 0, m = 0;
  scanf("%lld%lld", &Q, &len);
  for (int i = 1; i <= Q; i++) {
    scanf("%lld%lld%lld", &opt[i], &a[i], &c[i]);
    if (opt[i] == 1) {
      b[++n] = {a[i], i};
    }
  }
  sort(b + 1, b + 1 + n);
  for (int i = 1; i <= n; i++)
    a[b[i].second] = i;
  for (int i = 1; i <= Q; i++) {
    if (opt[i] == 1) {
      add(1, 1, n, a[i] + 1, n, c[i]);
      modify(1, 1, n, a[i], c[i]);
      m += c[i];
    } else {
      int L = lower_bound(b + 1, b + 1 + n, make_pair(a[i] - len, -1ll)) - b;
      int R =
          upper_bound(b + 1, b + 1 + n, make_pair(a[i] + len, Q + 1)) - b - 1;
      add(1, 1, n, R + 1, n, -c[i]);
      add2(1, 1, n, L, R, -c[i]);
    }
    printf("%lld\n", m - t[1].a[0][0]);
  }
}
