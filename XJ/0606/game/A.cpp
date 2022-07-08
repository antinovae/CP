#include<bits/stdc++.h>
using namespace std;
const int maxn=2e6+5;
vector<int>g[maxn];
int cnt[50],vis[maxn],pri[maxn],f[maxn],tot;
const int B=100000;
void euler(int n){
    for(int i=2;i<=n;i++){
	if(!vis[i]){
	    pri[++tot]=i;
	    f[i]=1;
	}
	for(int j=1;pri[j]*i<=n;j++){
	    vis[pri[j]*i]=1;
	    f[pri[j]*i]+=f[i];
	    if(i%pri[j]==0){
		break;
	    }
	    else{

	    }
	}
    }
}
// C++ Version
void pre() {
  d[1] = 1;
  for (int i = 2; i <= n; ++i) {
    if (!v[i]) v[i] = 1, p[++tot] = i, d[i] = 2, num[i] = 1;
    for (int j = 1; j <= tot && i <= n / p[j]; ++j) {
      v[p[j] * i] = 1;
      if (i % p[j] == 0) {
        num[i * p[j]] = num[i] + 1;
        d[i * p[j]] = d[i] / num[i * p[j]] * (num[i * p[j]] + 1);
        break;
      } else {
        num[i * p[j]] = 1;
        d[i * p[j]] = d[i] * 2;
      }
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
/* void pre(){ */
/* } */
/* void fwt(int *a,int tp){ */
/*     for(int mid=1;mid<1<<n;mid<<=1){ */
/*         for(int j=0;j<1<<n;j+=(mid<<1)){ */
/*             for(int i=0;i<mid;i++){ */
/*                 if(tp==1)(a[i+j+mid]+=a[i+j])%=mo; */
/*                 else (a[i+j+mid]+=mo-a[i+j])%=mo; */
/*             } */
/*         } */
/*     } */
/* } */
int main(){
    /* freopen("table.in","r",stdin); */
    /* freopen("table.out","w",stdout); */
    int n=1e2,B=sqrt(n)+1;
    euler(n);
    /* scanf("%d",&n); */
    /* int L=(n/B)*B; */
    /* for(int i=L+1;i<=n;i++){ */
	/* int res=cal(i); */
	/* cnt[res-1]++; */
    /* } */
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
	/* if(i%B==0){ */
	/*     cerr<<i<<endl; */
	/*     printf("{"); */
	/*     for(int i=0;i<=30;i++){ */
	/* 	printf("%d",cnt[i]); */
	/* 	if(i!=30)printf(","); */
	/*     } */
	/*     printf("},\n"); */

	/* } */
	cout<<i<<' '<<f[i]<<" "<<res-1<<endl;
    }
}


