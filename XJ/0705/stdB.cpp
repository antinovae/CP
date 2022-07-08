

//奇怪的做法..
#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define per(i, a, b) for (int i = (a); i >= (b); i--)
#define REP(i, n) for (int i = (0); i < (n); i++)
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define f(i, x, y) f[i][x + n][y + n]
#define g(i, x, y) g[i][x + n][y + n]
using namespace std;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef long long ll;

template <class T>
inline void read(T &x) {
  int f = 0;
  x = 0;
  char ch = getchar();
  for (; !isdigit(ch); ch = getchar())
    f |= (ch == '-');
  for (; isdigit(ch); ch = getchar())
    x = x * 10 + ch - '0';
  if (f)
    x = -x;
}

const int N = 155, mod = 998244353;
int f[N][N << 1][N << 1], g[N][N << 1][N << 1];
int s[N], pw[N], h[N][2], A[N], B[N];
int n, w1, w2, w3, w4, S2, S, ans;

int mul(int a, int b) {
  return (ll)a * b % mod;
}

void add(int &a, int b) {
  a = (a + b >= mod ? a + b - mod : a + b);
}

void sub(int &a, int b) {
  a = (a - b < 0 ? a - b + mod : a - b);
}

int main() {
  read(n);
  read(w1), read(w2);
  read(w3), read(w4);
  pw[0] = 1, pw[1] = ((ll)w1 + w2 + w3 + w4) % mod;
  rep(i, 2, n) pw[i] = mul(pw[i - 1], pw[1]);
  g(0, 0, 0) = 1;
  rep(i, 0, n - 1) rep(x, -i, i) rep(y, abs(x) - i, i - abs(x)) {
    if (!g(i, x, y))
      continue;
    add(g(i + 1, x + 1, y), mul(w1, g(i, x, y)));
    add(g(i + 1, x - 1, y), mul(w2, g(i, x, y)));
    add(g(i + 1, x, y - 1), mul(w3, g(i, x, y)));
    add(g(i + 1, x, y + 1), mul(w4, g(i, x, y)));
  }
  rep(i, 0, n) rep(x, -i, i) rep(y, abs(x) - i, i - abs(x)) {
    if (!g(i, x, y))
      continue;
    f(i, x, y) = g(i, x, y);
    rep(j, 0, i - 1) sub(f(i, x, y), mul(f(j, x, y), g(i - j, 0, 0)));
    add(s[i], f(i, x, y));
    add(S, mul(f(i, x, y), pw[n - i]));
  }
  rep(x, -n, n) rep(y, 0, n - abs(x)) {
    if (y == 0 && x <= 0)
      continue;
    memset(h, 0, sizeof h);
    rep(i, 1, n) A[i] = f(i, x, y), B[i] = f(i, -x, -y);
    int st = (x + y + 1) % 2 + 1;
    rep(i, 0, n) {
      for (int j = st; j <= i; j += 2) {
        sub(h[i][0], mul(h[i - j][1] + mod - s[i - j], A[j]));
        sub(h[i][1], mul(h[i - j][0] + mod - s[i - j], B[j]));
      }
      add(S2, mul(h[i][0] + h[i][1], pw[n - i]));
    }
  }
  ans = ((ll)(2ll * S2 + S) * pw[n] + mod - (ll)S * S % mod) % mod;
  cout << ans << endl;
  return 0;
}
