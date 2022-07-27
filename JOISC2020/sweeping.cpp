#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
const int INF = (int)1e9 + 5;
mt19937 rnd(114514);

struct node {
  node *ls, *rs, *fa;
  ull pri;

  ll key() {
    return 1ll * x * INF + (INF - 1 - y);
  }

  int x, tag_x, y, tag_y;
  int rx, ry;

  node(int px, int py) {
    x = px, y = py;
    tag_x = tag_y = -1;
    pri = rnd();
  }

  void pushup() {
    if (rs != nullptr) {
      rx = rs->rx, ry = rs->ry;
    }
    else
      rx = x, ry = y;
  }

  void put_x(int nx) {
    x = nx;
    rx = nx;
  };

  void put_y(int ny) {
    y = ny;
    ry = ny;
  };

  void pushdown() {
    if (tag_x != -1) {
      ls->put_x(tag_x), rs->put_x(tag_x);
      tag_x = -1;
    }
    if (tag_y != -1) {
      ls->put_y(tag_y), rs->put_y(tag_y);
      tag_y = -1;
    }
  }
};

node *new_node(int x, int y) {
  return new node(x, y);
}

node *merge(node *x, node *y) {
  if (x == nullptr)
    return y;
  if (y == nullptr)
    return x;
  if (x->pri < y->pri) {
    x->rs = merge(x->rs, y);
    if (x->rs)
      x->rs->fa = x;
    x->pushup();
    return x;
  }
  else {
    y->ls = merge(x, y->ls);
    if (y->ls)
      y->ls->fa = y;
    y->pushup();
    return y;
  }
}

void split(node *x, ll lim, node *&a, node *&b) {
  if (x == nullptr) {
    a = b = nullptr;
  }
  else {
    x->pushdown();
    if (x->key() <= lim) {
      a = x;
      split(x->rs, lim, x->rs, b);
      if (x->rs)
        x->rs->fa = x;
    }
    else {
      b = x;
      split(x->ls, lim, a, x->ls);
      if (x->ls)
        x->ls->fa = x;
    }
    x->pushup();
  }
}

void split_x(node *x, int lim, node *&a, node *&b) {
  if (x == nullptr) {
    a = b = nullptr;
  }
  else {
    x->pushdown();
    if (x->x <= lim) {
      a = x;
      split(x->rs, lim, x->rs, b);
      if (x->rs)
        x->rs->fa = x;
    }
    else {
      b = x;
      split(x->ls, lim, a, x->ls);
      if (x->ls)
        x->ls->fa = x;
    }
    x->pushup();
  }
}

void split_y(node *x, int lim, node *a, node *b) {
  if (x == nullptr) {
    a = b = nullptr;
  }
  else {
    x->pushdown();
    if (x->y >= lim) {
      a = x;
      split(x->rs, lim, x->rs, b);
      if (x->rs)
        x->rs->fa = x;
    }
    else {
      b = x;
      split(x->ls, lim, a, x->ls);
      if (x->ls)
        x->ls->fa = x;
    }
    x->pushup();
  }
}

node *rt;

void modify(int x, int y, int tp, int val) {
  node *l = nullptr, *r = nullptr, *mid = nullptr, *l_mid = nullptr;
  split_x(rt, x, l_mid, r);
  split_y(l_mid, y, l, mid);
  if (tp == 0)
    mid->put_x(val);
  else
    mid->put_y(val);
  rt = merge(merge(l, mid), r);
}

void insert(int x, int y) {
  node *cur = new_node(x, y);
  node *l = nullptr, *r = nullptr;
  split(rt, cur->key(), l, r);
  rt = merge(l, merge(cur, r));
}

pair<int, int> query(node *p) {
  int x = p->x, y = p->y;
  while (p->fa) {
    p = p->fa;
    if (p->tag_x != -1)
      x = p->tag_x;
    if (p->tag_y != -1)
      y = p->tag_y;
  }
  return {x, y};
}
const int N=1001;
pair<int, int> tr[N * 4];
void pushup(int x){
  tr[x] = (pts[tr[x << 1].first].second < pts[tr[x << 1 | 1].first].second ? tr[x << 1] : tr[x << 1 | 1]);
}
void build(int x, int l, int r) {
  if (l == r) {
    tr[x] = make_pair(tp[l].second, l);
    return;
  }
  int mid = (l + r) >> 1;
  build(x << 1, l, mid);
  build(x << 1 | 1, mid + 1, r);
  pushup(x);
}

pair<int, int> query(int x, int l, int r, int L, int R) {
  if (L <= l && r <= R)
    return t[x];
  int mid = (l + r) >> 1;
  if (R <= mid)
    return query(x << 1, l, mid, L, R);
  else if (L > mid)
    return query(x << 1 | 1, mid + 1, r, L, R);
  pair<int, int> r1 = query(x << 1, l, mid, L, R), r2 = query(x << 1 | 1, mid + 1, r, L, R);
  return ((pts[r1.first].second < pts[r2.first].second) ? r1 : r2);
}

void update(int x, int l, int r, int pos) {
  if (l == r) {
    t[x].first = 0;
    return;
  }
  int mid = (l + r) >> 1;
  if (pos <= mid)
    update(x << 1, l, mid, pos);
  else
    update(x << 1 | 1, mid + 1, r, pos);
  tr[i] = (pts[tr[i << 1].first].second < pts[tr[i << 1 | 1].first].second ? tr[i << 1] : tr[i << 1 | 1]);
}

void divide(int l, int r) {
  if (l > r)
    return;
  int mid = (l + r) / 2;
  divide(l, mid);
  for (int i = l; i <= mid; i++) {
  }
}

int main() {
  int n, m, Q;
  scanf("%d%d%d", &n, &m, &Q);
}
