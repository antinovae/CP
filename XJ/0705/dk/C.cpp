#include <bits/stdc++.h>
using namespace std;
const int N = 32, V = 22, mo = 998244353;

void add(int &x, int y) {
  x += y;
  if (x >= mo)
    x -= mo;
}

int b[N],res[N];
int f[N][N*V][V][V];
int g[N][N*V][V][V];

int main() {
  freopen("dk.in", "r", stdin);
  freopen("dk.out", "w", stdout);
  int n, v;
  scanf("%d%d", &n, &v);
  for (int i = 1; i <= n; i++)
    scanf("%d", &b[i]);
  sort(b + 1, b + n + 1);
  reverse(b + 1, b + n + 1);
  int lim = n * v + b[1];
  for (int i = 1; i <= lim; i++)
    f[0][i][v + 1][0] = 1;
  b[0] = v + 1;
  for (int i = 1; i <= n; i++) {
    for (int cnt = 0; cnt < i; cnt++) {
      for (int sum = b[i]; sum <= lim; sum++) {
        for (int mn = 1; mn <= v + 1; mn++) {
          for (int mx = 0; mx <= mn && mx <= v; mx++) {
            int val = f[cnt][sum][mn][mx];
            if (!val)
              continue;
            /* cout << i << " cnt " << cnt << " sum " << sum << " mn: " << mn << " mx " << mx << " " << val << endl; */
            if (mn < v) {
              if (b[i] + mn <= sum) {
                add(g[cnt + 1][sum][mn][mx], 1ll * (v - mn) * val % mo);
              }
              else {
                add(g[cnt + 1][sum][v + 1][mx], 1ll * (v - mn) * val % mo);
              }
            }
            int lim1 = min(mx, sum - b[i]);
            int lim2 = min({mn, v, sum - b[i] - mn});
            int lim3 = min({mn, v, sum - b[i]});
            for (int cur = 1; cur <= lim1; cur++) {
              if (b[i] + mn <= sum - cur) {
                add(g[cnt][sum - cur][mn][mx], val);
              }
              else {
                add(g[cnt][sum - cur][(v + 1)][mx], val);
              }
            }
            for (int cur = mx + 1; cur <= lim2; cur++) {
              add(g[cnt + 1][sum][cur][mx], val);
              add(g[cnt][sum - cur][mn][cur], val);
            }
            for (int cur = max(mx + 1, sum - b[i] - mn + 1); cur <= lim3; cur++) {
              add(g[cnt + 1][sum][cur][mx], val);
              add(g[cnt][sum - cur][v + 1][cur], val);
            }
            for (int cur = max(sum - b[i] + 1, mx + 1); cur <= min(mn, v); cur++) {
              if (b[i] + cur <= sum) {
                add(g[cnt + 1][sum][cur][mx], val);
              }
              else {
                add(g[cnt + 1][sum][v + 1][mx], val);
              }
            }
          }
        }
      }
    }
    for (int cnt = 0; cnt <= i; cnt++) 
      for (int sum = b[i+1]; sum <= lim; sum++) 
        for (int mn = 1; mn <= v + 1; mn++) 
          for (int mx = 0; mx <= mn && mx <= v; mx++)f[cnt][sum][mn][mx]=g[cnt][sum][mn][mx],g[cnt][sum][mn][mx]=0; 
    /* memcpy(f, g, sizeof(f)); */
    /* memset(g, 0, sizeof(g)); */
  }
  for (int j = 0; j <= n; j++)
    for (int s = 0; s <= lim; s++)
      for (int mx = 0; mx <= v; mx++)
        add(res[j], f[j][s][v + 1][mx]);
  for (int i = 1; i <= n; i++)
    add(res[i], res[i - 1]);
  int w = lim + 1;
  for (int i = 1; i <= n; i++)
    w = 1ll * w * v % mo;
  for (int i = 0; i <= n; i++)
    res[i] = (w - res[i] + mo) % mo;
  for (int i = 1; i <= n; i++)
    printf("%d ", res[n - i]);
  puts("");
  return 0;
}
