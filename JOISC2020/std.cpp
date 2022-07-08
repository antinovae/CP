
#include <bits/stdc++.h>
#define UP4D up(Lmax, r[i].l), down(Rmin, r[i].r), up(Tmax, r[i].t), down(Bmin, r[i].b)
#define fprintf(...) ((void)0)
#define fputs(...) ((void)0)
using std::cin;
using std::cout;

typedef std::pair<int, int> pr;
const int N = 400054;

struct rect {
  int l, r, t, b;

  rect *read() { return cin >> l >> t >> r >> b, this; }

  inline bool contain(int x, int y) { return l <= x && x <= r && t <= y && y <= b; }
} r[N];

int n, K, cX, cY;
int X[N], Y[N];

inline void up(int &x, const int y) { x < y ? x = y : 0; }

inline void down(int &x, const int y) { x > y ? x = y : 0; }

namespace mng {
int cov[N], remain;
std::set<pr> s;

inline void reset() { remain = n, memset(cov, 0, n << 2), s.clear(); }

inline bool insert(int x, int y) {
  if (s.emplace(x, y).second) {
    for (int i = 0; i < n; ++i)
      if (r[i].contain(x, y))
        remain -= !cov[i]++;
    return true;
  }
  return false;
}

inline bool erase(int x, int y) {
  if (s.erase(pr(x, y))) {
    for (int i = 0; i < n; ++i)
      if (r[i].contain(x, y))
        remain += !--cov[i];
    return true;
  }
  return false;
}

inline bool judge() {
  if (remain || (int)s.size() > K)
    return false;
  fputs("Found a solution !\n", stderr);
  for (const pr &e : s)
    cout << X[e.first] << ' ' << Y[e.second] << '\n';
  for (int i = K - (int)s.size(); i; --i)
    cout << "1 1\n";
  return true;
}
} // namespace mng

namespace DC {
int F[N];
pr D[N];

int Discretize(int n) {
  int i, cnt = 0;
  std::sort(D, D + n);
  for (i = 0; i < n; ++i)
    F[D[i].second] = (i && D[i].first == D[i - 1].first ? cnt - 1 : (D[cnt] = D[i], cnt++));
  return cnt;
}
} // namespace DC

namespace simple {
int Lmax, Rmin, Tmax, Bmin;
int o[N];

bool LR1D() {
  int i, j;
  std::iota(o, o + n, 0), std::sort(o, o + n, [](const int x, const int y) { return r[x].r < r[y].r; });
  for (i = 0; i < n; ++i)
    if (!mng::cov[j = o[i]])
      mng::insert(r[j].r, Tmax);
  return mng::judge();
}

bool TB1D() {
  int i, j;
  std::iota(o, o + n, 0), std::sort(o, o + n, [](const int x, const int y) { return r[x].b < r[y].b; });
  for (i = 0; i < n; ++i)
    if (!mng::cov[j = o[i]])
      mng::insert(Lmax, r[j].b);
  return mng::judge();
}

bool main() {
  fputs("Step 1 : simple ...\n", stderr);
  Lmax = -1, Rmin = INT_MAX, Tmax = -1, Bmin = INT_MAX;
  for (int i = 0; i < n; ++i)
    UP4D;
  if (mng::reset(), Tmax <= Bmin && LR1D())
    return true;
  return mng::reset(), Lmax <= Rmin && TB1D();
}
} // namespace simple

namespace corner {
bool dfs(int dep) {
  int i, Lmax = -1, Rmin = INT_MAX, Tmax = -1, Bmin = INT_MAX;
  if (mng::judge())
    return true;
  for (i = 0; i < n; ++i)
    if (!mng::cov[i])
      UP4D;
  if (!dep) {
    if (Lmax <= Rmin && Tmax <= Bmin)
      return mng::insert(Lmax, Tmax), assert(mng::judge()), true;
    return false;
  }
  if (mng::insert(Lmax, Tmax)) {
    if (dfs(dep - 1))
      return true;
    mng::erase(Lmax, Tmax);
  }
  if (mng::insert(Lmax, Bmin)) {
    if (dfs(dep - 1))
      return true;
    mng::erase(Lmax, Bmin);
  }
  if (mng::insert(Rmin, Tmax)) {
    if (dfs(dep - 1))
      return true;
    mng::erase(Rmin, Tmax);
  }
  if (mng::insert(Rmin, Bmin)) {
    if (dfs(dep - 1))
      return true;
    mng::erase(Rmin, Bmin);
  }
  return false;
}

bool main() {
  fputs("Step 2 : corner ...\n", stderr);
  return mng::reset(), dfs(K - 1);
}
} // namespace corner

