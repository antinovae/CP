#include<bits/stdc++.h>
using namespace std;
const int maxn=20;
int w[maxn];
int f[1<<20];
int main(){
    /* freopen("npc.in", "r", stdin); */
    /* freopen("npc.out", "w", stdout); */
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
	int x,y;scanf("%d%d",&x,&y);
	w[x]|=(1<<(y-1));
	w[y]|=(1<<(x-1));
    }
    for(int i=1;i<(1<<n);i++)
	for(int j=0;j<n;j++)
	    if(i>>j&1){
		f[i]=max(f[i^(1<<j)],f[i&w[j+1]]+1);
		break;
	    }
    for(int i=1;i<(1<<n)-1;i++)
	if(f[i]==f[(1<<n)-1^i]){
	    printf("%d\n",__builtin_popcount(i));
	    for(int j=0;j<n;j++){
		if(i>>j&1)printf("%d ",j+1);
	    }
	    puts("");
	    printf("%d\n",__builtin_popcount((1<<n)-1^i));
	    for(int j=0;j<n;j++){
		if((((1<<n)-1)^i)>>j&1)printf("%d ",j+1);
	    }
	    puts("");
	    return 0;
	}
    printf("0\n0\n");
    return 0;
} 
