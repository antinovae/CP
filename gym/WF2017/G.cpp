#include<bits/stdc++.h>
using namespace std;
const int N=305;
int n,m;
array<array<int,N>,N>a,b,c;
char str[N];
pair<int,int>calc(){
    b=a;
    c.fill(array<int,N>{0});
    int x=0,y=0;
    for(int i=1;i<=n&&!x;++i)
	for(int j=1;j<=m;++j)
	    if(b[i][j]){
		if(i>=n-1||j>=m-1){x=i;break;}
		c[i+1][j+1]=1;
		for(int k=i;k<i+3;++k)
		    for(int l=j;l<j+3;++l)
			b[k][l]^=1;
	    }
    if(!x)return {x,y};
    b=a;
    for(int j=1;j<=m&&!y;++j)
	for(int i=1;i<=n;++i)
	    if(b[i][j]){
		if(i>=n-1||j>=m-1){y=j;break;}
		for(int k=i;k<i+3;++k)
		    for(int l=j;l<j+3;++l)
			b[k][l]^=1;
	    }
    return {x,y};
}
bool work(){
    int tot=0;
    for(int i=1;i<=n;++i)
	for(int j=1;j<=m;++j)
	    tot+=a[i][j];
    if(tot==1)return false;
    pair<int,int>p1=calc(),p2={0,0};
    if(p1.first)a[p1.first][p1.second]^=1,p2=calc();
    if(!p2.first){
	a=c;
	return true;
    }
    if(p1.first)a[p1.first][p1.second]^=1;
    return false;
}
int main(){
    scanf("%d%d",&m,&n);
    for(int i=1;i<=n;i++){
	scanf("%s",str+1);
	for(int j=1;j<=m;++j)
	    a[i][j]=str[j]=='#';
    }
    while(work());
    int u=n,d=1,l=m,r=1;
    for(int i=1;i<=n;++i)
	for(int j=1;j<=m;++j)
	    if(a[i][j])
		u=min(u,i),d=max(d,i),l=min(l,j),r=max(r,j);
    for(int i=u;i<=d;++i,puts(""))
	for(int j=l;j<=r;++j)
	    putchar(a[i][j]?'#':'.');
    return 0;
}
