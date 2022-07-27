#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
using namespace std;
#define spe mod + 1
#define mp make_pair
const int mod = 998244353;

int read() {
  int x = 0, f = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-')
      f = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * f;
}

void write(int x) {
  if (x < 0)
    x = -x, putchar('-');
  if (x >= 10)
    write(x / 10);
  putchar(x % 10 + '0');
}

int quickmod(int x, int y) {
  int Ans = 1;
  while (y) {
    if (y & 1)
      Ans = (1ll * Ans * x) % mod;
    x = (1ll * x * x) % mod;
    y >>= 1;
  }
  return Ans;
}

int n, m;
int a[4005], fac2[4005];
int A[2005][4005], B[2005][4005], C[2005][4005], D[2005][4005], cov[2005][4005], preC[2005][4005];

signed main() {
  //	freopen ("13.in", "r", stdin);
  //	freopen (".out", "w", stdout);
  n = read(), m = read();
  fac2[0] = 1;
  for (int i = 1; i <= 4001; i++)
    fac2[i] = (fac2[i - 1] * 2ll) % mod;
  int sum = 0;
  for (int i = 1; i <= m; i++)
    a[i] = read(), sum += a[i];
  sum = quickmod(sum, mod - 2);
  for (int i = 1; i <= m; i++)
    a[i] = (1ll * a[i] * sum) % mod;
  for (int i = 1; i <= m; i++) {
    cout << a[i] << " ";
  }
  cout << endl;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= 4000; j++) {
      A[i][j] = (a[j] + 1ll * A[i][j - 1] * A[i - 1][j - 1]) % mod;
    }
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= 4000; j++) {
      B[i][j] = (1ll * A[i][j - 1] * B[i - 1][j - 1] + 1ll * A[i - 1][j - 1] * B[i][j - 1] + 1ll * A[i - 1][j - 1] * A[i][j - 1] % mod * fac2[j]) % mod;
      if (B[i][j])
        cout << i << ' ' << j << " " << B[i][j] << " " << endl;
    }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= 4000; j++)
      C[i][j] = (1ll * B[i][j] * (1 + mod - A[i - 1][j]) + 1ll * A[i][j] * (preC[i - 1][j - 1] + cov[i - 1][j + 1])) % mod;
    for (int j = 1; j <= 4000; j++)
      preC[i][j] = (preC[i][j - 1] + C[i][j]) % mod;
    for (int j = 4000; j >= 1; j--)
      D[i][j] = (preC[i - 1][j - 1] + cov[i - 1][j + 1] + 1ll * A[i - 1][j] * (D[i][j + 1] + fac2[j + 1]) + B[i - 1][j]) % mod;
    for (int j = 4000; j >= 1; j--)
      cov[i][j] = (cov[i][j + 1] + 1ll * a[j] * D[i][j]) % mod;

    for (int j = 1; j <= 4000; j++)
      cout << C[i][j] << " " << D[i][j] << endl;
  }
  int Ans = 0;
  for (int i = 1; i <= m; i++)
    Ans = (Ans + 1ll * a[i] * D[n][i]) % mod;
  Ans = (Ans % mod + mod) % mod;
  write((1ll * Ans * quickmod(2, mod - 2)) % mod), putchar('\n');
  return 0;
}

/*
 */
