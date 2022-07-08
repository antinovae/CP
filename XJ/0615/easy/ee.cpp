#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
int n,m,c[maxn];
vector<int>e[maxn],st;
unordered_map<int,int>s[maxn];
vector<pair<int,int>>ans;
int in[maxn];
void rmv(int i,int c){
    s[i][c]--;
    if(!s[i][c])s[i].erase(s[i].find(c));
    if(s[i].size()==1&&!in[i])st.push_back(i);
}
void solve(){
    while(!st.empty()){
	int x=st.back();st.pop_back();
	int cc=c[x];
	in[x]=0;
	if(cc==-1){
	    for(auto v:e[x]){
		if(c[v]!=-1){
		    cc=c[v];
		    break;
		}
	    }
	}
	if(cc==-1)continue;
	ans.push_back({x,cc});
	if(c[x]!=-1){
	    rmv(x,c[x]);
	    for(int j:e[x])rmv(j,c[x]);
	    c[x]=-1;

	}
	for(auto v:e[x]){
	    if(c[v]!=-1){
		rmv(v,c[v]);
		for(int j:e[v])rmv(j,c[v]);
		c[v]=-1;
	    }
	}
    }
}
int main(){
    freopen("easy.in","r",stdin);
    freopen("easy.out","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
	scanf("%d",&c[i]);
	s[i][c[i]]=1;
    }
    for(int i=1;i<=m;i++){
	int x,y;
	scanf("%d%d",&x,&y);
	e[x].push_back(y);e[y].push_back(x);
	s[x][c[y]]++,s[y][c[x]]++;
    }
    for(int i=1;i<=n;i++){
	if(s[i].size()==1){
	    st.push_back(i);
	    in[i]=1;
	}
    }  
    solve();
    for(int i=1;i<=n;i++){
	if(c[i]!=-1){
	    puts("NO");
	    return 0;
	}
    }
    puts("YES");
    reverse(ans.begin(),ans.end());
    printf("%d\n",(int)ans.size());
    for(auto v:ans){
	printf("%d %d\n",v.first,v.second);
    }
} 
