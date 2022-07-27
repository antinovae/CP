#include <algorithm>
#include <bits/stdc++.h>
#include <cstdio>
#include <functional>
using namespace std;
const int N = 1001, INF = 1e9;
int L;
int n;
int l[N], r[N];
vector<pair<int, int>> mnl[N];

struct seg1 {
  struct node {
    pair<pair<int, int>, int> mn;
    int tag;

    void add(int v) {
      mn.first.first += v;
      tag += v;
    };

    node() {
      mn = {{INF, INF}, INF};
      tag = 0;
    }
  } t[N * 4];

  void pr(int x, int l, int r) {
    cout << x << ' ' << l << ' ' << r << " " << t[x].mn.first.first << " " << t[x].mn.first.second << endl;
    if (l == r) {
    }
    else {

      int mid = (l + r) / 2;
      if (l <= mid)
        pr(x << 1, l, mid);
      if (mid < r)
        pr(x << 1 | 1, mid + 1, r);
    }
  }

  void pushup(int x) {
    /* cout<<"pushup "<<x<<endl; */
    t[x].mn = min(t[x << 1].mn, t[x << 1 | 1].mn);
    /* if(x==4){ */
    /*   cout<<"check    "<<x<<" "<<t[x].mn.first.first<<' '<<t[x].mn.first.second<<endl; */
    /*   int v=x<<1; */
    /*   cout<<"check    "<<v<<" "<<t[v].mn.first.first<<' '<<t[v].mn.first.second<<endl; */
    /*    v=x<<1|1; */
    /*   cout<<"check    "<<v<<" "<<t[v].mn.first.first<<' '<<t[v].mn.first.second<<endl; */
    /* } */
  }

  void pushdown(int x) {
    if (t[x].tag != 0) {
      t[x << 1].add(t[x].tag);
      t[x << 1 | 1].add(t[x].tag);
      t[x].tag = 0;
    }
  }

  void modify(int x, int l, int r, int L, int R, int v) {
    if (l >= L & r <= R) {
      t[x].add(v);
    }
    else {
      pushdown(x);
      int mid = (l + r) / 2;
      if (L <= mid)
        modify(x << 1, l, mid, L, R, v);
      if (R > mid)
        modify(x << 1 | 1, mid + 1, r, L, R, v);
      pushup(x);
    }
  }

  void insert(int x, int l, int r, int pos, pair<int, int> v) {
    if (l == r) {
      cout << "set	  " << x << " " << l << " " << r << ' ' << v.first << ' ' << v.second << endl;
      t[x].mn = {v, pos};
    }
    else {
      int mid = (l + r) / 2;
      pushdown(x);
      if (pos <= mid)
        insert(x << 1, l, mid, pos, v);
      else
        insert(x << 1 | 1, mid + 1, r, pos, v);
      pushup(x);
    }
  }
} T1;

struct seg2 {
  struct node {
    pair<int, int> mn;
  } t[N * 4];

  void pushup(int x) {
    t[x].mn = min(t[x << 1].mn, t[x << 1 | 1].mn);
  }

  void pr(int x, int l, int r) {
    cout << "seg2 " << x << ' ' << l << ' ' << r << " min " << t[x].mn.first << " " << t[x].mn.second << endl;
    if (l == r) {
    }
    else {

      int mid = (l + r) / 2;
      if (l <= mid)
        pr(x << 1, l, mid);
      if (mid < r)
        pr(x << 1 | 1, mid + 1, r);
    }
  }

  void modify(int x, int l, int r, int p) {
    if (l == r) {
      if (mnl[l].size() > 1)
        mnl[l].pop_back();
      t[x].mn = mnl[l].back();
      cout << "modify! " << l << " " << mnl[l].back().first << endl;
    }
    else {
      int mid = (l + r) / 2;
      if (p <= mid)
        modify(x << 1, l, mid, p);
      else
        modify(x << 1 | 1, mid + 1, r, p);
      pushup(x);
    }
  }

  void query(int x, int l, int r, int L, int R, pair<int, int> &mn) {
    if (l >= L & r <= R) {
      mn = min(mn, t[x].mn);
    }
    else {
      int mid = (l + r) / 2;
      if (L <= mid)
        query(x << 1, l, mid, L, R, mn);
      if (R > mid)
        query(x << 1 | 1, mid + 1, r, L, R, mn);
    }
  }

  void build(int x, int l, int r) {
    if (l == r) {
      if (mnl[l].empty()) {
        t[x].mn = {INF, INF};
      }
      else
        t[x].mn = mnl[l].back();
      cout << "seg2 " << x << " " << l << " " << r << ' ' << t[x].mn.first << " " << t[x].mn.second << endl;
    }
    else {

      int mid = (l + r) / 2;
      if (l <= mid)
        build(x << 1, l, mid);
      if (mid < r)
        build(x << 1 | 1, mid + 1, r);
      pushup(x);
    }
  }
} T2;

struct bit {
  array<int, N> c;
  int n;

  void modify(int x, int v) {
    for (; x <= n; x += x & -x)
      c[x] += v;
  }

  int que(int x, int res = 0) {
    for (; x; x -= x & (-x))
      res += c[x];
    return res;
  }

  int query(int l, int r) {
    return que(r) - que(l);
  }
} B;

set<int> exist;
vector<pair<int, int>> lnode, rnode;
vector<int> vals;
set<int> online, offline;
int real_id[N];

