#include<bits/stdc++.h>
using namespace std;
const int maxn=2e6+10,INF=(1<<25);
int pre[maxn],xyx;
struct LCT;
int ans;
struct LCT{
    int n,ch[maxn][2],fa[maxn];
    int len[maxn],slen[maxn],pos[maxn],ptag[maxn];
    pair<int,int>mn[maxn],mn_lim[maxn];
#define ls (ch[x][0])
#define rs (ch[x][1])
    bool nroot(int x){
        return ch[fa[x]][0]==x||ch[fa[x]][1]==x;
    }
    void pushup(int x){
	slen[x]=slen[ls]^len[x]^slen[rs];
	mn[x]=min({mn[ls],mn[rs],{len[x],x}});
	mn_lim[x]=min({mn_lim[ls],mn_lim[rs],{len[x]+pos[x],x}});
    }
    void put_tag(int x,int p){
	ptag[x]=pos[x]=p;
	mn_lim[x]={mn[x].first+p,mn[x].second};
    }
    void pushdown(int x){
        if(ptag[x]){
            put_tag(ch[x][0],ptag[x]),put_tag(ch[x][1],ptag[x]);
            ptag[x]=0;
        }
    }
    void rotate(int x){
        int y=fa[x],z=fa[y],l=x==ch[y][1],r=l^1;
        if(nroot(y)) ch[z][y==ch[z][1]]=x;fa[x]=z;
        ch[y][l]=ch[x][r],fa[ch[x][r]]=y;
        ch[x][r]=y,fa[y]=x;
        pushup(y),pushup(x);
    }
    void push_all(int x){
	if(!x)return;
        if(nroot(x))push_all(fa[x]);
        pushdown(x);
    }
    void splay(int x){
        push_all(x);
        for(;nroot(x);rotate(x)){
            int y=fa[x],z=fa[y];
            if(nroot(y))rotate((x==ch[y][1])!=(y==ch[z][1])?x:y);
        }
    }
    void access(int x){
        for(int y=0;x;y=x,x=fa[x]){
            splay(x);ch[x][1]=y;pushup(x);
	}
    }
    int cal(int l,int r,int v){
	if(v<=l){
	    return pre[r]^pre[l-1];
	}
	else if(v>l&&v<=r){
	    return pre[r]^pre[v-1];
	}
	else return 0;
    }
    void pr(int x){
	/* cout<<x<<" sons "<<ls<<" "<<rs<<" "<<" fa "<<fa[x]<<" len: "<<len[x]<<" "<<slen[x]<<" mn_lim: "<<mn_lim[x].first<<" "<<mn_lim[x].second<<endl; */

    }
    int modify(int x){
	/* cout<<"modify "<<x<<endl; */
	pr(x);
	access(x);splay(x);
	pr(x);
	while(1){
	    splay(x);
	    auto [val,v]=mn_lim[x];
	    if(val<x){
		splay(v);
		len[v]=INF;
		pushup(v);
	    }
	    else break;
	}
	put_tag(x,x);
	int ans=(slen[x]^x)&(INF-1);
	return ans;
    }
}T;
int pi[maxn];
void prev_extend(char s[],int i){
    int j=pi[i-1];
    while(j&&s[i]!=s[j+1])j=pi[j];
    if(s[i]==s[j+1]){
	++j;
    }
    pi[i]=j;
}
char str[maxn];
int n,tp;
signed main(){
    freopen("noname.in","r",stdin);
    freopen("noname.out","w",stdout);
    scanf("%d%d",&n,&tp);
    scanf("%s",str+1);
    for(int i=1;i<=n;i++){
	pre[i]=pre[i-1]^i;
    }
    long long ans=0;
    int lst=0;
    T.len[0]=INF;T.mn[0]=T.mn_lim[0]={INF,0};
    T.pushup(0);
    T.pr(0);
    for(int i=1;i<=n;++i){
	/* cout<<"round "<<i<<endl; */
	if(tp)str[i]=(str[i]+lst)%26+97;
	if(i>1)prev_extend(str,i);
	/* cout<<"	 pi: "<<pi[i]<<endl; */

	/* cout<<"link "<<pi[i]<<" "<<i<<endl; */
	T.fa[i]=pi[i];
	T.len[i]=i;
	T.pushup(i);
	lst=T.modify(i);
	/* cout<<lst<<endl; */
	ans+=lst;
    }
    cout<<ans<<endl;
    /* cout<<xyx<<endl; */
}
