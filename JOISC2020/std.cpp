#include <bits/stdc++.h>
using namespace std;

// Fast IO start
namespace io {
const int BUFSIZE = 1 << 20;
char ibuf[BUFSIZE], *is = ibuf, *it = ibuf;
char obuf[BUFSIZE], *os = obuf, *ot = obuf + BUFSIZE - 1;

inline void read_char(char &c) {
  if (is == it) {
    it = (is = ibuf) + fread(ibuf, 1, BUFSIZE, stdin);
    if (is == it)
      *it++ = EOF;
  }
  c = *is++;
}

template <class T>
inline void read_int(T &x) {
  T f = 1;
  char c;
  read_char(c);
  while (!isdigit(c)) {
    if (c == '-') {
      f = -1;
    }
    read_char(c);
  }
  x = 0;
  while (isdigit(c)) {
    x = x * 10 + c - '0';
    read_char(c);
  }
  x *= f;
}

inline void flush() {
  fwrite(obuf, 1, os - obuf, stdout);
  os = obuf;
}

inline void print_char(char c) {
  *os++ = c;
  if (os == ot) {
    flush();
  }
}

template <class T>
inline void print_int(T x) {
  static char q[40];
  if (!x) {
    print_char('0');
  }
  else {
    if (x < 0) {
      print_char('-');
      x = -x;
    }
    int top = 0;
    while (x) {
      q[top++] = x % 10 + '0';
      x /= 10;
    }
    while (top--) {
      print_char(q[top]);
    }
  }
}

struct flusher_t {
  inline ~flusher_t() {
    flush();
  }
} flusher;
} // namespace io

using io::print_char;
using io::print_int;
using io::read_char;
using io::read_int;
// Fast IO end
const int N = 1500005;
mt19937 gen(1145141);
int n, m, clk;
pair<int, int> pts[N], ans[N];
int qt[N], qc[N], tag[N], del[N];
pair<pair<int, int>, int> tp[N];

namespace SegTree {
pair<int, int> tr[N * 4];

void build(int i, int l, int r) {
  if (l == r) {
    tr[i] = make_pair(tp[l].second, l);
    return;
  }
  int mid = (l + r) >> 1;
  build(i << 1, l, mid);
  build(i << 1 | 1, mid + 1, r);
  tr[i] = (pts[tr[i << 1].first].second < pts[tr[i << 1 | 1].first].second ? tr[i << 1] : tr[i << 1 | 1]);
}

pair<int, int> query(int i, int l, int r, int lf, int rg) {
  if (lf <= l && r <= rg)
    return tr[i];
  int mid = (l + r) >> 1;
  if (rg <= mid)
    return query(i << 1, l, mid, lf, rg);
  else if (lf > mid)
    return query(i << 1 | 1, mid + 1, r, lf, rg);
  pair<int, int> r1 = query(i << 1, l, mid, lf, rg), r2 = query(i << 1 | 1, mid + 1, r, lf, rg);
  return ((pts[r1.first].second < pts[r2.first].second) ? r1 : r2);
}

void update(int i, int l, int r, int pos) {
  if (l == r) {
    tr[i].first = 0;
    return;
  }
  int mid = (l + r) >> 1;
  if (pos <= mid)
    update(i << 1, l, mid, pos);
  else
    update(i << 1 | 1, mid + 1, r, pos);
  tr[i] = (pts[tr[i << 1].first].second < pts[tr[i << 1 | 1].first].second ? tr[i << 1] : tr[i << 1 | 1]);
}
} // namespace SegTree

namespace Treap {
struct Node {
  int lson, rson, par, rnd, x, y, tagx, tagy;

  inline void upd(int tx, int ty) {
    x = max(x, tx);
    tagx = max(tagx, tx);
    y = max(y, ty);
    tagy = max(tagy, ty);
  }

