#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e5+10,inf=1e9;
int pre[maxn];
struct SAM{
    int last=1,tot=1;
    int ch[maxn][26],fa[maxn],len[maxn],idx[maxn],epos[maxn],mx[maxn];
    void upd(int y,int cur_pos,int &ans){
	if(y){
	    mx[y]=max(mx[y],cur_pos-epos[y]);
	    epos[y]=max(epos[y],cur_pos);
	    upd(fa[y],cur_pos,ans);
		int r=len[y];
		int l=max(len[fa[y]],mx[y]-1);
		if(l<r){
		    ans^=(pre[r]^pre[l]);
		}
	}
    }
    void extend(int c,int p,int &ans){
        int x=last,cur=last=++tot;
        len[cur]=len[x]+1,idx[p]=cur;
	mx[cur]=epos[cur]=p;
        for(;x&&!ch[x][c];x=fa[x]) ch[x][c]=cur;
        if(!x){
	    fa[cur]=1;return;
	}
        int y=ch[x][c];
        if(len[y]==len[x]+1){
	    fa[cur]=y;
	    upd(y,p,ans);
	    return;
	}
        int clone=++tot;
        copy(ch[y],ch[y]+26,ch[clone]);
        fa[clone]=fa[y],len[clone]=len[x]+1;epos[clone]=epos[y],mx[clone]=mx[y];
        fa[cur]=fa[y]=clone;
	upd(clone,p,ans);
        for(;ch[x][c]==y;x=fa[x]) ch[x][c]=clone;
    }
    int cal(int p){
	int ans=0;
	for(int i=1;i<=tot;i++){
	    /* cout<<i<<" fa: "<<fa[i]<<" epos "<<epos[i]<<" mx "<<mx[i]<<" len "<<len[i]<<endl; */
	    if(epos[i]==p){
		int r=len[i];
		int l=max(len[fa[i]],mx[i]-1);
		if(l<r){
		    ans^=(pre[r]^pre[l]);
		    /* cout<<"add "<<l+1<<" "<<r<<"  "<<ans<<endl; */
		}
	    }
	}
	return ans^p;
    }
}S;
char str[maxn];
int n,tp;
signed main(){
    scanf("%lld%lld",&n,&tp);
    scanf("%s",str+1);
    for(int i=1;i<=n;i++){
	pre[i]=pre[i-1]^i;
    }
    int ans=0;
    for(int i=1;i<=n;++i){
	int res=0;
	S.extend(str[i]-'a',i,res);
	ans+=res;
	cout<<res<<endl;
    }
    cout<<ans<<endl;
}
