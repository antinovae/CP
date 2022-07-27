#include <bits/stdc++.h>
using namespace std;
const int N = 2005;
vector<int> e[N];

void color(int n) {
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> q;
  static int vis[N], deg[N];
  for (int i = 1; i <= n; i++) {
    q.push({e[i].size(), i});
    deg[i] = (int)e[i].size();
    vis[i] = 0;
  }
  vector<int> c;
  while (!q.empty() && c.size() < n) {
    auto [v, x] = q.top();
    q.pop();
    if (!vis[x]) {
      vis[x] = 1;
      c.push_back(x);
      for (auto v : e[x]) {
        if (!vis[v]) {
          deg[v]--;
          q.push({deg[v], v});
        }
      }
    }
  }

  reverse(c.begin(), c.end());
  static int cnt[N];
  static int col[N];
  static vector<int> grp[N];
  for (int i = 1; i <= n; i++)
    grp[i].clear();
  memset(col, 0, sizeof(col));
  for (auto x : c) {
    memset(cnt, 0, sizeof(cnt));
    for (auto v : e[x]) {
      cnt[col[v]]++;
    }
    for (int i = 1; i <= n; i++) {
      if (cnt[i] == 0) {
        col[x] = i;
        grp[i].push_back(x);
        break;
      }
    }
  }

  for (int i = 1; i <= n; i++) {
    if (!grp[i].empty()) {
      while (true) {
        cout << "? " << grp[i].size() + 1 << " " << n + 1 << " ";
        for (auto v : grp[i])
          cout << v << " ";
        cout << endl;
        int x, y;
        cin >> x >> y;
        if (x == -1)
          break;
        assert(x == n + 1 || y == n + 1);
        e[x].push_back(y);
        e[y].push_back(x);
        if (x == n + 1)
          grp[i].erase(find(grp[i].begin(), grp[i].end(), y));
        else
          grp[i].erase(find(grp[i].begin(), grp[i].end(), x));
        if (grp[i].empty())
          break;
      }
    }
  }
}

int main() {
  int n;
  cin >> n;
  for (int i = 1; i < n; i++) {
    color(i);
  }
  vector<pair<int, int>> ans;
  for (int i = 1; i <= n; i++) {
    for (auto j : e[i]) {
      if (i < j)
        ans.emplace_back(i, j);
    }
  }
  cout << "! " << ans.size() << endl;
  for (auto [x, y] : ans) {
    cout << x << " " << y << endl;
  }
}
