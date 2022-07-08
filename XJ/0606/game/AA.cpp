#include<bits/stdc++.h>
using namespace std;
const int maxn=2e6+5;
vector<int>g[maxn];
int cnt[50],vis[maxn],pri[maxn],tot;
const int B=100000;
void euler(int n){
    for(int i=2;i<=n;i++){
	if(!vis[i]){
	    pri[++tot]=i;
	}
	for(int j=1;pri[j]*i<=n;j++){
	    vis[pri[j]*i]=1;
	    if(i%pri[j]==0)break;
	}
    }
}
int cal(int x){
    int cnt=0;
    for(int i=1;i<=tot;i++){
	while(x%pri[i]==0){
	    x/=pri[i];
	    cnt++;
	}
    }
    if(x>1)cnt++;
    return cnt;
}
void pre(){
}
int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    freopen("table.cpp","w",stdout);
    pre();
    int n=1e9;
    euler(sqrt(n)+1);
    /* for(int i=2;i<=n;i++){ */
	/* for(int j=i+i;j<=n;j+=i){ */
	    /* g[j].push_back(i); */
	/* } */
    /* } */
    /* for(int i=2;i<=n;i++){ */
	/* if(!g[i].empty()){ */
	    /* vector<int>c; */
	    /* for(auto v:g[i]){c.push_back(f[v]);} */
	    /* sort(c.begin(),c.end()); */
	    /* int mn=0; */
	    /* f[i]=c.back()+1; */
	    /* for(auto v:c){ */
		/* if(v>mn){f[i]=mn;break;} */
		/* mn=v+1; */
	    /* } */
	/* } */
	/* cnt[f[i]]++; */
    /* } */
    /* f[0]=-1; */
    cnt[0]++;
    for(int i=2;i<=n;i++){
	int res=0;
	res=cal(i);
	cnt[res-1]++;
	/* if(f[i]!=res-1){ */
	/*     cout<< */
	/*     assert(0); */
	/* } */
	if(i%B==0){
	    cerr<<i<<endl;
	    printf("{");
	    for(int i=0;i<=30;i++){
		printf("%d",cnt[i]);
		if(i!=30)printf(",");
	    }
	    printf("},\n");

	}
	/* cout<<i<<' '<<f[i]<<" "<<res-1<<endl; */
    }
}

