#include <bits/stdc++.h>
#define ll long long
#define $ +N
using namespace std;
const ll mod = 1000000007; 
const int N = 155;
int n;
ll w1, w2, w3, w4, W, pw[N << 2];
ll g[N], w[N][N << 1][N << 1], Ans1, Ans2, f[N][N << 1][N << 1];

int mabs(int x) { return x > 0 ? x : -x; }

ll qpow(ll a, ll b) {
  ll ans = 1ll;
  while (b) {
    if (b & 1)
      ans = ans * a % mod;
    a = a * a % mod;
    b >>= 1;
  }
  return ans;
}

int main() {
  freopen("kel.in","r",stdin);
  freopen("kel.out","w",stdout);
  cin >> n;
  cin >> w1 >> w2 >> w3 >> w4;
  W = w1 + w2 + w3 + w4;
  W %= mod;
  pw[0] = 1ll;
  for (int i = 1; i <= n << 1; i++)
    pw[i] = pw[i - 1] * W % mod;
  w[0][0 $][0 $] = 1;
  for (int i = 1; i <= n; i++) {
    for (int x = -i; x <= i; x++) {
      int r = i - mabs(x);
      for (int y = -r; y <= r; y++) {
        w[i][x $][y $] = (w[i - 1][x $][y - 1 $] * w3 % mod + w[i - 1][x - 1 $][y $] * w1 % mod + w[i - 1][x + 1 $][y $] * w2 % mod + w[i - 1][x $][y + 1 $] * w4 % mod) % mod;
      }
    }
  }
  g[0] = 1;
  for (int i = 1; i <= n; i++) {
    ll tmp = 0;
    for (int j = 0; j < i; j++)
      tmp += g[j] * w[i - j][0 $][0 $] % mod, tmp %= mod;
    g[i] = (pw[i] + mod - tmp) % mod;
  }
  for (int i = 0; i <= n; i++)
    Ans1 += g[i] * pw[n - i] % mod, Ans1 %= mod;
  //	cout << Ans1 << endl;
  for (int i = 1; i <= n; i++) {
    for (int x = -i; x <= i; x++) {
      int r = i - mabs(x);
      for (int y = -r; y <= r; y++) {
        if (x == 0 && y == 0)
          continue;
        ll tmp = 0;
        int d = mabs(x) + mabs(y);
        for (int k = 0; k <= i - d; k++)
          tmp += g[k] * w[i - k][x $][y $] % mod, tmp %= mod;
        for (int k = 0; k <= i - d; k++)
          tmp += (mod - f[k][-x $][-y $] * w[i - k][x $][y $] % mod), tmp %= mod;
        for (int k = d; k <= i - 1; k++)
          tmp += (mod - f[k][x $][y $] * w[i - k][0 $][0 $] % mod), tmp %= mod;
        f[i][x $][y $] = tmp;
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int x = -i; x <= i; x++) {
      int r = i - mabs(x);
      for (int y = -r; y <= r; y++) {
        if (x == 0 && y == 0)
          continue;
        Ans2 += f[i][x $][y $] * pw[n - i] % mod, Ans2 %= mod;
      }
    }
  }
  ll Ans = (2 * Ans2 % mod + Ans1) % mod;
  //	cout << Ans << endl;
  Ans = Ans + mod - Ans1 * Ans1 % mod * qpow(pw[n], mod - 2) % mod;
  Ans %= mod;
  Ans = Ans * pw[n] % mod;
  cout << Ans << endl;
}
