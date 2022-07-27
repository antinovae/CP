#include "Spy.h"
#include "Participant.h"
#include <algorithm>
#include <bits/stdc++.h>
#include <sstream>
#include <string>
using namespace std;
stringstream out;
/* #define cout out */
namespace {
using ll = long long;
const int N = 1001;
ll g[N][N], dis[N][N];
bool vis[N][N];
int n, K, Q;
ll sp_dis[6];

ll f[N][6];
string code;

void append_code(int x) {
  if (x == 0)
    code += '0';
  else if (x == 1)
    code += '1';
  else
    assert(0);
}

int getlen(int x) {
  return (int)floor(log2(x)) + 1;
}

void encode(int val, int len) {
  for (int i = 0; i < len; i++) {
    append_code(val >> i & 1);
  }
}

void encode_two(int x, int y) {
  cout << "encode " << x << " " << y << endl;
  vector<pair<ll, int>> s;
  s.reserve(Q);
  for (int i = 0; i < Q; i++) {
    s.emplace_back(f[i][x] - f[i][y], i);
  }
  sort(s.begin(), s.end());
  int pos = (int)s.size();
  for (int i = 0; i < (int)s.size(); i++) 
    cout << (sp_dis[y] - sp_dis[x]) << " " << s[i].first << endl;
  for (int i = 0; i < (int)s.size(); i++) {
    if (sp_dis[y] - sp_dis[x] <= s[i].first) {
      pos = i;
      break;
    }
  }
  int len = getlen(Q);
  cout << "code " << pos << endl;
  encode(pos, len);
  cout << code << endl;
}

void encode_all() {
  string code = "";
  for (int i = 0; i <= K; i++)
    for (int j = i + 1; j <= K; j++) {
      encode_two(i, j);
    }
}

} // namespace

std::string SpySolve(int N, int M, int Qs, int Ks,
                     std::vector<int> U,
                     std::vector<int> V,
                     std::vector<long long> W,
                     std::vector<int> S,
                     std::vector<int> T,
                     std::vector<int> E) {
  n = N;
  K = Ks;
  Q = Qs;
  for (int i = 0; i < K; i++) {
    sp_dis[i + 1] = W[E[i]];
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
      for (int j = 0; j < n; j++)
        dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << "dis " << i << " " << j << " " << dis[i][j] << endl;
    }
  }

  for (int i = 0; i < Q; i++) {
    f[i][0] = dis[S[i]][T[i]];
    for (int j = 1; j <= K; j++) {
      /* cout << i << ' ' << j << " dis: " << S[i] << " " << U[E[0]] << " dis: " << V[E[j - 1]] << " " << T[i] << " " << dis[S[i]][U[E[0]]] << " " << dis[V[E[j - 1]]][T[i]] << endl; */

      f[i][j] = dis[S[i]][U[E[0]]] + dis[V[E[j - 1]]][T[i]];
    }
    for (int j = 0; j <= K; j++)
      cout << "X: " << i << " " << j << " " << f[i][j] << endl;
  }
  encode_all();
  return code;

}
