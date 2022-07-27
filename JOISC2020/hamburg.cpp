
#include <bits/stdc++.h>
#include <cstdio>
#include <sstream>
#include <string>
using namespace std;
int V;
vector<int> s[2];
stringstream out;

#define cout out
#define cerr out

struct two_sat {
  vector<vector<int>> e;
  vector<int> dfn, low, in, col;
  vector<int> st;
  int indec = 0, cc = 0;

  void tarjan(int x) {
    dfn[x] = low[x] = ++indec;
    st.push_back(x);
    in[x] = 1;
    for (auto v : e[x]) {
      if (!dfn[v]) {
        tarjan(v);
        low[x] = min(low[x], low[v]);
      }
      else if (in[v]) {
        low[x] = min(low[x], low[v]);
      }
    }
    if (dfn[x] == low[x]) {
      ++cc;
      while (st.back() != x) {
        int v = st.back();
        st.pop_back();
        in[v] = 0, col[v] = cc;
      }
      in[x] = 0, col[x] = cc;
      st.pop_back();
    }
  }

  int id(int var, int lim, int type) {
    return type * (4 * V) + var * V + lim + 1;
  }

  vector<int> solve() {
    for (int x = 1; x < e.size(); x++) {
      if (!dfn[x])
        tarjan(x);
    }
    vector<int> ans(4);
    for (int var = 0; var < 4; var++) {
      if (![&]() -> bool {
            for (int j = 1; j <= V; j++) {
              int x = id(var, j, 1);
              int nx = id(var, j, 0);
              if (col[x] == col[nx]) {
                assert(0);
              }
              if (col[x] < col[nx]) {
                ans[var] = j;
                return true;
              }
            }
            return false;
          }())
        ans[var] = -1;
    }
    return ans;
  }

  two_sat(int V) {
    e.resize(V * 4 * 2 + 10);
    dfn.resize(V * 4 * 2 + 10);
    low.resize(V * 4 * 2 + 10);
    in.resize(V * 4 * 2 + 10);
    col.resize(V * 4 * 2 + 10);
    for (int var = 0; var < 4; var++) {
      for (int j = 1; j < V; j++) {
        e[id(var, j + 1, 0)].push_back(id(var, j, 0));
        e[id(var, j, 1)].push_back(id(var, j + 1, 1));
      }
    }
  }

  void insert_or(int var1, int lim1, int tp1, int var2, int lim2, int tp2) {
    int x = id(var1, lim1, tp1), nx = id(var1, lim1, !tp1);
    int y = id(var2, lim2, tp2), ny = id(var2, lim2, !tp2);
    e[nx].push_back(y);
    e[ny].push_back(x);
  }

  void insert_must(int var, int lim, int tp) {
    int x = id(var, lim, tp), nx = id(var, lim, !tp);
    e[nx].push_back(x);
  }
};

struct point {
  int x, y;
};

struct mat {
  int xl, xr, yl, yr;

  bool contain(point c) const {
    return c.x >= xl && c.x <= xr && c.y >= yl && c.y <= yr;
  }
};

struct segs {
  vector<pair<int, int>> s;

  segs(const vector<mat> &src, int sdim) {
    if (sdim == 0) {
      for (auto [xl, xr, yl, yr] : src)
        s.emplace_back(xl, xr);
    }
    else {
      for (auto [xl, xr, yl, yr] : src)
        s.emplace_back(yl, yr);
    }
  }

  vector<int> solve() {
    sort(s.begin(), s.end(), [&](auto a, auto b) {
      if (a.second != b.second)
        return a.second < b.second;
      else
        return a.first < b.first;
    });
    int rst = 0;
    vector<int> ans;
    for (auto [cl, cr] : s) {
      if (cl > rst)
        rst = cr, ans.push_back(cr);
    }
    return ans;
  }
};

struct mat_set {
  vector<mat> s;
  int lim;
  vector<point> ans;

  vector<mat> filter(point c) {
    vector<mat> cur;
    for (const mat &v : s) {
      if (!v.contain(c))
        cur.push_back(v);
    }
    return cur;
  }

  mat find_core() {
    assert(!s.empty());
    auto [cxr, cxl, cyr, cyl] = s[0];
    for (auto &[xl, xr, yl, yr] : s) {
      cxl = min(cxl, xr);
      cxr = max(cxr, xl);
      cyl = min(cyl, yr);
      cyr = max(cyr, yl);
    }
    return {cxl, cxr, cyl, cyr};
  }

