#include<bits/stdc++.h>
const int maxn=1001;
#define ull unsigned long long
using namespace std;
int n,T,k,l,b[maxn],r;
ull p,a[maxn],cur;
struct asuka{
    int v,l,r;
};

int cnt=0,brk=0;
int check(){
    if(cur!=p)return 0;
    cout<<cur<<endl;
    for(int i=1;i<=n;i++)cout<<b[i]<<" ";cout<<endl;
    if(cnt>=k&&brk<=k&&cur==p){
	puts("YES");
	for(int i=1;i<=n;i++){
	    if(b[i]==0){
		if(l){
		    printf("%d %d\n",l,r);
		}
	    }
	    else{
		if(brk<k){
		    brk++;
		    printf("%d %d\n",i,i);
		}
		else{
		    if(b[i-1]==0)l=r=i;
		    else r=i;
		}
	    }
	}
	if(l){
	    printf("%d %d\n",l,r);
	}
    }
    return 0;
}
int dfs(int pos){
    if(pos>n){
	puts("NO");
	return 1;
    }
    if(check()){
	return 1;
    }
    b[pos]=1;cnt++;
    if(b[pos-1]==0)brk++;
    cur^=a[pos];if(dfs(pos+1))return 1;

    b[pos]=0;cnt--;
    if(b[pos-1]==0)brk--;
    cur^=a[pos];if(dfs(pos+1))return 1;
}
void solve(){
    scanf("%d%d%llu",&n,&k,&p);
    for(int i=1;i<=n;i++){
	scanf("%d",&a[i]);
    }
    dfs(1);
}
int main(){
    scanf("%d",&T);
    while(T--){
	solve();
    }
}
