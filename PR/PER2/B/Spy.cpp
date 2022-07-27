#include "Spy.h"
#include <bits/stdc++.h>
#include <vector>
using namespace std;

namespace {
const int N = 200001;
vector<int> e[N];
vector<int> col;

void dfs(int x, int fa) {
  if (fa) {
    if (x < fa)
      col[x] = col[fa];
    else
      col[x] = col[fa] ^ 1;
  }
  for (auto v : e[x]) {
    if (v != fa)
      dfs(v, x);
  }
}

} // namespace

std::vector<int> Init(int N, int T, std::vector<int> A, std::vector<int> B) {
  for (int i = 0; i < N - 1; i++) {
    int x = A[i], y = B[i];
    e[x].push_back(y);
    e[y].push_back(x);
  }
  col.resize(N + 1);
  dfs(T, 0);
  col.erase(col.begin());
  /* for(auto v:col){ */
  /*   cout<<v<<" "; */
  /* } */
  /* cout<<endl; */
  return col;
}
