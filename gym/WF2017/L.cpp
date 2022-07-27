#include<bits/stdc++.h>
using namespace std;
const int maxn=400001,INF=1e9+5;
struct point{
    int x,y,id;
}a[maxn],b[maxn];
struct comp{
    bool operator ()(point a,point b)const {
	return a.y<b.y;
    };
};
int n,ans[maxn];
pair<int,int>l[maxn];
int idx=0;
void add(int x,int y){
    l[++idx]={x,y};
}
unordered_map<int,vector<pair<int,int>>>ins,del;
vector<int>axis;
int Check(vector<pair<int,int>>&a){
    if(a.empty())return 1;
    sort(a.begin(),a.end());
    for(int i=0;i<a.size()-1;i++){
	if(a[i].second>=a[i+1].first)return 0;
    }
    return 1;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
	int x,y;scanf("%d%d",&x,&y);
	a[i]={x,y,i};
	axis.push_back(x);
    }
    for(int i=1;i<=n;i++){
	int x,y;scanf("%d%d",&x,&y);
	b[i]={x,y,i};
	axis.push_back(x);
    }
    sort(axis.begin(),axis.end());
    axis.erase(unique(axis.begin(),axis.end()),axis.end());
    sort(a+1,a+1+n,[](point a,point b){
		if(a.x!=b.x)return a.x>b.x;
		else return a.y>b.y;
	    });

    sort(b+1,b+1+n,[](point a,point b){
		if(a.x!=b.x)return a.x>b.x;
		else return a.y>b.y;
	    });
    set<point,comp>s;
    for(int i=1,j=1;i<=n;i++){
	/* cout<<"at "<<a[i].x<<" "<<a[i].y<<endl; */
	while(j<=n&&b[j].x>=a[i].x){
	    s.insert(b[j]);
	    /* cout<<"ins "<<b[j].x<<" "<<b[j].y<<endl; */
	    ++j;
	}
	auto p=s.lower_bound(a[i]);
	if(p==s.end()){
	    puts("syntax error");
	    return 0;
	}
	ans[a[i].id]=p->id;
	ins[a[i].x].push_back({a[i].y,p->y});
	del[p->x].push_back({a[i].y,p->y});
	s.erase(p);
	/* cout<<"frame: "<<a[i].x<<' '<<a[i].y<<" "<<p->x<<' '<<p->y<<endl; */
    }
    sort(l+1,l+1+n,[](auto a,auto b){return a.second<b.second;});
    set<int>ns;
    ns.insert(-INF);
    ns.insert(INF);
    auto check=[&](int x,int y){
	/* cout<<"check "<<x<<" "<<y<<endl; */
	/* for(auto v:ns)cout<<v<<" ";cout<<endl; */
	if(!ns.empty()){
	    auto r=ns.upper_bound(y);
	    auto l=prev(ns.lower_bound(x));
	    /* cout<<*l<<" "<<*r<<" "<<distance(l,r)<<endl; */
	    if(distance(l,r)>1){
		return 0;
	    }
	}
	return 1;
    };
    for(auto i:axis){
	/* cout<<endl; */
	/* cout<<"cur: "<<i<<endl; */
	if(!Check(ins[i])||!Check(del[i])){
		puts("syntax error");
		return 0;
	}
	for(auto [x,y]:ins[i]){
	    if(!check(x,y)){
		puts("syntax error");
		return 0;
	    }
	}
	for(auto [x,y]:ins[i]){
	    /* cout<<"ins "<<x<<" "<<y<<endl; */
	    ns.insert(x);ns.insert(y);
	}
	for(auto [x,y]:del[i]){
	    /* cout<<"del "<<x<<" "<<y<<endl; */
	    ns.erase(x);ns.erase(y);
	}
	for(auto [x,y]:del[i]){
	    if(!check(x,y)){
		puts("syntax error");
		return 0;
	    }
	}
    }
    for(int i=1;i<=n;i++){
	printf("%d\n",ans[i]);
    }
}
