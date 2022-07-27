#include<bits/stdc++.h>
using namespace std;
const int maxn=1000001;
vector<int>s[3];
struct frame{
    int c[3][2];
    void in(){
	for(int j:{0,1})for(int i:{0,1,2}){
	    scanf("%d",&c[i][j]);
	    s[i].push_back(c[i][j]);
	}
    }
    void rein(){
	for(int j:{0,1})for(int i:{0,1,2}){
	    c[i][j]=lower_bound(s[i].begin(),s[i].end(),c[i][j])-s[i].begin()+1;
	}
    }
}t[maxn];
vector<frame>a[3];
int check(int d1,int d2){
    int d;
    for(int j:{0,1,2})if(j!=d1&&j!=d2)d=j;
    int mn=s[d2].size()+1,mx=0;
    vector<int>p(s[d].size()+3);
    for(auto v:a[d2]){
	mn=min(mn,v.c[d2][0]);
	mx=max(mx,v.c[d2][0]);
	p[v.c[d][0]]++;
	p[v.c[d][1]]++;
    }
    for(int i=1;i<p.size();i++)p[i]+=p[i-1];
    for(auto v:a[d1]){
	if(min(v.c[d2][0],v.c[d2][1])>=mn||max(v.c[d2][0],v.c[d2][1])<=mx)return 0;
	if(p[max(v.c[d][0],v.c[d][1])]-p[min(v.c[d][0],v.c[d][1])-1]<a[d2].size())return 0;
    }
    return 1;
}
int n;
void _main(){
    scanf("%d",&n);
    for(int i:{0,1,2}){
	a[i].resize(0);s[i].resize(0);
    }
    for(int i=1;i<=n;i++)t[i].in();
    for(int i:{0,1,2})sort(s[i].begin(),s[i].end()),s[i].erase(unique(s[i].begin(),s[i].end()),s[i].end());
    for(int i=1;i<=n;i++){
	t[i].rein();
	for(int j:{0,1,2})
	    if(t[i].c[j][0]==t[i].c[j][1])
		a[j].push_back(t[i]);
    }
    int ans=0;
    int cnt=(!a[0].empty())+(!a[1].empty())+(!a[2].empty());
    if(cnt==1){
	puts("NO");
	return;
    }
    else if(cnt==2){
    for(int i=0;i<3;i++)
	for(int j=i+1;j<3;j++)
	    if(!a[i].empty()&&!a[j].empty()){
		if(check(i,j)&&check(j,i))puts("YES");
		else puts("NO");
		return;
	    }
    }
    else{
	for(int i=0;i<3;i++){
	    for(int j=i+1;j<3;j++){
		ans+=(check(i,j)&&check(j,i));
	    }
	}
	if(ans>=2)puts("YES");
	else puts("NO");
    }
}
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
	_main();
    }
}
