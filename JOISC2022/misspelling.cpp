#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
const int N = 500050;
int n, m;
multiset<int> H0, H1;
vector<pair<int, int>> in[N], out[N];
int dp[N][26], U[N][26], D[N][26]; // dp[i][j]: s_i=j,s_i\neq s_{i-1}

inline int cal_0(int l, int r, int x) {
  if (x == 0)
    return 0;
  return (D[r][x - 1] - D[l - 1][x - 1] + mod) % mod;
}

inline int cal_1(int l, int r, int x) {
  if (x == 25)
    return 0;
  return (U[r][x + 1] - U[l - 1][x + 1] + mod) % mod;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= m; ++i) {
    int l, r, opt = 0;
    cin >> l >> r;
    if (l > r)
      opt ^= 1, swap(l, r);
    if (opt)
      out[l + 1].emplace_back(l, 1), out[r + 1].emplace_back(l, -1);
    else
      in[l + 1].emplace_back(l, 1), in[r + 1].emplace_back(l, -1);
  }
  for (int i = 0; i < 26; ++i)
    D[1][i] = i + 1, U[1][i] = 26 - i;
  int ans = 26;
  for (int i = 2; i <= n; ++i) {
    for (auto [x, opt] : in[i]) {
      if (opt == 1)
        H0.insert(x);
      else
        H0.erase(H0.find(x));
    }
    for (auto [x, opt] : out[i]) {
      if (opt == 1)
        H1.insert(x);
      else
        H1.erase(H1.find(x));
    }
    int pa = H0.empty() ? 1 : *H0.rbegin() + 1;
    int pb = H1.empty() ? 1 : *H1.rbegin() + 1;
    for (int j = 0; j < 26; ++j) {
      if (pa < i) {
        dp[i][j] = (dp[i][j] + cal_0(pa, i - 1, j)) % mod;
      }
      if (pb < i) {
        dp[i][j] = (dp[i][j] + cal_1(pb, i - 1, j)) % mod;
      }
    }
    for (int j = 0, now = 0; j < 26; ++j) {
      ans = (ans + dp[i][j]) % mod;
      now = (now + dp[i][j]) % mod;
      D[i][j] = (D[i - 1][j] + now) % mod;
    }
    for (int j = 25, now = 0; j >= 0; --j) {
      now = (now + dp[i][j]) % mod;
      U[i][j] = (U[i - 1][j] + now) % mod;
    }
  }
  cout << ans << '\n';
  return 0;
}
