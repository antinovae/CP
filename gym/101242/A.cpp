#include<bits/stdc++.h>
const int maxn=1e6+5;
#define int long long
using namespace std;
int a[maxn],c[maxn];
int n,m,sum;
int calc(int x){return (1ll*sum*(c[x]+1)+a[x]-1)/a[x];}
struct cmp{
    bool operator ()(int x,int y){return calc(x)>calc(y);}
};
priority_queue<int,vector<int>,cmp>q;
signed main(){
    scanf("%lld%lld",&n,&m);
    if(n==1||m==0){
	puts("forever");
	return 0;
    }
    for(int i=1;i<=n;i++){
	scanf("%lld",&a[i]),sum+=a[i];
    }
    for(int i=1;i<=m;i++){
	int x;scanf("%lld",&x);
	c[x]++;
    }
    for(int i=1;i<=n;i++){
        if(calc(i)<=m){
	    puts("0");return 0;
	}
        q.push(i);
    }
    for(int i=1;i<=sum;i++){
        int x=q.top();q.pop();
        if(calc(q.top())<=i+m){
	    printf("%lld\n",i-1);
	    return 0;
	}
        ++c[x];q.push(x);
    }
    puts("forever");
    return 0;
}
