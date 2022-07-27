#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f3f3f3f3f;

ll mul(ll x, ll y) { return !x || y <= INF / x ? x * y : INF; }

int k;
ll n;
ll pw[20];
ll dp[60][610];

ll solve(vector<int> a) {
  ;
  for (auto it : a)
    if (it == 9)
      return 0;
  ll cal = 0;
  vector<int> cnt(k, 0);
  for (int i = 0; i < a.size(); i++) {
    if (a[i] == -1)
      cnt[i % k]++;
    else
      cal = (cal + pw[i % k] * a[i]) % (pw[k] - 1);
  }
  cal = (pw[k] - 1 - cal) % (pw[k] - 1);
  ll maxj = 0;
  for (int i = 0; i < k; i++) {
    maxj += 8 * pw[i] * cnt[i];
  }
  ll ans = 0;
  while (cal <= maxj) {
    // cout << "       need:" << need << endl;
    static const int B = 50;
    static ll f[B * 2 + 1];
    memset(f, 0, sizeof(f));
    f[B + cal / pw[k]] = 1;
    for (int i = k - 1; i >= 0; i--) {
      static ll g[B * 2 + 1];
      memset(g, 0, sizeof(g));
      for (int p = -B; p <= B; p++) {
        int pp = p * 10 + cal / pw[i] % 10;
        for (int t = 0; t <= cnt[i] * 8; t++) {
          int q = min(max(0, pp - t + B), B + B);
          g[q] += mul(f[p + B], dp[cnt[i]][t]);
          g[q] = min(g[q], INF);
        }
      }
      memcpy(f, g, sizeof(f));
    }
    ans += f[B];
    ans = min(ans, INF);
    cal += pw[k] - 1;
  }
  return ans;
}

int main() {
  dp[0][0] = 1;
  for (int i = 1; i <= 55; i++) {
    for (int j = 0; j <= 8 * i; j++) {
      for (int t = 0; t <= 8 && t <= j; t++) {
        dp[i][j] += dp[i - 1][j - t];
        dp[i][j] = min(dp[i][j], INF);
      }
    }
  }
  pw[0] = 1;
  for (int i = 1; i <= 18; i++)
    pw[i] = pw[i - 1] * 10;
  cin >> k >> n;
  n++;
  // cout << Solve({-1}) << endl;
  // return 0;
  vector<int> a;
  a.push_back(-1);
  while (solve(a) < n)
    a.push_back(-1);
  for (int i = (int)a.size() - 1; i >= 0; i--) {
    a[i] = 0;
    while (1) {
      ll tmp = solve(a);
      if (n <= tmp)
        break;
      n -= tmp, a[i]++;
    }
  }
  ll cur = 0;
  for (int i = (int)a.size() - 1; i >= 0; i--) {
    cur = cur * 10 + a[i];
    a[i] = cur / (pw[k] - 1), cur %= pw[k] - 1;
  }
  while (a.size() > 1 && a.back() == 0)
    a.pop_back();
  for (auto it : vector<int>(a.rbegin(), a.rend())) {
    cout << it;
  }
  cout << endl;
  return 0;
}