namespace Graph {
#define ad(x) ((((x)-1) ^ 1) + 1)
const int N = 888888, M = 3333333;

struct edge {
  int u, v;

  edge(int u0 = 0, int v0 = 0) : u(u0), v(v0) {}
} e[M];

int V, E = 0, V1;
int first[N], next[N];
int cnt = 0, id[N], low[N], topo[N];
int stc = 0, stack[N], top[N];
bool in_stack[N];
int col[N], conflict[N];

inline void addedge(int u, int v) { e[++E] = edge(u, v), next[E] = first[u], first[u] = E; }

inline void implies(int u, int v) { addedge(u, v), addedge(ad(v), ad(u)); }

inline void must(int x) { addedge(ad(x), x); }

void dfs(int x) {
  int i, y;
  id[x] = low[x] = ++cnt, in_stack[x] = true, stack[stc++] = x;
  for (i = first[x]; i; i = next[i])
    if (!id[y = e[i].v])
      dfs(y), down(low[x], low[y]);
    else if (in_stack[y])
      down(low[x], id[y]);
  if (id[x] == low[x]) {
    for (y = 0; y != x; y = stack[--stc], in_stack[y] = false, top[y] = x)
      ;
    topo[V1++] = x;
  }
}

inline bool _2_SAT() {
  int i, u, v;
  cnt = stc = 0;
  for (i = 1; i <= V; ++i)
    if (!id[i])
      dfs(i);
  for (i = 1; i <= V; i += 2) {
    if ((u = top[i]) == (v = top[i + 1]))
      return false;
    conflict[u] = v, conflict[v] = u;
  }
  for (i = 0; i < V1; ++i)
    if (!col[v = topo[i]])
      col[v] = 1, col[conflict[v]] = -1;
  for (i = 1; i <= V; ++i)
    col[i] = col[top[i]];
  return true;
}
} // namespace Graph

