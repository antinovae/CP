#include <bits/stdc++.h>
using namespace std;
std::stringstream out;
/* #define cout out */
#define int long long
int read() {
  int w = 1, c = 0;
  int ch = getchar();
  for (; !isdigit(ch); ch = getchar())
    if (ch == '-')
      w = -1;
  for (; isdigit(ch); ch = getchar())
    c = (c << 1) + (c << 3) + (ch ^ 48);
  return w * c;
}
struct info {
  int val, tag, mx;
  void up(info a) { mx = max(mx, a.mx); }
  void mdf(int a) {
    val += a;
    tag += a;
    mx += a;
  }
};
const int maxn = 1000001;
mt19937 rnd(0);
struct BST {
  int rt, indec;

  struct node;
  static node t[maxn];

  struct node {
    info a, b;
    unsigned int pri;
    int ch[2];
    int key() { return a.val - b.val; }
    void init(int x, int y) {
      a.val = a.mx = x, b.val = b.mx = y;
      pri = rnd();
    }
    void pushup() {
      a.mx = a.val;
      b.mx = b.val;
      if (ch[0])
        a.up(t[ch[0]].a), b.up(t[ch[0]].b);
      if (ch[1])
        a.up(t[ch[1]].a), b.up(t[ch[1]].b);
    }
    void pushdown() {
      if (ch[0])
        t[ch[0]].a.mdf(a.tag), t[ch[0]].b.mdf(b.tag);
      if (ch[1])
        t[ch[1]].a.mdf(a.tag), t[ch[1]].b.mdf(b.tag);
      a.tag = b.tag = 0;
    }
  };
#define ls t[x].ch[0]
#define rs t[x].ch[1]
  int new_node(int x, int y) {
    ++indec;
    t[indec].init(x, y);
    return indec;
  }

  void split(int x, int lim, int &a, int &b) {
    if (!x) {
      a = b = 0;
    } else {
      t[x].pushdown();
      if (t[x].key() <= lim)
        a = x, split(rs, lim, rs, b);
      else
        b = x, split(ls, lim, a, ls);
      t[x].pushup();
    }
  }
  int merge(int x, int y) {
    if (!x || !y)
      return x | y;
    else {
      if (t[x].pri < t[y].pri) {
        t[x].pushdown();
        t[x].ch[1] = merge(t[x].ch[1], y);
        t[x].pushup();
        return x;
      } else {
        t[y].pushdown();
        t[y].ch[0] = merge(x, t[y].ch[0]);
        t[y].pushup();
        return y;
      }
    }
  }
  void insert(int vx, int vy) {
    int id = new_node(vx, vy), x, y;
    split(rt, vx - vy, x, y);
    rt = merge(merge(x, id), y);
  }
  void modify_x(int v) { t[rt].a.mdf(v); }
  void modify_y(int v) { t[rt].b.mdf(v); }
  void modify_xy(int l, int r, int v) {
    int x, y, z, w;
    split(rt, l - 1, x, y);
    split(y, r, z, w);
    if (z)
      t[z].a.mdf(v * 2), t[z].b.mdf(v * 2);
    vector<pair<int, int>> ins;
    if (x) {
      int vx = t[x].a.mx + v * 2;
      int vy = t[x].a.mx - l + v * 2;
      ins.push_back({vx, vy});
      t[x].a.mdf(v), t[x].b.mdf(v);
    }
    if (w) {
      int vx = t[w].b.mx + r + v * 2;
      int vy = t[w].b.mx + v * 2;
      ins.push_back({vx, vy});
      t[w].a.mdf(v), t[w].b.mdf(v);
    }
    rt = merge(x, merge(z, w));
    for (auto [x, y] : ins)
      insert(x, y);
  }
  int ans() { return t[rt].a.mx; }
} T;
BST::node BST::t[maxn];
struct event {
  int x, tp;
  bool c;
};
vector<event> t;
signed main() {
  freopen("segment.in", "r", stdin);
  freopen("segment.out", "w", stdout);
  int n = read(), m = read(), C = read();
  for (int i = 1; i <= n; i++) {
    int x = read(), y = read();
    if (x != y) {
      t.push_back({x, 0, true});
      t.push_back({y, 0, false});
    }
  }
  for (int i = 1; i <= m; i++) {
    int x = read(), y = read();
    if (x != y) {
      t.push_back({x, 1, true});
      t.push_back({y, 1, false});
    }
  }
  sort(t.begin(), t.end(), [&](event a, event b) {
    if (a.x != b.x)
      return (a.x < b.x);
    else
      return (a.c < b.c);
    return ax != bx   ? ax < bx
           : ay != by ? by < by
           : az != bz ? az < bz
                      : aa < bb;
  });
  assert(!t.empty());
  T.insert(0, 0);
  bool c0 = false, c1 = false;
  for (int i = 0; i < t.size() - 1; i++) {
    while (i < t.size() - 1 && t[i].x == t[i + 1].x) {
      /* cout<<i<<" "<<t[i].x<<" "<<t.size()-1<<endl; */
      if (t[i].tp == 0)
        c0 = t[i].c;
      else
        c1 = t[i].c;
      ++i;
    }
    if (i == t.size() - 1)
      break;
    if (t[i].tp == 0)
      c0 = t[i].c;
    else
      c1 = t[i].c;
    int len = t[i + 1].x - t[i].x;
    if (c0 && c1) {
      T.modify_xy(-C, C, len);
    } else if (c0) {
      T.modify_x(len);
    } else if (c1) {
      T.modify_y(len);
    }
  }
  printf("%lld\n", T.ans());
  return 0;
}
