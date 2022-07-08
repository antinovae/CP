#include <bits/stdc++.h>
#include <cstdio>
#include <unistd.h>
using uint128 = __uint128_t;
using namespace std;

template <typename T1, typename T2>
void cmax(T1 &x, T2 y) {
  if (x < y)
    x = y;
}

using ull = unsigned long long;

void write(uint128 x) {
  if (!x)
    putchar('0');
  static int s[101], top;
  top = 0;
  while (x)
    s[top++] = x % 10, x /= 10;
  for (int i = top - 1; i >= 0; i--)
    printf("%d", s[i]);
}

int n, m;
long long k;
ull seed, a[500001], b[500001];

ull Get() {
  seed = (seed << 43) ^ (seed >> 15) ^ (seed << 27) ^ seed;
  return seed >> 4;
}

uint128 f(ull x, ull y) {
  return ((((uint128)x * y >> 60) * (x + y) >> 60) * (x >> 30) * (y >> 30) >> 60) *
         (x + y);
}

void Main() {
  scanf("%d%d%lld%llu", &n, &m, &k, &seed);
  for (int i = 1; i <= n; i++)
    a[i] = Get();
  sort(a + 1, a + n + 1);
  for (int i = 1; i <= m; i++)
    b[i] = Get();
  sort(b + 1, b + m + 1);
  uint128 l = 0, r = (uint128)(1) << 122;
  while (l <= r) {
    uint128 mid = (l + r) >> 1;
    long long cnt = 0LL;
    for (int i = 1, p = m; i <= n; i++) {
      while (p >= 1 && f(a[i], b[p]) > mid)
        p--;
      cnt += p;
      if (cnt > k)
        break;
    }
    if (cnt == k) {
      uint128 ans = 0;
      for (int i = 1, p = m; i <= n; i++) {
        while (p >= 1 && f(a[i], b[p]) > mid)
          p--;
        if (!p)
          break;
        cmax(ans, f(a[i], b[p]));
      }
      write(ans);
      puts("");
      return;
    }
    if (cnt > k)
      r = mid - 1;
    else
      l = mid + 1;
  }
}

int main() {
  freopen("narrative.in","r",stdin);
  freopen("narrative.out","w",stdout);
  int T;
  scanf("%d", &T);
  while (T--)
    Main();
  return 0;
}
