#include<bits/stdc++.h>
using namespace std;
const int maxn=1000001;
int a[maxn][3];
int vis[8],n,d[3];
vector<int>s[8];
vector<pair<int,int>>ans;
int get(int x){
    if(x>n)return x-n;
    else return x+n;
}
void add(int i,int j){
    /* cout<<"add "<<i<<' '<<j<<endl; */
    ans.push_back({i,j});
    ans.push_back({get(j),get(i)});
}
int main(){
    scanf("%d",&n);
    for(int i=0;i<3;i++){
	for(int j=1;j<=n;j++){
	    scanf("%d",&a[j][i]);
	}
    }
    for(int i=1;i<=n;i++){
	int cur=0;
	for(int j=0;j<3;j++)cur|=(a[i][j]<<j);
	vis[cur]=1;
	s[cur].push_back(i);
    }
    for(int i=0;i<8;i++){
	if(vis[i]){
	    /* cout<<i<<endl; */
	    /* for(auto v:s[i])cout<<v<<" ";cout<<endl; */
	    for(int j=0;j<s[i].size()-1;j++)add(s[i][j],s[i][j+1]);
	    if(s[i].size()>1)add(s[i].back(),s[i][0]);
	}
    }
    if(vis[0]){
	add(s[0][0],s[0][0]+n);
    }
    if(vis[7]){
	add(s[7][0]+n,s[7][0]);
    }
    int cnt=0;
    for(int i=1;i<4;i++){
	/* cout<<i<<" "<<vis[i]<<" "<<vis[8-i]<<endl; */
	if(vis[i]&&vis[7-i]){
	    add(s[i][0],s[7-i][0]+n);
	    add(s[i][0]+n,s[7-i][0]);
	    d[cnt++]=i;
	}
	else {
	    if(vis[i])d[cnt++]=i;
	    else if(vis[7-i])d[cnt++]=7-i;
	}
    }
    if(cnt>=3){
	puts("-1");return 0;
    }
    else{
	int c0=__builtin_popcount(d[0]),c1=__builtin_popcount(d[1]);
	/* cout<<d[0]<<" "<<d[1]<<" "<<c0<<" "<<c1<<endl; */
	if(c0==1&&c1==1){
	    add(s[d[0]][0],s[d[1]][0]+n);
	    add(s[d[1]][0],s[d[0]][0]+n);
	}
	else if(c0==1&&c1==2){
	    add(s[d[0]][0],s[d[1]][0]);
	    add(s[d[1]][0]+n,s[d[0]][0]+n);
	}
	else if(c0==2&&c1==1){
	    add(s[d[0]][0]+n,s[d[1]][0]+n);
	    add(s[d[1]][0],s[d[0]][0]);
	}
	else if(c0==2&&c1==2){
	    add(s[d[0]][0]+n,s[d[1]][0]);
	    add(s[d[1]][0]+n,s[d[0]][0]);
	}
    }
    sort(ans.begin(),ans.end());
    ans.erase(unique(ans.begin(),ans.end()),ans.end());
    printf("%zu\n",ans.size());
    for(auto [u,v]:ans){
	string s,t;
	if(u>n)s="!x",u-=n;
	else s="x";
	if(v>n)t="!x",v-=n;
	else t="x";
	printf("%s%d -> %s%d\n",s.c_str(),u,t.c_str(),v);
    }
}
