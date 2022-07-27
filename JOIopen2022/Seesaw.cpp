#include <algorithm>
#include <bits/stdc++.h>
#include <cstdio>
#include <random>
#include <vector>
using namespace std;
vector<int> a;

double cal(int l, int r) {
  double ans = 0;
  for (int i = l; i <= r; i++) {
    ans += a[i];
  }
  return ans / (r - l + 1);
}

int main() {
  int n;
  scanf("%d", &n);
  a.resize(n);
  mt19937 rnd(time(0));
  int V=200;
  for (int i = 0; i < n; i++)
    a[i]=rnd()%V;
  sort(a.begin(),a.end());
  vector<double> s;
  for (int l = 0; l < n; l++) {
    for (int r = l; r < n; r++) {
      s.push_back(cal(l, r));
    }
  }
  sort(s.begin(), s.end());
  double beg = cal(0, n - 1);
  auto check = [&](double lim) -> double {
    int l = 0, r = n - 1;
    double mn = beg;
    double sum = 0;
    for (auto v : a)
      sum += v;
    for (int i = 0; i < n - 1; i++) {
      if ((sum - a[l]) / (r - l) <= lim)
        sum -= a[l], ++l;
      else
        sum -= a[r], --r;
      mn = min(mn, sum / (r - l + 1));
      /* cout << l << " " << r << " " */
      /*      << "sum: " << sum << " " << mn << " " << lim << endl; */
    }
    return lim - mn;
  };
  int cnt=0;
  for (auto v : s) {
    if (v >= beg) {
      cout << check(v) << endl;
      ++cnt;
      if(cnt>=50)break;
    }
  }
}