void insert(int x, int tp = 1) {
  cout<<"insert "<<x<<" "<<tp<<endl;
  int val = B.query(l[x], r[x]);
  cout << "insert " << x << " range " << l[x] << " " << r[x] << " val  " << val << endl;
  T1.insert(1, 1, n, x, {val, real_id[x]});
  if (tp)
    T2.modify(1, 0, L, l[x]);
  offline.erase(x);
  online.insert(x);
}

void query() {
  // query
  cout << endl
       << " " << endl
       << endl;
  auto [val, x] = T1.t[1].mn;
  cout << "ans: " << val.second << endl;
  for (auto v : online)
    cout << v << " ";
  cout << endl;
  T1.pr(1, 1, n);
  cout << "queryd "
       << "val: " << val.first << " x: " << x << " lx: " << l[x] << " rx " << r[x] << endl;
  // remove seg
  cout << "exist: ";
  for (auto v : exist) {
    cout << v << " ";
  }
  cout << endl;
  while (!exist.empty()) {
    auto it = exist.lower_bound(l[x]);
    if (it == exist.end())
      break;
    int v = *it;
    cout << "v: " << v << " " << endl;
    if (v < r[x]) {
      exist.erase(it);
      cout << "erase! " << v << endl;
      auto cl = lower_bound(rnode.begin(), rnode.end(), make_pair(v + 1, 0));
      auto cr = prev(upper_bound(lnode.begin(), lnode.end(), make_pair(v, INF)));
      cout << "range " << cl->second << " " << cr->second - 1 << " ";
      cout << vals[v + 1] - vals[v] << endl;
      T1.modify(1, 1, n, cl->second, cr->second - 1, -vals[v + 1] + vals[v]);
    }
    else
      break;
  }
  // remove inter
  auto it = online.find(x);
  int lb = (it != online.begin()) ? *prev(it) : -1;
  int rb = (next(it) != online.end()) ? *next(it) : INF;
  online.erase(it);
  T1.insert(1, 1, n, x, {INF, INF});
  cout << "bounds " << lb << " " << rb << endl;
  int cnt = 0;
  while (!offline.empty()) {
    if (cnt > 10)
      assert(0);
    ++cnt;
    pair<int, int> res = {INF, INF};
    cout << "query " << lb + 1 << " " << L << endl;
    T2.query(1, 0, L, lb + 1, L, res);
    cout << res.first << " " << res.second << endl;
    if (res.first < rb) {
      insert(res.second);
      T2.pr(1, 0, L);
    }
    else break;
  }
}

void setperm(int a[], int p[], int l, int r) {
  static int tmp[N];
  for (int i = l; i < r; i++)
    tmp[i] = a[i];
  for (int i = l; i < r; i++)
    a[i] = tmp[p[i]];
}

int main() {
  static int id[N];
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", &l[i], &r[i]);
    vals.push_back(l[i]);
    vals.push_back(r[i]);
    id[i] = i;
    real_id[i] = i;
  }
  sort(vals.begin(), vals.end());
  vals.erase(unique(vals.begin(), vals.end()), vals.end());
  L = (int)(vals.size() + 1), B.n = L;
  for (int i = 1; i <= n; i++) {
    l[i] = (int)(lower_bound(vals.begin(), vals.end(), l[i]) - vals.begin());
    r[i] = (int)(lower_bound(vals.begin(), vals.end(), r[i]) - vals.begin());
  }
  for (auto [x, y] : lnode) {
    cout << x << " " << y << endl;
  }
  for (auto [x, y] : rnode) {
    cout << x << " " << y << endl;
  }

  for (int i = 1; i <= n; i++) {
    cout << l[i] << " " << r[i] << " " << real_id[i] << endl;
  }
  sort(id + 1, id + 1 + n, [&](int a, int b) {
      if(l[a] != l[b])return l[a] < l[b];
      else return r[a] > r[b]; });
  setperm(l, id, 1, n + 1);
  setperm(r, id, 1, n + 1);
  setperm(real_id, id, 1, n + 1);

  for (int i = 1; i <= n; i++) {
    lnode.emplace_back(l[i], i);
    rnode.emplace_back(r[i], i);
  }
  sort(lnode.begin(), lnode.end());
  sort(rnode.begin(), rnode.end());

  for (int i = 1; i <= n; i++) {
    cout << id[i] << " " << l[i] << " " << r[i] << " " << real_id[i] << endl;
  }

  for (int i = 0; i < vals.size() - 1; i++) {
    exist.insert(i);
    B.modify(i + 1, vals[i + 1] - vals[i]);
  }
  int mnr = INF;
  for (int i = n; i >= 1; i--) {
    if (r[i] < mnr) {
      mnr = min(mnr, r[i]);
      online.insert(i);
      cout << "online " << i << endl;
      insert(i, 0);
    }
    else {
      mnl[l[i]].emplace_back(r[i], i);
      cout << "offline " << i << endl;
      offline.insert(i);
    }
  }
  for (int i = 0; i < vals.size(); i++) {
    mnl[i].emplace_back(INF, INF);
    sort(mnl[i].begin(), mnl[i].end(), greater<>());
    for (auto [x, y] : mnl[i])
      cout << x << " " << y << "  ";
    cout << endl;
  }
  T2.build(1, 0, L);
  for (int i = 1; i <= n; i++) {
    cout << "round " << i << endl;
    query();
  }
}
