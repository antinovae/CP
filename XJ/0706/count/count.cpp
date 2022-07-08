#include <bits/stdc++.h>
#include <cstdio>
using namespace std;
const int N = 1001, mo = 1e9 + 7;

int qpow(int a, int b) {
  if (b == -1)
    b = mo - 2;
  assert(b >= 0);
  int res = 1;
  for (; b; b >>= 1, a = 1ll * a * a % mo)
    if (b & 1)
      res = 1ll * res * a % mo;
  return res;
}

void add(int &x, int y) {
  x += y;
  x > mo ? (x -= mo) : (x);
}

int n, m, vis[N];
vector<int> e[N];

void find_con(int x, int fa, int &cnt_p, int &cnt_e) {
  vis[x] = 1;
  cnt_p++;
  for (int &v : e[x]) {
    cnt_e++;
    if (!vis[v]) {
      find_con(v, x, cnt_p, cnt_e);
    }
  }
}

int cons[N];

int main() {
  freopen("count.in","r",stdin);
  freopen("count.out","w",stdout);
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    e[x].push_back(y);
    e[y].push_back(x);
  }
  bool cycle = false;
  int cc = 0;
  for (int i = 1; i <= n; i++) {
    if (!vis[i]) {
      int cnt_p = 0, cnt_e = 0;
      find_con(i, 0, cnt_p, cnt_e);
      cnt_e /= 2;
      /* cout << i << " " << cnt_p << " " << cnt_e << endl; */
      if (cnt_e == cnt_p - 1) {
        cons[++cc] = cnt_p;
      }
      else if (cnt_e == cnt_p) {
        if (cycle) {
          puts("0");
          return 0;
        }
        else {
          cycle = true;
          cons[++cc] = cnt_p;
        }
      }
      else if (cnt_e > cnt_p) {
        puts("0");
        return 0;
      }
      else
        assert(0);
    }
  }
  /* cout << cycle << endl; */
  /* for (int i = 1; i <= cc; i++) */
  /*   cout << cons[i] << " "; */
  /* cout << endl; */
  if (cycle) {
    int ans = 1;
    for (int i = 1; i <= cc; i++)
      ans = 1ll * ans * cons[i] % mo;
    ans = 1ll * ans * qpow(n, cc - 2) % mo;
    printf("%d\n", ans);
  }
  else {
    static int f[N][N], g[N][N];
    f[0][0] = 1;
    for (int i = 0; i < cc; i++) {
      for (int j = 0; j <= i; j++) {
        for (int sum = 0; sum <= n; sum++) {

          int val = f[j][sum];
          if (val) {
            if (cons[i + 1] > 1) {
              int v = cons[i + 1] * cons[i + 1] % mo;
              add(g[j + 1][sum + cons[i + 1]], 1ll * val * v % mo);
              add(g[j][sum], 1ll * val * cons[i + 1] % mo);
            }
            else {
              add(g[j + 1][sum + cons[i + 1]], 1ll * val % mo);
              add(g[j][sum], 1ll * val * cons[i + 1] % mo);
            }
          }
        }
      }
      if (i < cc) {
        memcpy(f, g, sizeof(f));
        memset(g, 0, sizeof(g));
      }
    }
    static int fac[N];
    fac[0] = 1;
    for (int i = 1; i <= n; i++) {
      fac[i] = 1ll * fac[i - 1] * i % mo;
    }
    int ans = 0;
    int inv2 = qpow(2, mo - 2);
    for (int cnt = 3; cnt <= cc; cnt++) {
      for (int sum = 3; sum <= n; sum++) {
        int cur = f[cnt][sum];
        if (cur) {
          cur = 1ll * cur * fac[cnt - 1] % mo * inv2 % mo;
          cur = 1ll * cur * sum % mo;
          cur = 1ll * cur * qpow(n, cc - cnt + 1 - 2) % mo;
          add(ans, cur);
        }
      }
    }
    int mul = 1;
    for (int i = 1; i <= cc; i++) {
      mul = 1ll * mul * cons[i] % mo;
    }
    for (int i = 1; i <= cc; i++) {
      int x = cons[i];
      if (x > 2) {
        int k = (x * (x - 1) / 2 - (x - 1));
        add(ans, 1ll * k * mul % mo * qpow(n, cc - 2)%mo);
      }
    }
    for (int i = 1; i <= cc; i++) {
      for (int j = i + 1; j <= cc; j++) {
        int x = cons[i];
        int y = cons[j];
        int mu = 1ll * mul * qpow(x, mo - 2) % mo * qpow(y, mo - 2) % mo * (x + y) % mo;
        if (y >= 2) {
          int k = y * (y - 1) / 2;
          add(ans, 1ll * k * x % mo * mu % mo * qpow(n, cc - 3) % mo);
        }
        if (x >= 2) {
          int k = x * (x - 1) / 2;
          add(ans, 1ll * k * y % mo * mu % mo * qpow(n, cc - 3) % mo);
        }
        if (x >= 2 && y >= 2) {
          int k1 = y * (y - 1) / 2;
          int k2 = x * (x - 1) / 2;
          add(ans, 1ll * k1 * k2 * 2 % mo * mu * qpow(n, cc - 3) % mo);
        }
        /* if(x>1&&y>1)cout << x<<" "<<y<<" "<<ans << endl; */
      }
    }
    printf("%d\n", ans);
  }
}
