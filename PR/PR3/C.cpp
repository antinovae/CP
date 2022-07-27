#include <bits/stdc++.h>
const int N = 4e3, mo = 998244353;

int m, n, va[N + 5], vb[N + 5], su, vs;

inline int qpow(int x, int y) {
  int z = 1;
  for (; y; x = 1ll * x * x % mo, y >>= 1)
    if (y & 1)
      z = 1ll * z * x % mo;
  return z;
}

inline int inv(int x) { return qpow(x, mo - 2); }

int f[N + 5][N + 5], g[N + 5][N + 5];

int main() {
  scanf("%d%d", &m, &n);
  for (int i = 0; i <= m; ++i)
    scanf("%d", &va[i]), su += va[i];
  vs = inv(su);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &vb[i]);

  f[0][0] = 1ll * va[0] * vs % mo;
  for (int i = 1; i <= m; ++i)
    f[0][i] = (f[0][i - 1] + 1ll * va[i] * vs) % mo;
  for (int i = 1; i <= n; ++i)
    for (int j = i; j <= m; ++j)
      f[i][j] = (qpow(f[i - 1][j], vb[i]) + mo - qpow(f[i - 1][i - 1], vb[i])) % mo;

  for (int i = 0; i < n; ++i)
    for (int j = i; j <= m; ++j)
      f[i][j] = qpow(f[i][j], vb[i + 1] - 1);
  g[n][m] = 1;
  for (int i = n - 1; ~i; --i) {
    for (int j = m; j > i; --j)
      g[i][j] = 1ll * f[i][j] * g[i + 1][j] % mo;
    for (int j = m; j > i; --j)
      g[i][i] = (1ll * (mo - f[i][i]) * g[i + 1][j] + g[i][i]) % mo;
  }

  for (int k = 0; k <= m; ++k) {
    int ans = 0;
    for (int i = k; i <= m; ++i)
      ans = (1ll * va[k] * vs % mo * g[0][i] + ans) % mo;
    for (int i = 1; i <= n; ++i)
      ans = 1ll * ans * vb[i] % mo;
    printf("%d\n", ans);
  }

  return 0;
}
