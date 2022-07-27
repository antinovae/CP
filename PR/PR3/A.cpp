#include <bits/stdc++.h>
#include <cstdio>
#include <vector>
using namespace std;
const int N = 1001;
int a[N], b[N], c[N], d[N];

int main() {
  int n, m;
  scanf("%d%d", &n, &m);

  for (int i = 1; i < n; i++) {
    scanf("%d", &a[i]);
  }
  for (int i = 1; i <= m; i++) {
    scanf("%d", &b[i]);
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d", &c[i]);
  }
  for (int i = 1; i < m; i++) {
    scanf("%d", &d[i]);
  }

}
