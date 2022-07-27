#include "guess.h"
#include <bits/stdc++.h>
#define ll long long
#define uit unsigned int
using namespace std;
vector<int> ans;
int p[10], w[10];

bool cmp(int x, int y) {
  return w[x] > w[y];
}

vector<int> solve(int n, int m) {
  ans.resize(n);
  p[0] = 0;
  p[1] = 1;
  p[2] = 2;
  p[3] = 3;
  w[0] = query2(1, 2, 3);
  w[1] = query2(0, 2, 3);
  w[2] = query2(0, 1, 3);
  w[3] = query2(0, 1, 2);
  sort(p, p + 4, cmp);
  int mn = w[p[3]], mx = w[p[0]];
  for (int i = 4; i < n; i++) {
    int x = query2(p[0], p[3], i);
    if (x == mn)
      ans[p[0]] = x, p[0] = i, mn = query2(p[0], p[1], p[2]);
    else if (x == mx)
      ans[p[3]] = x, p[3] = i, mx = query2(p[1], p[2], p[3]);
    else if (x < mn)
      ans[p[1]] = mn, p[1] = i, mn = x;
    else if (x > mx)
      ans[p[2]] = mx, p[2] = i, mx = x;
    else
      ans[i] = x;
  }
  if (query1(p[0], p[1]))
    ans[p[0]] = 1, ans[p[1]] = 2;
  else
    ans[p[1]] = 1, ans[p[0]] = 2;
  if (query1(p[2], p[3]))
    ans[p[2]] = n - 1, ans[p[3]] = n;
  else
    ans[p[3]] = n - 1, ans[p[2]] = n;
  return ans;
}
