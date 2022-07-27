#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int n,m,C,col,aff;
int c[maxn],cnt[maxn],op[maxn],mx,se;
vector<int>ans;
inline bool check(int pos){
    --cnt[c[pos]];++cnt[op[1]];
    if(n==1&&op[m]==col)return 1;
    int res=cnt[col]-aff;
    bool ans=cnt[mx]<res&&cnt[se]<res&&(op[1]==col||cnt[op[1]]<res);
    ++cnt[c[pos]];--cnt[op[1]];
    return ans;
}
 
int main(){
    freopen("kabaleo.in","r",stdin);
    freopen("kabaleo.out","w",stdout);
    scanf("%d%d%d%d",&n,&m,&C,&col);
    for(int i=1;i<=n;i++){
	scanf("%d",&c[i]);
	++cnt[c[i]];
    }
    for(int i=1;i<=m;i++)scanf("%d",&op[i]);
    for(int i=2;i<=m;i++){
	if(op[i]!=col)++cnt[op[i]],++aff;
    }
    for(int i=1;i<=C;i++){
	if(i!=col){
	    if(cnt[i]>cnt[mx])se=mx,mx=i;
	    else if(cnt[i]>cnt[se])se=i;
        }
    }
    for(int i=1;i<=n;i++){
	if(check(i)){
	    ans.push_back(i);
	}
    }
    printf("%zu\n",ans.size());
    for(auto v:ans){
	printf("%d ",v);
    }
    return 0;
}
 
