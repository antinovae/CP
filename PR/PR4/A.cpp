#include <bits/stdc++.h>
#include <ios>
#include <vector>
using namespace std;
using ll = long long;
using ld = long double;
const double INF = 1e9;

struct point {
  ll x, y;
  point() = default;

  point(int x, int y) : x(x), y(y) {}

  point operator-(point a) const {
    return {x - a.x, y - a.y};
  }

  bool operator<(point a) const {
    if (x != a.x)
      return x < a.x;
    else
      return y < a.y;
  }
};

ll cross(point a, point b) {
  return 1ll * a.x * b.y - 1ll * a.y * b.x;
}

vector<point> con;

void convex_push(int x, int y) {
  point cur(x, y);
  while (con.size() >= 2 && cross(cur - *prev(con.end(), 1), cur - *prev(con.end(), 2))) {
    con.pop_back();
  }
  con.push_back(cur);
}

int main() {
  int n;
  scanf("%d", &n);
  vector<point> ev, ew;
  int sum = 0;
  for (int i = 0; i < n; i++) {
    int x, y, k;
    scanf("%d%d%d", &x, &y, &k);
    sum += -k;
    ev.emplace_back(x, k);
    ev.emplace_back(y, k);
  }
  sort(ev.begin(), ev.end());
  for (auto [x, y] : ev) {
    sum += y;
    convex_push(x, sum);
    ew.emplace_back(x, sum);
  }
  ll getval = [&](int x) {
    auto it = lower_bound(ew.begin(), ew.end(), point(x,INF));
    return prev(it)->y;
  };
  ld lst = INF;
  int ans = 0;
  for (int i = 0; i < con.size() - 1; i++) {
    point a = con[i], b = con[i + 1];
   ld k = (ld)(b.y - a.y) / (b.x - a.x);
    if ((int)lst >= k) {
      int p = (int)lst;
      ans = max(ans, k * b.x + b.y + getval(a.x));
      lst = k;
    }
    ans = max(ans, )
  }
}
