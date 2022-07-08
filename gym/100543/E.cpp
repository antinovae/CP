#include<bits/stdc++.h>
using namespace std;
const int maxn=1001;
int n,a[maxn];
int f[maxn][1<<14],indec;
tuple<int,int,int>pre[maxn][1<<14];
void pr(int x,int y){
    if(x==0)return;
    auto [_x,_y,t]=pre[x][y];
    pr(_x,_y);
    if(t)putchar('r');
    else putchar('l');
}
void _main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
	scanf("%d",&a[i]);
    }
    int sum=0;
    f[0][0]=indec;
    for(int i=1;i<=n;i++){
	for(int j=0;j<=sum;j++){
	    if(f[i-1][j]){
		cout<<i-1<<" "<<j<<" "<<endl;
	    }
	    if(!((a[i]-1)&j)&&f[i-1][j]==indec){
		f[i][j+a[i]]=f[i-1][j];
		pre[i][j+a[i]]={i-1,j,0};
	    }
	    if(!((a[i]-1)&(sum-j))&&f[i-1][j]==indec){
		/* int p1=j?31-__builtin_clz(j):-1; */
		int p2=(sum-j+a[i])?31-__builtin_clz(sum-j+a[i]):-1;
		if(1<<(p2+1)>=j){
		    f[i][j+(1<<p2)]=f[i-1][j];
		    pre[i][j+(1<<p2)]={i-1,j,1};
		}
		else{
		    f[i][j]=f[i-1][j];
		    pre[i][j]={i-1,j,1};
		}
	    }
	}
	sum+=a[i];
    }
    if(f[n][sum]!=indec||__builtin_popcount(sum)!=1)puts("no");
    else pr(n,sum),puts("");
}
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
	++indec;
	_main();
    }
}
