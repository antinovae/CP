#include <bits/stdc++.h>
using namespace std;

template <unsigned mod_>
struct ModInt {
  static constexpr unsigned mod = mod_;
  unsigned x;

  constexpr ModInt() : x(0U) {}

  constexpr ModInt(unsigned x_) : x(x_ % mod) {}

  constexpr ModInt(unsigned long long x_) : x(x_ % mod) {}

  constexpr ModInt(int x_) : x(((x_ %= static_cast<int>(mod)) < 0) ? (x_ + static_cast<int>(mod)) : x_) {}

  constexpr ModInt(long long x_) : x(((x_ %= static_cast<long long>(mod)) < 0) ? (x_ + static_cast<long long>(mod)) : x_) {}

  ModInt &operator+=(const ModInt &a) {
    x = ((x += a.x) >= mod) ? (x - mod) : x;
    return *this;
  }

  ModInt &operator-=(const ModInt &a) {
    x = ((x -= a.x) >= mod) ? (x + mod) : x;
    return *this;
  }

  ModInt &operator*=(const ModInt &a) {
    x = (static_cast<unsigned long long>(x) * a.x) % mod;
    return *this;
  }

  ModInt &operator/=(const ModInt &a) { return (*this *= a.inv()); }

  ModInt pow(long long e) const {
    if (e < 0)
      return inv().pow(-e);
    ModInt a = *this, b = 1U;
    for (; e; e >>= 1) {
      if (e & 1)
        b *= a;
      a *= a;
    }
    return b;
  }

  ModInt inv() const {
    unsigned a = mod, b = x;
    int y = 0, z = 1;
    for (; b;) {
      const unsigned q = a / b;
      const unsigned c = a - q * b;
      a = b;
      b = c;
      const int w = y - static_cast<int>(q) * z;
      y = z;
      z = w;
    }
    assert(a == 1U);
    return ModInt(y);
  }

  ModInt operator+() const { return *this; }

  ModInt operator-() const {
    ModInt a;
    a.x = x ? (mod - x) : 0U;
    return a;
  }

  ModInt operator+(const ModInt &a) const { return (ModInt(*this) += a); }

  ModInt operator-(const ModInt &a) const { return (ModInt(*this) -= a); }

  ModInt operator*(const ModInt &a) const { return (ModInt(*this) *= a); }

  ModInt operator/(const ModInt &a) const { return (ModInt(*this) /= a); }

  template <class T>
  friend ModInt operator+(T a, const ModInt &b) { return (ModInt(a) += b); }

  template <class T>
  friend ModInt operator-(T a, const ModInt &b) { return (ModInt(a) -= b); }

  template <class T>
  friend ModInt operator*(T a, const ModInt &b) { return (ModInt(a) *= b); }

  template <class T>
  friend ModInt operator/(T a, const ModInt &b) { return (ModInt(a) /= b); }

  explicit operator bool() const { return x; }

  bool operator==(const ModInt &a) const { return (x == a.x); }

  bool operator!=(const ModInt &a) const { return (x != a.x); }

  friend std::ostream &operator<<(std::ostream &os, const ModInt &a) { return os << a.x; }
};

const int N = 2001, mod = 998244353, L = 4000;

int p[N];
int n, m;

template <class T>
T qpow(T a, T b) {
  T res = 1;
  for (; b; b >>= 1, a = a * a)
    res = res * a;
  return res;
}

ModInt<mod> fac2[L + 5], a[L + 5], f[N][L + 5], g[N][L + 5], h[N][L + 5], d[N][L + 5], sh[N][L + 5], cov[N][L + 5];

int main() {
  scanf("%d%d", &n, &m);
  fac2[0] = 1;
  for (int i = 1; i <= L + 1; i++)
    fac2[i] = fac2[i - 1] * 2;
  ModInt<mod> sum = 0;
  for (int i = 1; i <= m; i++) {
    int x;
    scanf("%d", &x);
    a[i] = x;
    sum += a[i];
  }
  for (int i = 1; i <= m; i++)
    a[i] = a[i] * ModInt<mod>(sum).pow(mod - 2);
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= L; j++) {
      f[i][j] = a[j] + f[i][j - 1] * f[i - 1][j - 1];
    }
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= L; j++) {
      g[i][j] = f[i][j - 1] * g[i - 1][j - 1] + f[i - 1][j - 1] * g[i][j - 1] + f[i - 1][j - 1] * f[i][j - 1] * fac2[j];
    }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= L; j++)
      h[i][j] = g[i][j] * (1 - f[i - 1][j]) + f[i][j] * (sh[i - 1][j - 1] + cov[i - 1][j + 1]);
    for (int j = 1; j <= L; j++)
      sh[i][j] = (sh[i][j - 1] + h[i][j]);
    for (int j = L; j >= 1; j--)
      d[i][j] = sh[i - 1][j - 1] + cov[i - 1][j + 1] + f[i - 1][j] * (d[i][j + 1] + fac2[j + 1]) + g[i - 1][j];
    for (int j = L; j >= 1; j--)
      cov[i][j] = cov[i][j + 1] + a[j] * d[i][j];
    /* for(int j=1;j<=L;j++){ */
    /*   cout<<h[i][j]<<" "<<d[i][j]<<endl; */
    /* } */
  }
  ModInt<mod> Ans = 0;
  for (int i = 1; i <= m; i++){
    Ans += a[i] * d[n][i];
  }
  cout << Ans*  ModInt<mod>(2).pow(mod - 2);
  return 0;
}
