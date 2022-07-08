#include <bits/stdc++.h>
#include <vector>
using namespace std;
using ll = long long;
const int N = (int)2e5 + 10;

struct SEG {
  struct seg {
    ll sum;
    int tag, len;

    void put(int x) {
      sum += 1ll * x * len;
      tag += x;
    }
  };

  vector<seg> t;

  SEG(int x) {
    t.resize(x * 4 + 10);
  }

  void pushup(int x) {
    t[x].sum = t[x << 1].sum + t[x << 1 | 1].sum;
  }

  void pushdown(int x) {
    if (t[x].tag) {
      t[x << 1].put(t[x].tag);
      t[x << 1 | 1].put(t[x].tag);
      t[x].tag = 0;
    }
  }

  void modify(int x, int l, int r, int L, int R, int v) {
    if (l >= L && r <= R) {
      t[x].put(v);
    }
    else {
      int mid = (l + r) / 2;
      pushdown(x);
      if (L <= mid)
        modify(x << 1, l, mid, L, R, v);
      if (R > mid)
        modify(x << 1 | 1, mid + 1, r, L, R, v);
      pushup(x);
    }
  }

  void query(int x, int l, int r, int L, int R, ll &v) {
    if (l >= L && r <= R) {
      v += t[x].sum;
    }
    else {
      int mid = (l + r) / 2;
      pushdown(x);
      if (L <= mid)
        query(x << 1, l, mid, L, R, v);
      if (R > mid)
        query(x << 1 | 1, mid + 1, r, L, R, v);
      pushup(x);
    }
  }

  void build(int x, int l, int r, vector<int> &a, vector<int> &at) {
    if (l == r) {
      t[x].len = a[at[l]];
      /* cout<<"build "<<l<<' '<<a[at[l]]<<endl; */
    }
    else {
      int mid = (l + r) / 2;
      if (mid >= l)
        build(x << 1, l, mid, a, at);
      if (mid < r)
        build(x << 1 | 1, mid + 1, r, a, at);
      t[x].len = t[x << 1].len + t[x << 1 | 1].len;
    }
  }
};

struct HLD {
  vector<int> fa, sz, dep, son, top, dfn, dis, val, at;
  vector<vector<int>> e;
  int indec;
  int n;
  SEG *seg;

  HLD(int x) {
    n = x;
    indec=0;
    seg=NULL;
    fa = sz = dep = son = top = dfn = dis = val = at = vector<int>(x + 5);
    e = vector<vector<int>>(x + 5);
  }

  void add(int x, int y) {
    e[x].push_back(y);
  }

  void dfs1(int x, int f) {
    fa[x] = f, sz[x] = 1, dep[x] = dep[f] + 1, son[x] = 0;
    for (int &v : e[x]) {
      if (v != f) {
        dfs1(v, x);
        if (sz[v] > sz[son[x]])
          son[x] = v;
        sz[x] += sz[v];
      }
    }
  }

  void dfs2(int x, int tp) {
    top[x] = tp;
    dfn[x] = ++indec;
    at[indec] = x;
    if (son[x])
      dfs2(son[x], tp);
    for (int &v : e[x]) {
      if (v == fa[x] || v == son[x])
        continue;
      dfs2(v, v);
    }
  }

  ll query(int x) {
    ll ans = 0;
    while (top[x] != 1) {
      seg->query(1, 1, n, dfn[top[x]], dfn[x], ans);
      x = fa[top[x]];
    }
    seg->query(1, 1, n, dfn[1], dfn[x], ans);
    return ans;
  }

  void modify(int x) {
    while (top[x] != 1) {
      seg->modify(1, 1, n, dfn[top[x]], dfn[x], 1);
      x = fa[top[x]];
    }
    seg->modify(1, 1, n, dfn[1], dfn[x], 1);
  }
};

struct SAM {
  int last = 1, tot = 1;
  int ch[N*2][26], fa[N*2], len[N*2], pos[N];
  SAM() = default;

  void extend(int c, int p) {
    int x = last, cur = last = ++tot;
    len[cur] = len[x] + 1, pos[p] = cur;
    for (; x and !ch[x][c]; x = fa[x])
      ch[x][c] = cur;
    if (!x) {
      fa[cur] = 1;
      return;
    }
    int y = ch[x][c];
    if (len[y] == len[x] + 1) {
      fa[cur] = y;
      return;
    }
    int clone = ++tot;
    copy(ch[y], ch[y] + 26, ch[clone]);
    fa[clone] = fa[y], len[clone] = len[x] + 1;
    fa[cur] = fa[y] = clone;
    for (; ch[x][c] == y; x = fa[x])
      ch[x][c] = clone;
  }

  HLD gen() {
    HLD hld(tot);
    for (int i = 1; i <= tot; i++) {
      hld.add(fa[i], i);
      hld.val[i] = len[i] - len[fa[i]];
    }

    return hld;
  }
} sam;

int main() {
  freopen("str.in","r",stdin);
  freopen("str.out","w",stdout);
  static char str[N];
  scanf("%s", str + 1);
  int n = (int)strlen(str + 1);
  for (int i = n; i >= 1; --i)
    sam.extend(str[i] - 'a', n - i + 1);
  /* for (int i = 1; i <= n; i++) { */
  /*   cout << sam.pos[i] << endl; */
  /* } */

  static vector<tuple<int, int, int>> que[N];
  int Q;
  scanf("%d", &Q);
  for (int i = 1; i <= Q; i++) {
    int x, l, r;
    scanf("%d%d%d", &x, &l, &r);
    l = n - l + 1, r = n - r + 1, x = n - x + 1;
    swap(l, r);
    que[l - 1].emplace_back(sam.pos[x], -1, i);
    que[r].emplace_back(sam.pos[x], 1, i);
  }

  HLD hld = sam.gen();
  hld.dfs1(1, 0);
  hld.dfs2(1, 1);
  SEG seg(sam.tot);
  hld.seg = &seg;

  seg.build(1, 1, sam.tot, hld.val, hld.at);
  static ll ans[N];
  for (int i = 1; i <= n; i++) {
    hld.modify(sam.pos[i]);
    hld.query(6);
    for (const auto &[x, tp, id] : que[i]) {
      ll res = hld.query(x);
      ans[id] += 1ll * tp * res;
    }
  }
  for (int i = 1; i <= Q; i++) {
    printf("%lld\n", ans[i]);
  }
}
