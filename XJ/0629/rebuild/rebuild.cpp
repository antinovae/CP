#include "rebuild.h"
#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<int> c, p;

void run(int x) {
  if (c[x])
    return;
  ++m;
  int cur = x;
  for (int i = 0; i <= 4; ++i) {
    if (c[cur])
      break;
    c[cur] = m;
    cur = p[cur];
  }
  run(cur);
}
void solve(vector<int> _p) {
  n = _p.size();
  c.resize(n);
  p = _p;
  while (1) {
    bool flag = true;
    m = 0;
    for (int i = 0; i < n; ++i)
      flag &= (p[i] == i), c[i] = 0;
    if (flag)
      break;
    for (int i = 0; i < n; ++i)
      run(i);
    p = shuffle(c);
  }
}
