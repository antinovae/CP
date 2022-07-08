#include <bits/stdc++.h>
#include <cstdio>
using namespace std;
const int N = 1001, mo = 1000000007;

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
      cout << i << " " << cnt_p << " " << cnt_e << endl;
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
  cout << cycle << endl;
  for (int i = 1; i <= cc; i++)
    cout << cons[i] << " ";
  cout << endl;
  if (cycle) {
    int ans = 1;
    for (int i = 1; i <= cc; i++)
      ans = 1ll * ans * cons[i] % mo;
    ans = 1ll * ans * qpow(n, cc - 2) % mo;
    printf("%d\n", ans);
  }
  else {
    static int f[N][N][2], g[N][N][2];
    f[0][0][0] = 1;
    for (int i = 0; i <= cc; i++) {
      for (int j = 0; j <= i; j++) {
        for (int sum = 0; sum <= n; sum++) {
          for (int st : {0, 1}) {

            int val = f[j][sum][st];
            if (val) {
              cout << i << " cnt: " << j << " sum: " << sum << " " << val << endl;
              if (cons[i + 1] > 1) {
                int v = cons[i + 1] * (cons[i + 1] - 1) % mo;
                add(g[j + 1][sum + cons[i + 1]][st], 1ll * val * v % mo);
                add(g[j + 1][sum + cons[i + 1]][st | 1], 1ll * val * cons[i + 1] % mo);
                add(g[j][sum][st], 1ll * val * cons[i + 1] % mo);
              }
              else {
                add(g[j + 1][sum + cons[i + 1]][st | 1], 1ll * val * cons[i + 1] % mo);
                add(g[j][sum][st], 1ll * val * cons[i + 1] % mo);
              }
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
        for (int k : {0, 1}) {

          int cur = f[cnt][sum][k];
          if (cur) {
            cout << "cnt " << cnt << " sum " << sum << " tp " << k << " " << cur << endl;
            /* if (cnt == 1) { */
            /*   int v = sum == 1 ? 1 : (sum * (sum - 1) % mo); */
            /*   cur = 1ll * f[cnt][sum][k] * qpow(v, mo - 2) % mo * (1ll * v * inv2 % mo - (sum - 1)) % mo; */
            /*   cout << "re " << cur << endl; */
            /* } */
            /* else if (cnt == 2) { */
            /*   if (k) */
            /*     cur = 1ll * cur * fac[cnt - 1] % mo * inv2 % mo; */
            /*   else */
            /*     cur = 1ll * cur * fac[cnt - 1] % mo; */
            /* } */
            /* else { */
            /* cur = 1ll * cur * fac[cnt - 1] % mo * inv2 % mo; */
            /* if (cnt == 2) { */
            /*   if (k) */
            /*     cur = 1ll * cur * fac[cnt - 1] % mo * inv2 % mo; */
            /*   else */
            /*     cur = 1ll * cur * fac[cnt - 1] % mo * inv2 % mo; */
            /* } */
            /* else { */
            /*   if (k) */
            /*     cur = 1ll * cur * fac[cnt - 1] % mo * inv2 % mo; */
            /*   else */
            /*     cur = 1ll * cur * fac[cnt - 1] % mo * inv2 % mo; */
            /* } */
            /* } */
            cur = 1ll * cur * fac[cnt - 1] % mo * inv2 % mo;
            cout << "cur: " << cur << endl;

            if (cc - cnt + 1 - 2 >= 0) {
              cur = 1ll * cur * sum % mo;
              cur = 1ll * cur * qpow(n, cc - cnt + 1 - 2);
              cout << "cur: " << cur << endl;
            }
            /* if (i > 1) { */

            /*   if (cc - i + 1 - 2 >= 0) */
            /*     add(ans, 1ll * f[i][j] * j % mo * fac[i - 1] % mo * inv2 % mo * qpow(n, cc - i + 1 - 2) % mo); */
            /*   else { */
            /*     add(ans, 1ll * f[i][j] % mo * fac[i - 1] % mo * inv2 % mo); */
            /*   } */
            /* } */
            /* else { */
            /*   if (cc - i + 1 - 2 >= 0) */
            /*     add(ans, 1ll * f[i][j] * j % mo * fac[i - 1] % mo * qpow(n, cc - i + 1 - 2) % mo); */
            /*   else { */
            /*     add(ans, 1ll * f[i][j] % mo * fac[i - 1] % mo); */
            /*   } */
            /* } */
            add(ans, cur);
            cout << ans << endl;
          }
        }
      }
    }
    printf("%d\n", ans);
  }
}
