#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cassert>
#include <cmath>
#include "still.h"
using namespace std;
namespace Grader{
	int T,tid,n,x,lim,u[200005],v[200005],first[100005],nxt[200005];
	int query_cnt;
	vector<int> _u,_v;
	int book[100005];
	long long dfs(int now,int f,int d){
		long long ans=0;
		if (book[now]==1)ans+=d;
		for (int i=first[now];i;i=nxt[i])
			if (v[i]!=f)ans+=dfs(v[i],now,d+1);
		return ans;
	}
	long long query(int L,vector<int> S){
		++query_cnt;
		if (query_cnt>4*lim){
				printf("Too many queries (testcase %d)\n",tid);
				exit(0);
			}
		if (S.size()!=L){
			printf("Invalid query format (testcase %d) :　The size of S is not L\n",tid);
			exit(0);
		}
		long long ans=0;
		for (int i=0;i<L;i++){
			if (S[i]<1||S[i]>n){
				printf("Invalid query format (testcase %d) : S is not a subset of [1,n]\n",tid);
				exit(0);
			}
			if (book[S[i]]==1){
				printf("Invalid query format (testcase %d) : S contains repeat elements\n",tid);
				exit(0);
			}
			book[S[i]]=1;
		}
		ans=dfs(x,0,0);
		for (int i=0;i<L;i++)book[S[i]]=0;
		return ans;
	}
	int main(){
		scanf("%d%d",&T,&lim);
		int mx=0;
		while((++tid)<=T){
			scanf("%d%d",&n,&x);
			for (int i=1;i<n;i++){
				scanf("%d%d",&u[i],&v[i]);
				nxt[i]=first[u[i]],first[u[i]]=i;
				u[i+n]=v[i],v[i+n]=u[i];
				nxt[i+n]=first[u[i+n]],first[u[i+n]]=i+n;
			}
			query_cnt=0;
			_u.clear(),_v.clear();
			for (int i=1;i<n;i++)_u.push_back(u[i]),_v.push_back(v[i]);
			cout<<"test tid "<<tid<<" start: "<<endl;
			int ans=solve(n,lim,_u,_v);
			if (ans!=x){
				printf("Wrong answer (testcase %d) : Expected %d Found %d\n",tid,x,ans);
				exit(0);
			}
			else mx=max(mx,query_cnt),printf("The answer is right (testcase %d) : Used %d queries\n",tid,query_cnt);
			memset(first,0,sizeof(int)*(n+1));
			memset(nxt,0,sizeof(int)*(2*n+1));
		}
		printf("All right : Maximum number of queries you have used %d\n",mx);
		return 0;
	}
}
long long query(int L,vector<int> S){
	return Grader::query(L,S);
}
int main(){
	Grader::main();
	return 0;
}
