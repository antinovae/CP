#include <bits/stdc++.h>
using namespace std;
const int N=410;
vector<tuple<int,int,int>>ans;
int n,a[N][N],m;
void push(int x, int y, int z) {
    ans.push_back({x,y,z});
    a[x][y]=z;
}
mt19937 rnd(0);
void brute(){
    int x,y;
    for(int i=1;i<=n;i++){
	for(int j=1;j<=n;j++){
	    if(a[i][j]==1)x=i,y=j;
	}
    }
    for(int i=1;i<=n;i++){
	for(int j=1;j<=n;j++){
	    push(i,j,a[x][y]);
	}
    }
    printf("%zu\n",ans.size());
    for(auto &[x,y,z]:ans){
	printf("%d %d %d\n",x,y,z);
    }
}
int main() {
    /* freopen("language.in","r",stdin); */
    /* freopen("language.out","w",stdout); */
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
	for(int j=1;j<=n;j++){
	    scanf("%d",&a[i][j]);
	}
    }
    if(n<=25){
	brute();
	return 0;
    }
    int b=(sqrt(n)+1)/2,step=(n+b-1)/b;
    for(int i=(step+1)/2;i<=n;i+=step){
	for(int j=1;j<=n;j++){
	    if(a[i][j]!=n)push(i,j,n);
	}
    }
    for(int i=1;i<=n;i++){
	if(a[i][1]!=n)push(i,1,n);
    }
    while(ans.size()+n<=m){
	for(int i=n;i>=1;i--)push(1,1,i);
    }
    printf("%zu\n",ans.size());
    for(auto &[x,y,z]:ans){
	printf("%d %d %d\n",x,y,z);
    }
    return 0;
} 
