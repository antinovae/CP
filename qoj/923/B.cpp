#include <bits/stdc++.h>
using namespace std;
const int N = 4e5 + 5;
int vis[N], a[N], tp[N];
vector<int> c[N];
int n;

struct seg {
  int mx, tag;

  void put(int x) {
    tag += x;
    mx += x;
  }
} t[N * 4];

void pushdown(int x) {
  if (t[x].tag) {
    t[x << 1].put(t[x].tag);
    t[x << 1 | 1].put(t[x].tag);
    t[x].tag = 0;
  }
}

void pushup(int x) {
  t[x].mx = max(t[x << 1].mx, t[x << 1 | 1].mx);
}

void modify(int x, int l, int r, int L, int R, int v) {
  if (l >= L && r <= R) {
    t[x].put(v);
  }
  else {
    int mid = (l + r) >> 1;
    pushdown(x);
    if (L <= mid)
      modify(x << 1, l, mid, L, R, v);
    if (R > mid)
      modify(x << 1 | 1, mid + 1, r, L, R, v);
    pushup(x);
  }
}

void build(int x, int l, int r) {
  if (l == r) {
    t[x].mx = -(2 * n - l + 1);
  }
  else {
    int mid = (l + r) >> 1;
    if (l <= mid)
      build(x << 1, l, mid);
    if (r > mid)
      build(x << 1 | 1, mid + 1, r);
    pushup(x);
  }
}

int main() {

  scanf("%d", &n);
  for (int i = 1; i <= 2 * n; i++) {
    scanf("%d", &tp[i]);
    c[tp[i]].push_back(i);
  }
  int cnt = 0;
  build(1, 1, 2 * n);
  for (int i = 1; i <= 2 * n; i++) {
    if (vis[i] == 0) {
      for (auto v : c[tp[i]]) {
        modify(1, 1, 2 * n, 1, v, 2);
      }
      if (t[1].mx > 0) {
        for (auto v : c[tp[i]]) {
          modify(1, 1, 2 * n, 1, v, -2);
        }
        for (auto v : c[tp[i]])
          vis[v] = -1;
      }
      else {
        ++cnt;
        for (auto v : c[tp[i]])
          vis[v] = 1;
      }
    }
  }
  if (cnt * 2 != n) {
    puts("(");
  }
  else {

    for (int i = 1; i <= 2 * n; i++) {
      if (vis[i] == 1)
        putchar('(');
      else
        putchar(')');
    }
  }
}
