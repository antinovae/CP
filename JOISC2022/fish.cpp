#include <bits/stdc++.h>
using namespace std;

#ifdef CLANGD
const int maxn = 11;
#else
const int maxn = 100001;
#endif
using ll = long long;

struct bar {
  ll lim, sum;
};

struct node {
  ll sum;
  int cnt;
};

using bars = vector<bar>;
using nodes = vector<node>;

bars merge_bar(const bars &a, const bars &b, ll seg_sum) {
  bars c = a;
  if (a.back().sum == seg_sum) {
    for (auto v : b) {
      if (seg_sum + c.back().lim < v.lim) {
        cout << "ins " << v.lim << ' ' << v.sum << " " << seg_sum << endl;
        c.push_back({v.lim - seg_sum, seg_sum + v.sum});
      }
      else {
        c.back().sum = seg_sum + v.sum;
      }
    }
  }
  return c;
}

void walk(nodes a, nodes b, bars ar, bars br, int tar, nodes &app) {
  auto br_it = br.begin();
  auto ar_it = ar.begin();
  auto b_it = b.begin();
  auto a_it = a.begin();
  ll a_sum = a_it->sum, b_sum = 0;
  int cnt = a_it->cnt;
  cout << "walk " << endl;
  a_it++;
  do {
    while (br_it != br.end() && a_sum + b_sum >= br_it->lim) {
      while (b_it != b.end() && b_it->sum <= br_it->sum) {
        b_sum = b_it->sum;
        cnt += b_it->cnt;
        ++b_it;
      }
      ++br_it;
    }
    while (ar_it != ar.end() && a_sum + b_sum >= ar_it->lim) {
      while (a_it != a.end() && a_it->sum <= ar_it->sum) {
        a_sum = a_it->sum;
        cnt += a_it->cnt;
        ++a_it;
      }
      ++ar_it;
    }
    cout << a_sum << " " << b_sum << " " << cnt << endl;
    if (tar == 1 && br_it == br.end()) {
      app.push_back({a_sum + b_sum, cnt});
    }
    else if (tar == 0 && ar_it == ar.end()) {
      app.push_back({a_sum + b_sum, cnt});
    }
  } while (a_it != a.end());
}

struct seg {
  bars pre_bar, suf_bar;
  nodes pre_node, suf_node;
  node full_node;
  ll seg_sum;

  seg() = default;

  seg(const seg &a, const seg &b) {
    seg_sum = a.seg_sum + b.seg_sum;
    pre_bar = merge_bar(a.pre_bar, b.pre_bar, a.seg_sum);
    suf_bar = merge_bar(b.suf_bar, a.suf_bar, b.seg_sum);

    suf_node = b.suf_node;
    walk(a.suf_node, b.pre_node, a.suf_bar, b.pre_bar, 0, suf_node);
    walk(b.pre_node, a.suf_node, b.pre_bar, a.suf_bar, 1, suf_node);

    pre_node = a.pre_node;
    walk(b.pre_node, a.suf_node, b.pre_bar, a.suf_bar, 0, pre_node);
    walk(a.suf_node, b.pre_node, a.suf_bar, b.pre_bar, 1, pre_node);
  }

  seg(ll x) {
    seg_sum = x;
    full_node = {x, 1};
    suf_bar.push_back({x, x});
    pre_node.push_back({x, 1});
    suf_node.push_back({x, 1});
  }

  void pr() {
    cout << "seg sum: " << seg_sum << endl;
    cout << "pre bar: ";
    for (auto [x, y] : pre_bar)
      cout << x << " " << y << "  ";
    cout << endl;
    cout << "suf bar: ";
    for (auto [x, y] : suf_bar)
      cout << x << " " << y << "  ";
    cout << endl;
    cout << "pre node: ";
    for (auto [x, y] : pre_node)
      cout << x << " " << y << "  ";
    cout << endl;
    cout << "suf node: ";
    for (auto [x, y] : suf_node)
      cout << x << " " << y << "  ";
    cout << endl;
    cout << endl;
  }
} t[maxn << 2];

void modify(int x, int l, int r, int pos, ll v) {
  if (l == r) {
    t[x] = seg(v);
  }
  else {
    int mid = (l + r) / 2;
    if (pos <= mid)
      modify(x << 1, l, mid, pos, v);
    else
      modify(x << 1 | 1, mid + 1, r, pos, v);
    t[x] = seg(t[x << 1], t[x << 1 | 1]);
  }
}

seg query(int x, int l, int r, int L, int R) {
  if (l >= L && r <= R) {
    return t[x];
  }
  else {
    int mid = (l + r) / 2;
    if (L <= mid && R > mid) {
      return {query(x << 1, l, mid, L, R), query(x << 1 | 1, mid + 1, r, L, R)};
    }
    else if (L <= mid)
      return query(x << 1, l, mid, L, R);
    else if (R > mid)
      return query(x << 1 | 1, mid + 1, r, L, R);
    else
      assert(0);
  }
}

int a[maxn];

void build(int x, int l, int r) {
  if (l == r) {
    t[x] = seg(a[l]);
  }
  else {

    int mid = (l + r) / 2;
    if (l <= mid)
      build(x << 1, l, mid);
    if (r > mid)
      build(x << 1 | 1, mid + 1, r);
    t[x] = seg(t[x << 1], t[x << 1 | 1]);
  }
}

void pr(int x, int l, int r) {
  cout << "print: " << x << " " << l << " " << r << endl;
  t[x].pr();
  if (l == r) {
    return;
  }
  else {

    int mid = (l + r) / 2;
    if (l <= mid)
      pr(x << 1, l, mid);
    if (r > mid)
      pr(x << 1 | 1, mid + 1, r);
  }
}

int main() {
  int n, Q;
  scanf("%d%d", &n, &Q);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
  }
  build(1, 1, n);
  pr(1, 1, n);
  /* for (int i = 1; i <= Q; i++) { */
  /*   int tp, x, y; */
  /*   scanf("%d%d%d", &tp, &x, &y); */
  /*   if (tp == 1) { */
  /*     a[x] = y; */
  /*     modify(1, 1, n, x, y); */
  /*   } */
  /*   else { */
  /*     auto res = query(1, 1, n, x, y); */
  /*     if (res.seg_sum == res.pre_node.back().sum) { */
  /*       printf("%d\n", res.pre_node.back().cnt); */
  /*     } */
  /*   } */
  /* } */
}