namespace sat {
#define True(x) (2 * (x)-1)
#define False(x) (2 * (x))
using Graph::col;

int L, R, T, B, V, La, Lb, Ra, Rb, Ta, Tb, Ba, Bb;
int type[N], Lf[N], Rf[N], Tf[N], Bf[N];

inline void implies(int u, int v) {
  if (u > 0 && v > 0)
    Graph::implies(u, v);
}

inline void must(int x) {
  if (x > 0)
    Graph::must(x);
}

bool main() {
  int i, Lmax = -1, Rmin = INT_MAX, Tmax = -1, Bmin = INT_MAX;
  int l1, r1, l2, r2;
  bool LT, LB, RT, RB;
  for (i = 0; i < n; ++i)
    UP4D;
  if (Lmax <= Rmin || Tmax <= Bmin)
    return false;
  Ta = Ba = L = Rmin, Tb = Bb = R = Lmax,
  La = Ra = T = Bmin, Lb = Rb = B = Tmax;
  for (i = 0; i < n; ++i) {
    LT = r[i].contain(L, T), LB = r[i].contain(L, B);
    RT = r[i].contain(R, T), RB = r[i].contain(R, B);
    if (LT + LB + RT + RB > 1)
      continue;
    if (L < r[i].l && r[i].r < R && T < r[i].t && r[i].b < B)
      return false;
    if (LT)
      type[i] = 1;
    else if (LB)
      type[i] = 2;
    else if (RT)
      type[i] = 3;
    else if (RB)
      type[i] = 4;
    else if (r[i].l <= L && R <= r[i].r)
      type[i] = 5;
    else if (r[i].t <= T && B <= r[i].b)
      type[i] = 6;
    else if (r[i].l <= L)
      up(La, r[i].t), down(Lb, r[i].b);
    else if (r[i].r >= R)
      up(Ra, r[i].t), down(Rb, r[i].b);
    else if (r[i].t <= T)
      up(Ta, r[i].l), down(Tb, r[i].r);
    else if (r[i].b >= B)
      up(Ba, r[i].l), down(Bb, r[i].r);
    else
      throw "what the fuck ?";
  }
  if (La > Lb || Ra > Rb || Ta > Tb || Ba > Bb)
    return false;
  V = 0;
  for (i = La; i < Lb; ++i)
    Lf[i] = ++V;
  for (i = Ra; i < Rb; ++i)
    Rf[i] = ++V;
  for (i = Ta; i < Tb; ++i)
    Tf[i] = ++V;
  for (i = Ba; i < Bb; ++i)
    Bf[i] = ++V;
  Graph::V = V * 2;
  for (i = La + 1; i < Lb; ++i)
    implies(True(Lf[i - 1]), True(Lf[i]));
  for (i = Ra + 1; i < Rb; ++i)
    implies(True(Rf[i - 1]), True(Rf[i]));
  for (i = Ta + 1; i < Tb; ++i)
    implies(True(Tf[i - 1]), True(Tf[i]));
  for (i = Ba + 1; i < Bb; ++i)
    implies(True(Bf[i - 1]), True(Bf[i]));
#define operate(x, y, l1_, r1_, l2_, r2_)              \
  up(l1 = l1_, x##a), down(r1 = r1_, x##b),            \
      up(l2 = l2_, y##a), down(r2 = r2_, y##b);        \
  if (l1 > r1 && l2 > r2)                              \
    return false;                                      \
  if (l1 > r1)                                         \
    must(False(y##f[l2 - 1])), must(True(y##f[r2]));   \
  else if (l2 > r2)                                    \
    must(False(x##f[l1 - 1])), must(True(x##f[r1]));   \
  else                                                 \
    implies(True(x##f[l1 - 1]), False(y##f[l2 - 1])),  \
        implies(True(x##f[l1 - 1]), True(y##f[r2])),   \
        implies(False(x##f[r1]), False(y##f[l2 - 1])), \
        implies(False(x##f[r1]), True(y##f[r2]))
  for (i = 0; i < n; ++i)
    switch (type[i]) {
    case 1:
      operate(L, T, T, r[i].b, L, r[i].r);
      break;
    case 2:
      operate(L, B, r[i].t, B, L, r[i].r);
      break;
    case 3:
      operate(R, T, T, r[i].b, r[i].l, R);
      break;
    case 4:
      operate(R, B, r[i].t, B, r[i].l, R);
      break;
    case 5:
      operate(L, R, r[i].t, r[i].b, r[i].t, r[i].b);
      break;
    case 6:
      operate(T, B, r[i].l, r[i].r, r[i].l, r[i].r);
      break;
    }
  fprintf(stderr, "all (2x)%d vertices.\n", V);
  if (Graph::_2_SAT()) {
    mng::reset();
    for (i = La; i < Lb && col[False(Lf[i])] == 1; ++i)
      ;
    mng::insert(L, i);
    for (i = Ra; i < Rb && col[False(Rf[i])] == 1; ++i)
      ;
    mng::insert(R, i);
    for (i = Ta; i < Tb && col[False(Tf[i])] == 1; ++i)
      ;
    mng::insert(i, T);
    for (i = Ba; i < Bb && col[False(Bf[i])] == 1; ++i)
      ;
    mng::insert(i, B);
    return assert(mng::judge()), true;
  }
  return false;
}
} // namespace sat

int main() {
  int i;
  std::ios::sync_with_stdio(false), cin.tie(NULL);
  cin >> n >> K;
  for (i = 0; i < n; ++i)
    DC::D[i] = pr(r[i].read()->l, i), DC::D[i + n] = pr(r[i].r, i + n);
  cX = DC::Discretize(2 * n);
  for (i = 0; i < n; ++i)
    r[i].l = DC::F[i], r[i].r = DC::F[i + n];
  for (i = 0; i < cX; ++i)
    X[i] = DC::D[i].first;

  for (i = 0; i < n; ++i)
    DC::D[i] = pr(r[i].t, i), DC::D[i + n] = pr(r[i].b, i + n);
  cY = DC::Discretize(2 * n);
  for (i = 0; i < n; ++i)
    r[i].t = DC::F[i], r[i].b = DC::F[i + n];
  for (i = 0; i < cY; ++i)
    Y[i] = DC::D[i].first;

  if (simple::main())
    return 0;
  if (corner::main()) {
    cout << "case " << std::endl;
    return 0;
  }
  if (K == 4 && sat::main()) {
    return 0;
  }
  return cout << "No solution !!!\n", 0;
}
