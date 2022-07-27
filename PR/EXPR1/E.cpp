

#include <bits/stdc++.h>
using namespace std;
#define N 1205
#define mo 1000000007
#define ll long long

int ksm(int a, int k) {
  int s = 1;
  while (k) {
    if (k & 1)
      s = 1ll * s * a % mo;
    a = 1ll * a * a % mo;
    k >>= 1;
  }
  return s;
}

int n, col[N];
int f[N][N], g[N][N], ct[N];
int jc[N], nc[N];

int C(int n, int m) {
  if (n < 0 || m < 0 || n < m)
    return 0;
  return 1ll * jc[n] * nc[m] % mo * nc[n - m] % mo;
}

int main() {
  cin >> n;
  for (int i = 1, x; i <= n; i++) {
    cin >> x;
    col[x] = 1;
  }
  jc[0] = 1;
  for (int i = 1; i <= n; i++)
    jc[i] = 1ll * jc[i - 1] * i % mo;
  nc[n] = ksm(jc[n], mo - 2);
  for (int i = n - 1; i >= 0; i--)
    nc[i] = 1ll * nc[i + 1] * (i + 1) % mo;
  g[0][0] = 1;
  for (int i = 1; i <= n; i++)
    for (int j = 0; j < i; j++) {
      g[i][j] = (g[i][j] + g[i - 1][j]) % mo;
      g[i][j + 1] = (g[i][j + 1] + 2ll * g[i - 1][j]) % mo;
      if (j + 2 <= i)
        g[i][j + 2] = (g[i][j + 2] + g[i - 1][j]) % mo;
    }
  f[2 * n + 1][0] = 1;
  for (int i = 2 * n; i >= 1; i--) {
    for (int j = 0; j <= ct[1]; j++) {
      if (col[i]) {
        f[i][j] = (f[i][j] + f[i + 1][j]) % mo;
        for (int k = j + 1; k <= ct[1] + col[i]; k++)
          f[i][k] = (f[i][k] + 1ll * f[i + 1][j] * g[k - j - 1][k - j - 1] % mo * C(ct[1] - j, k - j - 1) % mo * (k - j + 1) % mo * jc[k - j - 1]) % mo;
      }
      else
        f[i][j] = (f[i][j] + 1ll * f[i + 1][j] * max(0, j - ct[0])) % mo;
    }
    ct[col[i]]++;
  }
  cout << (1ll * f[1][n] * ksm(ksm(2, mo - 2), n) % mo) << '\n';
  return 0;
}
