#include <bits/stdc++.h>
#include <cstdio>
#include <cstring>
using namespace std;
using ll = long long;
using ldb = long double;
const int N = 2e5 + 5;
const ll INF = 1e18;
int n;
ll a[N];
ll f[N][3][3];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%lld", &a[i]);
  }
  memset(f, 127 / 3, sizeof(f));
  f[1][0][0] = 0;
  f[1][1][1] = a[1];
  f[1][2][2] = a[1] * 2;
  for (int i = 2; i <= n; i++) {
    for (int beg : {0, 1, 2})
      for (int j : {0, 1, 2}) {
        for (int k : {0, 1, 2}) {
          if (j + k >= 2) {
            f[i][beg][k] = min(f[i][beg][k], f[i - 1][beg][j] + a[i] * k);
          }
        }
      }
    if (i >= 3) {
      ldb ans = INF;
      for (int beg : {0, 1, 2})
        for (int j : {0, 1, 2})
          if (beg + j >= 2) {
            ans = min(ans, (ldb)f[i][beg][j]);
          }
      printf("%Lf ", ans / 2.0);
    }
  }
}
