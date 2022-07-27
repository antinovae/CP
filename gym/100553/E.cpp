#include<bits/stdc++.h>
using namespace std;
const int maxn=1000001;
int n,st[maxn],tr[maxn][3],my_st[maxn],my_tr[maxn][3];
char s[3];
int indec;
int new_node(int x){
    ++indec;
    my_st[indec]=x;
    return indec;
}
int make_beat(int x){
    int k=0,pos=indec;
    for(int i=1;i<=n;i++){
	int j=new_node((st[i]+1)%3);
	if(i==x)k=j;
	/* cout<<"my_st "<<j<<" "<<my_st[j]<<endl; */
	my_tr[j][st[i]]=tr[i][my_st[j]]+pos;
	/* cout<<"my_tr "<<j<<" "<<st[i]<<" -> "<<tr[i][my_st[j]]<<" "<<my_tr[j][st[i]]<<endl; */
    }
    return k; 
}


void solve(int x,vector<int>s,int step){
    /* cout<<"solve: "<<x<<" "<<step<<endl; */
    /* for(auto v:s)cout<<v<<" ";cout<<endl; */
    if(step>n){
	/* cout<<"beating! "<<endl; */
	int v=tr[st[s.back()]][my_st[x]];
	my_tr[x][st[s.back()]]=make_beat(v);
	return;
    }
    vector<int>t[3];
    for(auto v:s){
	t[st[v]].push_back(tr[v][my_st[x]]);
    }
    for(int i=0;i<3;i++){
	if(t[i].empty())continue;
	sort(t[i].begin(),t[i].end());
	t[i].erase(unique(t[i].begin(),t[i].end()),t[i].end());
	int v=new_node((i+1)%3);
	my_tr[x][i]=v;

	if(s.size()==t[i].size())solve(v,t[i],step+1);
	else solve(v,t[i],0); 
    }
}
char c[3]={'R','P','S'};
int main(){
    freopen("epic.in","r",stdin);
    freopen("epic.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
	scanf("%s",s);
	if(s[0]=='R')st[i]=0;
	else if(s[0]=='P')st[i]=1;
	else st[i]=2;
	for(int j=0;j<3;j++)scanf("%d",&tr[i][j]);
    }
    vector<int>s;
    for(int i=1;i<=n;i++){
	s.push_back(i);
    }
    ++indec;solve(1,s,0);
    ++indec;
    printf("%d\n",indec);
    for(int i=1;i<=indec;i++){
	printf("%c ",c[my_st[i]]);
	for(int j=0;j<3;j++){
	    if(!my_tr[i][j])my_tr[i][j]=indec;
	    printf("%d ",my_tr[i][j]);
	}
	puts("");
    }

}
