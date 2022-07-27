#include <bits/stdc++.h>
using namespace std;
const int INF = 1000001;

struct point {
  int x, y, tp, id;
};

vector<point> a, b;
vector<int> ans;

struct bit {
  vector<pair<int, int>> c;

  bit(int n) {
    c.resize(n);
    fill(c.begin(),c.end(),make_pair(INF,0));
  }

  void modify(int x, pair<int, int> v) {
    for (; x < c.size(); x += x & (-x))
      c[x] = min(c[x], v);
  }

  pair<int, int> query(int x, pair<int, int> res = {INF, 0}) {
    for (; x; x -= x & -x)
      res = min(res, c[x]);
    return res;
  }
};

tuple<vector<point>, vector<point>, vector<point>, vector<point>> solve(const vector<point> &a, const vector<point> &b) {
  vector<int> sy;
  sy.reserve(a.size() + b.size());
  for (auto v : a) 
    sy.push_back(v.y);
  for (auto v : b) 
    sy.push_back(v.y);
  sort(sy.begin(), sy.end());
  sy.erase(unique(sy.begin(), sy.end()), sy.end());

  vector<point> c;
  for (auto [x, y, t, id] : a) {
    y = (int)(lower_bound(sy.begin(), sy.end(), y) - sy.begin() + 1);
    c.push_back({x, y, t, id});
  }
  for (auto [x, y, t, id] : b) {
    y = (int)(lower_bound(sy.begin(), sy.end(), y) - sy.begin() + 1);
    c.push_back({x, y, t, id});
  }
  sort(c.begin(), c.end(), [&](point a, point b) {
    if (a.x != b.x)
      return a.x < b.x;
    else
      return a.y < b.y;
  });
  vector<pair<int, int>> f(a.size() + b.size());
  bit T((int)(sy.size() + 5));
  for (int i = 0; i < c.size(); i++) {
    int j = 0;
    int sum_a = 0, sum_b = 0;
    while (c[j].x == c[i].x) {
      if (c[j].tp)
        sum_b++;
      j++;
    }
    for (int k = i; k < j; k++) {
      pair<int, int> pre_val = T.query(c[j].y);
      f[i] = {pre_val.first + sum_a + sum_b, pre_val.second};
      T.modify(c[j].y, {f[i].first, i});
      if (c[j].tp)
        sum_b--;
      else
        sum_a++;
    }
  }
  auto id = T.query((int)b.size()).second;
  unordered_map<int, int> s;
  while (id) {
    s[c[id].x] = c[id].y;
    id = T.query(c[id].y).second;
  }
  vector<point> ans_a, ans_b, not_ans_a, not_ans_b;
  for (auto v : c) {
    if (v.tp == 0) {
      if (v.y <= s[v.x])
        ans_a.push_back(v);
      else
        not_ans_a.push_back(v);
    }
    else {
      if (v.y > s[v.x])
        ans_b.push_back(v);
      else
        not_ans_b.push_back(v);
    }
  }
  return {ans_a, not_ans_a, ans_b, not_ans_b};
}

void div(const vector<point> &a, const vector<point> &b, int ca, int cb) {
  if (!a.size())
    return;
  if (!b.size()) {
  }

  vector<point> lft, rig;
  int mid = a[a.size() / 2].id;
  for (auto v : a) {
    if (v.id <= mid)
      lft.push_back(v);
    else
      rig.push_back(v);
  }
  auto [ans_a, not_ans_a, ans_b, not_ans_b] = solve(lft, b);
  for (auto v : not_ans_a)
    rig.push_back(v);
  int cla = ca + (int)(lft.size() - not_ans_a.size());
  int crb = cb + (int)ans_b.size();
  ans[mid] = cla + crb;
  div(rig, ans_b, cla, cb);
  div(ans_a, not_ans_b, ca, crb);
}

int main() {
  int n;
  scanf("%d", &n);
  b.resize(n), a.resize(n);
  ans.resize(n);
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", &b[i].x, &b[i].y);
    b[i].tp = 1;
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", &a[i].x, &a[i].y);
    b[i].tp = 0;
  }
  div(a, b, 0, 0);
  for(int i=0;i<n;i++){
    ans[i]=max(ans[i],ans[i-1]);
    printf("%d\n",ans[i]);
  }
}