  inline void pushdown();
} tr[N];

int tot, root;

inline void Init() {
  tot = root = 0;
  tr[0].lson = tr[0].rson = tr[0].par = tr[0].rnd = tr[0].x = tr[0].y = tr[0].tagx = tr[0].tagy = 0;
}

inline int NewNode(int x, int y) {
  int p = ++tot;
  tr[p].lson = tr[p].rson = tr[p].par = tr[p].tagx = tr[p].tagy = 0;
  tr[p].rnd = gen();
  tr[p].x = x, tr[p].y = y;
  return p;
}

inline void Node::pushdown() {
  if (tagx || tagy) {
    if (lson)
      tr[lson].upd(tagx, tagy);
    if (rson)
      tr[rson].upd(tagx, tagy);
    tagx = tagy = 0;
  }
}

inline pair<int, int> Split_y(int p, int y) {
  if (!p)
    return make_pair(0, 0);
  tr[p].pushdown();
  if (tr[p].y <= y) {
    pair<int, int> q = Split_y(tr[p].lson, y);
    tr[p].lson = q.second;
    if (tr[p].lson)
      tr[tr[p].lson].par = p;
    q.second = p;
    tr[p].par = 0;
    return q;
  }
  else {
    pair<int, int> q = Split_y(tr[p].rson, y);
    tr[p].rson = q.first;
    if (tr[p].rson)
      tr[tr[p].rson].par = p;
    q.first = p;
    tr[p].par = 0;
    return q;
  }
}

inline pair<int, int> Split_x(int p, int x) {
  if (!p)
    return make_pair(0, 0);
  tr[p].pushdown();
  if (tr[p].x > x) {
    pair<int, int> q = Split_x(tr[p].lson, x);
    tr[p].lson = q.second;
    if (tr[p].lson)
      tr[tr[p].lson].par = p;
    q.second = p;
    tr[p].par = 0;
    return q;
  }
  else {
    pair<int, int> q = Split_x(tr[p].rson, x);
    tr[p].rson = q.first;
    if (tr[p].rson)
      tr[tr[p].rson].par = p;
    q.first = p;
    tr[p].par = 0;
    return q;
  }
}

int Merge(int p1, int p2) {
  if (!p1 || !p2)
    return p1 | p2;
  if (tr[p1].rnd < tr[p2].rnd) {
    tr[p1].pushdown();
    tr[p1].rson = Merge(tr[p1].rson, p2);
    if (tr[p1].rson)
      tr[tr[p1].rson].par = p1;
    return p1;
  }
  else {
    tr[p2].pushdown();
    tr[p2].lson = Merge(p1, tr[p2].lson);
    if (tr[p2].lson)
      tr[tr[p2].lson].par = p2;
    return p2;
  }
}

int Insert(int x, int y) {
  int p = NewNode(x, y);
  int a, b, c;
  tie(b, c) = Split_x(root, x);
  tie(a, b) = Split_y(b, y - 1);
  root = Merge(Merge(a, p), Merge(b, c));
  return p;
}

inline pair<int, int> query(int p) {
  int x = tr[p].x, y = tr[p].y;
  while (p) {
    x = max(x, tr[p].tagx);
    y = max(y, tr[p].tagy);
    p = tr[p].par;
  }
  return make_pair(x, y);
}
} // namespace Treap

int nid[N];

void solve(int l, int r) {
  if (l == r)
    return;
  int mid = (l + r) >> 1;
  solve(l, mid);
  solve(mid + 1, r);
  int tot = 0;
  clk++;
  for (int i = l; i <= mid; i++) {
    if (qt[i] == 4) {
      tp[++tot] = make_pair(pts[qc[i]], qc[i]);
      tag[qc[i]] = clk;
      del[qc[i]] = 0;
    }
  }
  if (!tot)
    return;
  sort(tp + 1, tp + 1 + tot);
  SegTree::build(1, 1, tot);
  Treap::Init();
  for (int i = mid + 1; i <= r; i++) {
    if (qt[i] == 4 || (qt[i] == 1 && tag[qc[i]] != clk))
      continue;
    if (qt[i] == 1) {
      ans[i] = (del[qc[i]] ? Treap::query(nid[qc[i]]) : pts[qc[i]]);
    }
    else if (qt[i] == 2) {
      int p, q;
      tie(p, q) = Treap::Split_y(Treap::root, qc[i]);
      if (q)
        Treap::tr[q].upd(n - qc[i], 0);
      Treap::root = Treap::Merge(p, q);
      int xr = lower_bound(tp + 1, tp + 1 + tot, make_pair(make_pair(n - qc[i], n + 5), 0)) - tp - 1;
      if (!xr)
        continue;
      pair<int, int> pr;
      while (true) {
        pr = SegTree::query(1, 1, tot, 1, xr);
        if (pts[pr.first].second > qc[i])
          break;
        nid[pr.first] = Treap::Insert(n - qc[i], pts[pr.first].second);
        del[pr.first] = 1;
        SegTree::update(1, 1, tot, pr.second);
      }
    }
    else if (qt[i] == 3) {
      int p, q;
      tie(p, q) = Treap::Split_x(Treap::root, qc[i]);
      if (p)
        Treap::tr[p].upd(0, n - qc[i]);
      Treap::root = Treap::Merge(p, q);
      int xr = lower_bound(tp + 1, tp + 1 + tot, make_pair(make_pair(qc[i], n + 5), 0)) - tp - 1;
      if (!xr)
        continue;
      pair<int, int> pr;
      while (true) {
        pr = SegTree::query(1, 1, tot, 1, xr);
        if (pts[pr.first].second > n - qc[i])
          break;
        nid[pr.first] = Treap::Insert(pts[pr.first].first, n - qc[i]);
        del[pr.first] = 1;
        SegTree::update(1, 1, tot, pr.second);
      }
    }
  }
  for (int i = l; i <= mid; i++) {
    if (qt[i] == 4 && del[qc[i]]) {
      pts[qc[i]] = Treap::query(nid[qc[i]]);
    }
  }
}

int main() {
  int q, cnt;
  read_int(n);
  read_int(m);
  read_int(q);
  for (int i = 1; i <= m; i++) {
    read_int(pts[i].first);
    read_int(pts[i].second);
    qt[i] = 4;
    qc[i] = i;
  }
  cnt = m;
  for (int i = m + 1; i <= m + q; i++) {
    read_int(qt[i]);
    if (qt[i] <= 3)
      read_int(qc[i]);
    else {
      qc[i] = ++cnt;
      read_int(pts[cnt].first);
      read_int(pts[cnt].second);
    }
  }
  m += q;
  clk = 0;
  pts[0].second = n + 5;
  solve(1, m);
  for (int i = 1; i <= m; i++) {
    if (qt[i] == 1)
      printf("%d %d\n", ans[i].first, ans[i].second);
  }
  return 0;
}
