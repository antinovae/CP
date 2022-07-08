#include"graph.h"
#include<bits/stdc++.h>
using namespace std;
mt19937 rnd(time(0));
const int maxn=100001;
unordered_map<int,int>reso[maxn];
int Query(int x,int y){
    if(reso[x].find(y)==reso[x].end()){
	int ans=query(x,y);
	reso[x][y]=ans;reso[y][x]=ans^1;
	return ans;
    }
    else return reso[x][y];
}
int DAG(int n){
    vector<int>cur;
    for(int i=1;i<=n;i++)cur.push_back(i);
    shuffle(cur.begin(),cur.end(),rnd);
    /* for(auto v:cur)cout<<v<<endl; */
    while(cur.size()>1){
	int x=cur.back();
	cur.pop_back();
	vector<int>nxt;
	for(auto v:cur){
	    if(Query(x,v))nxt.push_back(v);
	}
	if(nxt.empty())return x;
	cur=nxt;
    }
    /* cout<<cur[0]<<endl; */
    return cur[0];
}
unordered_map<int,int>mp[maxn];
set<int>v[3];
int id[maxn];
int gornd(int n){
    for(int i=1;i<=n;i++)id[i]=i;
    shuffle(id+1,id+1+n,rnd);
    for(int i=1;i<=n;i++)v[0].insert(id[i]);
    for(int i:{0,1}){
	while(!v[i].empty()){
	    int x=*v[i].begin();
	    int res=[&]{
	    for(int j=i;j<=2;j++)
		for(auto u:v[j]){
		    if(x!=u&&mp[x].find(u)==mp[x].end()){
			mp[u][x]=mp[x][u]=1;
			if(Query(x,u)==1){
			    if(i<2)v[i+1].insert(x),v[i].erase(x);
			    return 0;
			}
			else{
			    if(j<2)v[j+1].insert(u),v[j].erase(u);
			    return 0;
			}
		    }
		}
		return x;
	    }();
	    if(res!=0)return x;
	}
    }
    return 0;
}
int find(int n,int type) {
    if(type==1){
	int x=DAG(n);
	for(int i=1;i<=n;i++){
	    if(i!=x)Query(x,i);
	}
	return x;
    }
    else return gornd(n);
}

