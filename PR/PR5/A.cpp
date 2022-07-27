#include <bits/stdc++.h>
using namespace std;
const int N = 19;
int a[N][N], f[1 << N][N][N], g[1 << N];

void cmin(int &x, int y) {
  x = min(x, y);
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      scanf("%d", &a[i][j]);
    }
  }
  int ans = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < i; j++) {
      if (a[i][j] != -1 && a[j][i] != -1) {
        int mn = min(a[i][j], a[j][i]);
        ans += mn;
        a[i][j] -= mn;
        a[j][i] -= mn;
      }
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++)
      cout << a[i][j] << " ";
    cout << endl;
  }
  memset(f, 127 / 3, sizeof(f));
  memset(g, 127 / 3, sizeof(g));
  g[1] = 0;
  for (int s = 1; s < 1 << n; s++)
    for (int cur = 0; cur < n; cur++)
      for (int tar = 0; tar < n; tar++) {
        cmin(f[s][cur][tar], g[s]);
        if (f[s][cur][tar] <= 10000) {

          if ((s >> cur & 1) && (s >> tar & 1)) {
            for (int i = 0; i < 4; i++) {
              cout << (s >> i & 1);
            }
            cout << " " << cur << ' ' << tar << " " << f[s][cur][tar] << endl;
            for (int nxt = 0; nxt < n; nxt++) {
              if (tar != nxt) {
                if (a[tar][nxt] >= 0) {
                  if (!(s >> nxt & 1)) {
                    cout << "add " << nxt << " " << a[tar][nxt] << endl;
                    cmin(f[s | (1 << nxt)][nxt][tar], f[s][cur][tar] + a[tar][nxt]);
                  }

                  else {
                    if (tar == nxt)
                      cmin(g[s], f[s][cur][tar] + a[tar][nxt]);
                  }
                }
              }
            }
          }
        }
      }
  cout << ans + g[1 << n - 1];
}
