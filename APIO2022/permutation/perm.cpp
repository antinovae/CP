#include "perm.h"
#include <algorithm>
#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
int flag = 0;
#define ll long long
unordered_map<ll,int>vis;

void init(int n) {
  vector<int> id(n);
  for (int i = 0; i < n; i++) {
    id[i] = i;
  }
  do {
    vector<ll> f(n);
    ll ans = 1;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < i; j++)
        if (id[j] < id[i])
          f[i] += f[j];
      f[i]++;
      ans += f[i];
    }
    /* for (auto v : id) */
      /* cout << v << " "; */
    /* cout << endl; */
    /* cout << ans << endl; */
    vis[ans]=1;

  } while (next_permutation(id.begin(), id.end()));
}

/* std::vector<int> construct_permutation(long long k) { */
/*   if (!flag) */
/*     init(); */
/*   flag = 1; */
/* } */
int main() {
  for(int i=1;i<=10;i++){
    cout<<i<<endl;
    init(i);
  }
  cout<<"fin: "<<vis.size()<<endl;
  for(int i=2;;i++){
    if(vis.find(i)==vis.end()){
      cout<<i;break;
    }
  }
}
