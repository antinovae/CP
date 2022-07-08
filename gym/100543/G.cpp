#include<bits/stdc++.h>
using namespace std;
const int maxn=100005,INF=1e9;
int fail[maxn][18],fa[maxn],ch[maxn][4],tot=2,len[maxn],p=1,val[maxn],mn[maxn];
char s[maxn];
int id[100];
void init(int n){
    for(int i=1;i<=tot;i++){
	fail[i][0]=fa[i]=len[i]=val[i]=mn[i]=0;
	for(int j:{0,1,2,3})ch[i][j]=0;
    }
    fail[2][0]=1;
    len[1]=-1;
    p=1;
    tot=2;
}
void pr(){
    /* for(int i=1;i<=tot;i++){ */
    /* cout<<i<<" len "<<len[i]<<" fail "<<fail[i][0]<<endl; */
    /* } */
}
void trans(int x){
    /* cout<<len[7]<<endl; */
    /* cout<<"tr "<<x<<" len "<<len[x]<<" "<<fa[x]<<" "<<val[fa[x]]<<endl; */
    for(int k=1;k<=17;k++){
	fail[x][k]=fail[fail[x][k-1]][k-1];
    }
    int p=x;
    for(int k=17;k>=0;k--){
	if(len[fail[p][k]]*2>len[x])p=fail[p][k];
    }
    /* cout<<p<<" "<<len[p]<<endl; */
    p=fail[p][0];
    /* cout<<p<<" "<<len[p]<<endl; */
    if(len[x]%2==1){
	val[x]=0;
	mn[x]=mn[fail[x][0]];
    }
    else if(len[x]==2){
	val[x]=2;
	mn[x]=min(val[x],mn[fail[x][0]]);
    }
    else{
	int res=mn[p]+1+len[x]/2;
	val[x]=min(val[fa[x]]-1,res-len[x]);
	mn[x]=min(val[x],mn[fail[x][0]]);
    }
}
void extend(int pos){
    int x=id[(int)s[pos]];
    while(s[pos-len[p]-1]!=s[pos])p=fail[p][0];
    if(ch[p][x])p=ch[p][x];
    else{
	int cur=++tot;
	ch[p][x]=cur;fa[cur]=p;
	len[cur]=len[p]+2;
	if(p==1)fail[cur][0]=2;
	else{
	    p=fail[p][0];
	    while(s[pos-len[p]-1]!=s[pos])p=fail[p][0];
	    /* cout<<"fail cur= "<<ch[p][x]<<" "<<len[ch[p][x]]<<endl; */
	    fail[cur][0]=ch[p][x];
	}
	trans(cur);
	p=cur;
    }
}
void _main(){
    scanf("%s",s+1);
    int n=strlen(s+1);
    int ans=n;
    init(n);
    pr();
    for(int i=1;i<=n;i++){
	/* cout<<"round "<<i<<endl; */
	extend(i);
	/* cout<<len[p]<<" v "<<val[p]<<" "<<len[p]+val[p]<<endl; */
	pr();
	ans=min(ans,n+val[p]);
    }
    printf("%d\n",ans);
}
int main(){
    id[(int)'A']=0;id[(int)'C']=1;id[(int)'G']=2;id[(int)'T']=3;
    int T;
    scanf("%d",&T);
    for(int t=1;t<=T;t++){
	_main();

    }

}
