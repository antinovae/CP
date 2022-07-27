#include "game.h"
#include <bits/stdc++.h>
#include <vector>
using namespace std;
vector<int> l, r;
vector<vector<int>> e, f;

// r : min of out
// l: max of in
bool check(int, int);
bool update(int);

bool check(int x, int y) {
  // x to y
  if (r[y] <= l[x])
    return true;
  int midx = (l[x] + r[x]) >> 1;
  int midy = (l[y] + r[y]) >> 1;
  if (r[y] <= midx) {
    r[x] = midx;
    return update(x);
  }
  if (l[x] > midy) {
    l[y] = midy + 1;
    return update(y);
  }
  return false;
}

bool update(int x) {
  for (auto v : e[x]) {
    if (check(x, v))
      return true;
  }
  for (auto v : f[x]) {
    if (check(v, x))
      return true;
  }
  return false;
}

void init(int n, int k) {
  l = vector<int>(n);
  r = vector<int>(n);
  e = vector<vector<int>>(n);
  f = vector<vector<int>>(n);
  for (int i = 0; i < n; i++)
    l[i] = -1, r[i] = n;
  for (int i = 0; i < k; i++)
    l[i] = r[i] = i;
}

int add_teleporter(int u, int v) {
  e[u].push_back(v);
  f[v].push_back(u);
  return check(u, v);
  return 0;
}
