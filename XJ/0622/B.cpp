#include<bits/stdc++.h>
using namespace std;
const int maxn=2001;
int n,m,x[maxn],y[maxn],col[maxn],idx;
bitset<maxn>s,a[maxn];
void oper(){
    for(int i=1;i<=n;i++){
	if(!s[i]){
	    if((a[i]&s).count()>=2){
		s[i]=1;
	    }
	}
    }
}
int solve(int x,int y){
    s=bitset<maxn>();
    s[x]=1;s[y]=1;
    cout<<"solve "<<x<<" "<<y<<endl;
    cout<<(x&y)<<endl;
    for(int i=1;i<=n;i++){
	if(s.count()<n)oper();
    }
    for(int i=1;i<=n;i++){
	if(s[i])col[i]=idx;
    }
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
	scanf("%d%d",&x[i],&y[i]);
	a[x[i]][y[i]]=1;
	a[y[i]][x[i]]=1;
    }
    for(int i=1;i<=n;i++){
	for(int j=i+1;j<=n;j++){
	    if(a[i][j]&&(a[i]&a[j]).count()){
		cout<<"yes "<<i<<" "<<j<<endl;
	    }
	}
    }
    for(int i=1;i<=m;i++){
	if(!col[x[i]]&&!col[y[i]]){
	    ++idx;
	    solve(x[i],y[i]);	
	}
    }
    /* puts("No"); */

}
