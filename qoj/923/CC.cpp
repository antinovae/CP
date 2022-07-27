#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ldb = long double;
const int N = 2e5 + 5;
const ll INF = 1e9;
int n;
int a[N];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
  }
  static ll suma[N], sumb[N], cura[N], curb[N];
  suma[1] = a[1];
  sumb[2] = a[2];
  curb[2] = a[1] + a[2];
  cura[1] = a[1];
  for (int i = 3; i <= n; i++) {
    if (i & 1) {
      cura[i] = min(cura[i - 2] + a[i], sumb[i - 1] + a[i]);
      suma[i] = suma[i - 2] + a[i];
      ldb ans = min((ldb)min(cura[i], curb[i - 1]) * 1.0, (ldb)(suma[i] + sumb[i - 1]) / 2.0);
      printf("%.1Lf ", ans);
    }
    else {
      curb[i] = min(curb[i - 2] + a[i], suma[i - 1] + a[i]);
      sumb[i] = sumb[i - 2] + a[i];
      cout << endl<<suma[i - 1] << ' ' << sumb[i] << endl;
      printf("%lld ", min(suma[i - 1], sumb[i]));
    }
    /* cout << "cura " << cura[i] << " curb " << curb[i] << endl; */
  }
}
