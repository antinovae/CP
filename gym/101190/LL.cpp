#include<bits/stdc++.h>
#define int long long
using namespace std;
const int U=2500;
const int INF=1.5e18;
int pri[2510],vis[2510],f[2510][405],g[2510][405],w[405];
int L,R;
int pre=-1,cur=0;
string s;
vector<int>T;
void print(int x) {
    if(x>9)print(x/10);
    s+=(char)((x%10)+'0');
}
void dfs(int x,int y,int W) {
    int res;
    if(g[x][y]+W*f[x][y]>INF) res=INF;
    else res=g[x][y]+W*f[x][y];
    if(!res)return;
    if(cur+res<L) {
        cur+=res;
        return;
    }
    if(!x) {
        if(pre<0)pre=cur;
        s+="[";
        for(auto x:T) {
            print(x);
            if(x==T.back())s+="], ";
            else s+=", ";
        }
        cur+=res;
        return;
    }
    T.push_back(pri[y]);
    dfs(x-pri[y],y+1,W+w[y]);
    T.pop_back();
    if(cur>=R)return;
    dfs(x,y+1,W);
}
void init() {
    for(int i=2; i<=U; i++) {
        if(!vis[i])pri[++pri[0]]=i;
        for(int j=1; j<=pri[0]&&i*pri[j]<=U; j++) {
            vis[i*pri[j]]=1;
            if(i%pri[j]==0) break;
        }
    }
}
signed main() {
    freopen("list.in","r",stdin);
    freopen("list.out","w",stdout);
    init();
    for(int i=1; i<=400; i++)f[0][i]=1;
    for(int i=1; i<=400; i++) {
        w[i]=2;
        for(int s=pri[i]; s; s/=10,w[i]++);
    }
    for(int i=1; i<=U; i++) {
        for(int j=400; j; j--) {
            int x=pri[j];
            if(x>i)continue;
            f[i][j]=min(INF,f[i][j+1]+f[i-x][j+1]);
            g[i][j]=min(INF,g[i][j+1]+g[i-x][j+1]+f[i-x][j+1]*w[j]);
        }
    }
    scanf("%lld%lld",&L,&R);
    for(int i=2; i<=U&&cur<R; i++)dfs(i,1,2);
    for(int i=L; i<=R; i++)putchar(s[i-pre-1]);
    return 0;
}

