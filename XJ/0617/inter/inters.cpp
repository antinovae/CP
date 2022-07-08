#include<bits/stdc++.h>
using namespace std;
const int N=51,M=1010;
int query(int x,int y);
int n,m;
struct seg{
    int a[M];
    int l,r,pos,mid,id,hv;
    int get(){
	pos=(l+r)/2;
	if(l>r){hv=0;return 0;}
	if(!a[pos])a[pos]=query(id,pos);
	return a[pos];
    }
}t[N];
void init(){
    for(int i=1;i<=n;i++){
	memset(t[i].a,0,sizeof(t[i].a));
	t[i].l=1,t[i].r=m,t[i].id=i,t[i].hv=1;
	t[i].get();
    }
}
void guess(int T,int n,int m,int k) {
    ::n=n;::m=m;
    init();
    while(1){
        int a=0,b=0;
        for(int i=1;i<=n;i++)a+=t[i].pos;
        for(int i=1;i<=n;i++)if(t[i].hv)b=b?-1:i;
        if(a==k&&b>0){
	    printf("%d %d %d\n",t[b].get(),b,t[b].pos);
	    return;
	}
        if(a>k){
            int v=0;
            for(int i=1;i<=n;i++)if(t[i].hv) v=max(v,t[i].get());
            for(int i=1;i<=n;i++)if(t[i].hv && v==t[i].get()){t[i].r=t[i].pos-1,t[i].get();break;}
        }
        else{
            int v=2e9;
            for(int i=1;i<=n;i++)if(t[i].hv) v=min(v,t[i].get());
            for(int i=1;i<=n;i++)if(t[i].hv && v==t[i].get()){t[i].l=t[i].pos+1,t[i].get();break;}
        }
    }
}
