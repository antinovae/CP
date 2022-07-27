#include "Participant.h"
#include <bits/stdc++.h>
using namespace std;

namespace {
using ll = long long;
const int N = 1001;
ll g[N][N], dis[N][N];
int rem[N][N];
bool vis[N][N];
int n, K, Q;

ll f[N][6];

string code;
int iter;

int read_code() {
  int x = code[iter] - '0';
  ++iter;
  return x;
}

int getlen(int x) {
  return (int)floor(log2(x)) + 1;
}

int decode(int len) {
  int ans = 0;
  for (int i = 0; i < len; i++) {
    int v = read_code();
    ans += v << i;
  }
  return ans;
}

int cmp[N][6][6];

void decode_two(int x, int y) {
  cout << "decode " << x << " " << y << endl;
  cout << endl;
  vector<pair<ll, int>> s;
  s.reserve(Q);
  for (int i = 0; i < Q; i++) {
    s.emplace_back(f[i][x] - f[i][y], i);
  }
  sort(s.begin(), s.end());
  int len = getlen(Q);
  int pos = decode(len);
  cout << "found " << pos << endl;
  for (int i = 0; i < pos; i++) {
    cout << s[i].first << endl;
    cmp[s[i].second][x][y] = 0;
  }
  for (int i = pos; i < s.size(); i++) {
    cout << s[i].first << endl;
    cmp[s[i].second][x][y] = 1;
  }
}

void decode_all() {
  string code = "";
  for (int i = 0; i <= K; i++)
    for (int j = i + 1; j <= K; j++) {
      decode_two(i, j);
    }
}

void find_path(int s, int t, int ed, vector<int> &ans) {
  if (s == t) {
    if (ed)
      ans.push_back(s);
  }
  else {

    int mid = rem[s][t];
    if (!mid) {
      ans.push_back(s);
      if (ed)
        ans.push_back(t);
    }
    else {
      find_path(s, mid, 0, ans);
      find_path(mid, t, 1, ans);
    }
  }
}

} // namespace

void ParticipantSolve(int N, int M, int Qs, int Ks,
                      std::vector<int> U,
                      std::vector<int> V,
                      std::vector<long long> W,
                      std::vector<int> S,
                      std::vector<int> T,
                      std::vector<int> E,
                      std::string Z) {
  cout << "DECODE! " << endl;
  code = move(Z);
  n = N;
  K = Ks;
  Q = Qs;
  for (int i = 0; i < M; i++) {
    cout << W[i] << endl;
  }
  for (int i = 0; i < M; i++) {
    int x = U[i], y = V[i];
    ll w = W[i];
    vis[x][y] = true;
    g[x][y] = w;
  }
  for (int i = 0; i < K; i++) {
    vis[U[E[i]]][V[E[i]]] = false;
  }
  memset(dis, 127 / 3, sizeof(dis));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (vis[i][j])
        dis[i][j] = g[i][j];
      if (i == j)
        dis[i][j] = 0;
    }
  }
  for (int k = 0; k < n; k++)
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++) {
        ll val = min(dis[i][j], dis[i][k] + dis[k][j]);
        if (val < dis[i][j]) {
          dis[i][j] = val;
          rem[i][j] = k;
        }
      }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << "dis " << i << " " << j << " " << dis[i][j] << endl;
    }
  }

  for (int i = 0; i < Q; i++) {
    f[i][0] = dis[S[i]][T[i]];
    for (int j = 1; j <= K; j++) {
      f[i][j] = dis[S[i]][U[E[0]]] + dis[V[E[j - 1]]][T[i]];
    }
    for (int j = 0; j <= K; j++)
      cout << "X: " << i << " " << j << " " << f[i][j] << endl;
  }
  decode_all();
  for (int q = 0; q < Q; q++) {
    int p = 0;
    for (int i = 1; i <= K; i++) {
      if (p <= i) {
        if (cmp[q][p][i] == 1)
          p = i;
      }
      else {
        if (cmp[q][i][p] == 0)
          p = i;
      }
      cout << "ans: " << q << " " << p << endl;
    }
    vector<int> ans;
    if (p) {
      cout << S[q] << " -> " << U[E[p - 1]] << " -> " << V[E[p - 1]] << " -> " << T[q] << endl;
      find_path(S[q], U[E[p - 1]], 1, ans);
      find_path(V[E[p - 1]], T[q], 1, ans);
    }
    else
      find_path(S[q], T[q], 1, ans);
    for (auto v : ans)
      cout << v << " ";
    cout << endl;
    Report(ans);
  }
}
