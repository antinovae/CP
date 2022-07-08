#include<bits/stdc++.h>
using namespace std;
const int maxn=3001;
int x,y,st[maxn],cc,res3,res2,res1,bcc,com1[maxn],com2[maxn],indec,n,m,top;
int low[maxn],dfn[maxn];
int ban[maxn][maxn],link[maxn][maxn];
vector<int>e[maxn];
void dfs(int x,int fa){
    /* cout<<x<<" "<<fa<<endl; */
    dfn[x]=low[x]=++indec;
    com1[x]=cc;
    st[++top]=x;
    for(auto v:e[x]){
	if(ban[x][v])continue;
	if(v==fa||!v)continue;
	if(!dfn[v]){
	    dfs(v,x);
	    low[x]=min(low[x],low[v]);
	}
	else{
	    if(dfn[v]<dfn[x]){
		low[x]=min(low[x],dfn[v]);
	    }
	}
    }
    if(low[x]==dfn[x]){
	com2[x]=++bcc;
	while(st[top]!=x){
	    com2[st[top]]=bcc;
	    top--;
	}
	top--;
    }
}
int cnt1[maxn],cnt2[maxn];
map<int,int>cnt3;
void cal_2(){
    for(int i=1;i<=n;i++){
	if(dfn[i])continue;
	++cc;dfs(i,0);
    }
    /* for(int i=1;i<=n;i++){ */
	/* cout<<i<<" dfn low "<<dfn[i]<<" "<<low[i]<<" com "<<com1[i]<<" "<<com2[i]<<endl; */
    /* } */
    for(int i=1;i<=n;i++){
	cnt1[com1[i]]++;
	cnt2[com2[i]]++;
    }
    for(int i=1;i<=n;i++){
	res1+=cnt1[i]*(cnt1[i]-1)/2;
	res2+=cnt2[i]*(cnt2[i]-1)/2;
    }
}
const int bs=6841,mo=1e9+9;
int hsh[maxn];
void cal_3(){
    for(int i=1;i<=n;i++){
	for(auto j:e[i]){
	    if(j>i)continue;
	    ban[i][j]=ban[j][i]=1;
	    memset(dfn,0,sizeof(dfn));
	    memset(low,0,sizeof(low));
	    memset(com2,0,sizeof(com2));
	    top=0;bcc=0;
	    for(int i=1;i<=n;i++){
		if(!dfn[i])dfs(i,0);
	    }
	    for(int i=1;i<=n;i++){
		hsh[i]=(1ll*hsh[i]*bs+com2[i])%mo;
	    }
	    ban[i][j]=ban[j][i]=0;
	}
    }
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
	scanf("%d%d",&x,&y);
	e[x].push_back(y);
	e[y].push_back(x);
    }
    cal_2();
    cal_3();
    for(int i=1;i<=n;i++){
	cnt3[hsh[i]]++;
    }
    for(auto v:cnt3)
	res3+=v.second*(v.second-1)/2;
    /* cout<<res1<<" "<<res2<<" "<<res3<<endl; */
    printf("%d\n",res1+res2+res3);
}
