#include<bits/stdc++.h>
using namespace std;
const int maxn=1000001;
int n,m;
#define mat vector<pair<int,int>>
mat a,b,c;
int check(mat s1,mat s2){
    if(s1.size()!=s2.size())return 0;
    for(int i=0;i<s1.size();i++){
	if(s1[i].first-s1[0].first!=s2[i].first-s2[0].first)return 0;
	if(s1[i].second-s1[0].second!=s2[i].second-s2[0].second)return 0;
    }
    return 1;
}
char s[maxn];
void in(mat &a){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
	scanf("%s",s+1);
	for(int j=1;j<=m;j++){
	    if(s[j]=='*')a.push_back({i,j});
	}
    }
    sort(a.begin(),a.end());
}
mat merge(const mat &a,const mat &b){
    mat c;
    for(int i=0,j=0;i<a.size()||j<b.size();){
	if(i<a.size()&&(j==b.size()||a[i]<b[j]))c.push_back(a[i]),++i;
	else if(j<b.size()&&(i==a.size()||a[i]>b[j]))c.push_back(b[j]),++j;
	else if(i<a.size()&&j<b.size()&&a[i]==b[j])i++,j++;
    }
    return c;
}
mat move(mat a,int x,int y){
    for(int i=0;i<a.size();i++){
	a[i].first+=x;
	a[i].second+=y;
    }
    return a;
}
int fl;
void solve(){
    int x=a[0].first-c[0].first;
    int y=a[0].second-c[0].second;
    mat e=move(c,x,y);
    mat d=merge(a,e);
    if(check(b,d)){
	puts("YES");
        if(!fl)cout<<d[0].second-b[0].second<<" "<<d[0].first-b[0].first<<endl;
	else cout<<b[0].second-d[0].second<<" "<<b[0].first-d[0].first<<endl;
	exit(0);
    }
}
void psolve(){
    int x=a[0].first-b[0].first;
    int y=a[0].second-b[0].second;
    mat e=move(b,x,y);
    mat d=merge(a,e);
    if(check(c,d)){
	puts("YES");
	cout<<y<<" "<<x<<endl;
	exit(0);
    }
}
int main(){
    freopen("kids.in","r",stdin);
    freopen("kids.out","w",stdout);
    in(a);in(b);in(c);
    if(a.empty()&&b.empty()){
	if(c.empty())puts("YES"),puts("0 0");
	else puts("NO");
    }
    if(a.empty()){
	if(check(b,c)){
	    puts("YES");
	    cout<<c[0].second-b[0].second<<" "<<c[0].first-b[0].first<<endl;
	}
	else puts("NO");
	
    }
    else if(b.empty()){
	if(check(a,c))
	    puts("YES"),puts("0 0");
	else puts("NO");
    }
    else{
	psolve();
	solve();
	swap(a,b);fl=1;
	solve();
	puts("NO");
    }
}