  bool bigsolve();

  bool solve() {
    if (s.empty())
      return true;
    if (lim == 0)
      return false;
    auto [cxl, cxr, cyl, cyr] = find_core();
    if (cxl >= cxr && cyl >= cyr) {
      ans.push_back({cxl, cyl});
      return lim >= 1;
    }
    else if (cxl >= cxr) {
      auto sub = segs(s, 1);
      auto res = sub.solve();
      for (auto y : res)
        ans.push_back({cxl, y});
      return lim >= ans.size();
    }
    else if (cyl >= cyr) {
      auto sub = segs(s, 0);
      auto res = sub.solve();
      for (auto x : res)
        ans.push_back({x, cyl});
      return lim >= ans.size();
    }
    else {
      mat_set cur;
      auto check = [&](point p) -> bool {
        auto pp = filter(p);

        cur = mat_set({pp, lim - 1, {}});
        if (cur.solve()) {
          ans = cur.ans;
          ans.push_back(p);
          return true;
        }
        return false;
      };
      if (check({cxl, cyl}) ||
          check({cxl, cyr}) ||
          check({cxr, cyl}) ||
          check({cxr, cyr}))
        return true;
      if (lim == 4) {
        auto sat = two_sat(V);
        for (const auto &[xl, xr, yl, yr] : s) {
          vector<tuple<int, int, int>> segs;
          if (xl <= cxl && xr >= cxl) {
            segs.emplace_back(max(cyl, yl), min(cyr, yr), 0);
          }
          if (xl <= cxr && xr >= cxr)
            segs.emplace_back(max(cyl, yl), min(cyr, yr), 1);
          if (yl <= cyl && yr >= cyl)
            segs.emplace_back(max(cxl, xl), min(cxr, xr), 2);
          if (yl <= cyr && yr >= cyr)
            segs.emplace_back(max(cxl, xl), min(cxr, xr), 3);
          if (segs.size() == 1) {
            auto [l, r, var] = segs[0];
            sat.insert_must(var, r, 1);
            sat.insert_must(var, l - 1, 0);
          }
          else if (segs.size() == 2) {
            auto [l1, r1, var1] = segs[0];
            auto [l2, r2, var2] = segs[1];
            sat.insert_or(var1, l1 - 1, 0, var2, l2 - 1, 0);
            sat.insert_or(var1, l1 - 1, 0, var2, r2, 1);
            sat.insert_or(var1, r1, 1, var2, l2 - 1, 0);
            sat.insert_or(var1, r1, 1, var2, r2, 1);
          }
        }
        vector<int> res = sat.solve();
        for (int i = 0; i < 4; i++) {
          if (res[i] == -1)
            assert(0);
        }
        ans = {{cxl, res[0]},
               {cxr, res[1]},
               {res[2], cyl},
               {res[3], cyr}};
        return true;
      }
      else
        return false;
    }
  }
};

mat_set S;

int main() {
  int n;
  scanf("%d%d", &n, &S.lim);
  vector<array<int, 4>> p(n);
  for (int i = 0; i < n; i++) {
    for (int j : {0, 1, 2, 3}) {
      scanf("%d", &p[i][j]);
    }
    s[0].push_back(p[i][0]);
    s[0].push_back(p[i][2]);
    s[1].push_back(p[i][1]);
    s[1].push_back(p[i][3]);
  }
  for (auto &c : s) {
    sort(c.begin(), c.end());
    c.erase(unique(c.begin(), c.end()), c.end());
  }
  for (auto &c : p) {
    c[0] = (int)(lower_bound(s[0].begin(), s[0].end(), c[0]) - s[0].begin() + 1);
    c[2] = (int)(lower_bound(s[0].begin(), s[0].end(), c[2]) - s[0].begin() + 1);
    c[1] = (int)(lower_bound(s[1].begin(), s[1].end(), c[1]) - s[1].begin() + 1);
    c[3] = (int)(lower_bound(s[1].begin(), s[1].end(), c[3]) - s[1].begin() + 1);
    S.s.push_back({c[0], c[2], c[1], c[3]});
  }
  V = (int)max(s[0].size(), s[1].size()) + 5;
  assert(S.solve());
  while (S.ans.size() < S.lim)
    S.ans.push_back(S.ans.back());
  vector<mat> cur = S.s;
  for (auto &[x, y] : S.ans) {
    printf("%d %d \n", s[0][x - 1], s[1][y - 1]);
  }
}
