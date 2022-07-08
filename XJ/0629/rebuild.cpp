#include<bits/stdc++.h>
#include "rebuild.h"
using namespace std;
#define cout cerr
bool check(const vector<int> &a){
    for(int i=0;i<a.size();i++)if(a[i]!=i)return false;
    return true;
}

void work(vector<int> &a){
    int n=(int)a.size();
    vector<int>b(n);
    for(auto &v:b)v=-1;
    int idx=-1;
    for(int i=0;i<n;i++){
	if(b[i]==-1){
	    if(a[i]==i)b[i]=++idx;
	    else {
		int j=i;
		while(b[j]==-1&&b[a[j]]==-1){
		    b[a[j]]=b[j]=++idx;
		    j=a[j];j=a[j];
		}
	    }
	}
    }
    for(auto &v:b)if(v==-1)v=++idx;
    /* for(auto v:b)cout<<v<<" ";cout<<endl; */
    /* for(auto v:a)cout<<v<<" ";cout<<endl; */
    a=shuffle(b);
    /* for(auto v:a)cout<<v<<" ";cout<<endl; */
    /* cout<<endl; */
}

void solve(vector<int>a){
    while(!check(a)){
	work(a);
    }
    return;

}


