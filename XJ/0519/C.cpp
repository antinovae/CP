#include<bits/stdc++.h>
using namespace std;
const int maxn=5001,INF=2e9;
char ch[maxn],s[maxn];
int kn,m,p,kl,ac[maxn][4],tot,cnt[maxn],val[maxn],f[2][8][151][151];
int a[maxn],ans,fail[maxn];
void add(char *x,int val){
    int pos=0,len=strlen(x);
    for(int i=0;i<len;i++){
	if(!ac[pos][x[i]-'a'])
	    ac[pos][x[i]-'a']=++kn,pos=kn;
	else pos=ac[pos][x[i]-'a'];
    }
    cnt[pos]+=val;
    return;
}
void prep(){
    for(int i=0;i<=kn;i++){
	int j=i;while(j){
	    val[i]+=cnt[j];
	    j=fail[j];
	}
    }
}
void buildfail(){
    queue<int>fi;
    for(int i=0;i<4;i++)
	if(ac[0][i])fi.push(ac[0][i]);
    while(!fi.empty()){
	int x=fi.front();fi.pop();
	for(int i=0;i<4;i++){
	    if(ac[x][i])fail[ac[x][i]]=ac[fail[x]][i],fi.push(ac[x][i]);
	    else ac[x][i]=ac[fail[x]][i];
	}	
    }
}
int n;
void tr(char *s){
    int n=strlen(s);
    for(int i=0;i<n;i++){
	if(s[i]=='O')s[i]='a';
	if(s[i]=='I')s[i]='b';
	if(s[i]=='L')s[i]='c';
	if(s[i]=='J')s[i]='d';
    }
}
void cmax(int &x,int y){
    y>x?(x=y):x;
}
struct st{
    int s[7],len=0;
    string ch;
    void ins(int x){
	s[len]=x;++len;
	ch+=(char)(x+'a');
    }

}S[141];
int cal(int x,st head){
    int ans=0;
    for(int j=0;j<head.len;j++){
	x=ac[x][head.s[j]];
	/* cout<<x<<" "<<ac[x][head.s[j]]<<' '<<val[x]<<endl; */
	ans+=val[x];
    }
    return ans;
}
int solve(st head){
    memset(f,128,sizeof(f));
    f[0][0][0][0]=0;
    for(int i=1;i<=n;i++){
	int cur=i%2;
	for(int j=0;j<=head.len;j++)
	    for(int x=0;x<=kn;x++)
		for(int y=0;y<=kn;y++)f[cur][j][x][y]=-INF;
	for(int j=0;j<=min(i,head.len);j++){
	    for(int x=0;x<=kn;x++){
		for(int y=0;y<=kn;y++){
		    if(f[cur^1][j][x][y]<0)continue;
		    int v=s[i]-'a';
		    if(j<head.len){
			if(v==head.s[j]){
			    cmax(f[cur][j+1][x][ac[y][v]],f[cur^1][j][x][y]+val[ac[y][v]]);
			     cmax(f[cur][j][ac[x][v]][y],f[cur^1][j][x][y]+val[ac[x][v]]);
			}
			else{
			    cmax(f[cur][j][ac[x][v]][y],f[cur^1][j][x][y]+val[ac[x][v]]); 
			}
		    }
		    else{
			cmax(f[cur][j][ac[x][v]][y],f[cur^1][j][x][y]+val[ac[x][v]]);
			cmax(f[cur][j][x][ac[y][v]],f[cur^1][j][x][y]+val[ac[y][v]]);
		    }
		}
	    }
	}
    }
    for(int i=0;i<=kn;i++)
	for(int j=0;j<=kn;j++){
	    if(f[n%2][head.len][i][j]<0)continue;
	    ans=max(ans,f[n%2][head.len][i][j]+cal(i,head)-cal(0,head));

	}
    return ans;
}
int Scnt;
void split(char *s){
    int n=strlen(s);
    for(int i=0;i<n;i++){
	++Scnt;
	for(int j=i;j<n;j++){
	    S[Scnt].ins(s[j]-'a');
	}
    }
}
int main(){
    freopen("tetr.in","r",stdin);
    freopen("tetr.out","w",stdout);
    scanf("%d%d",&n,&m);
    scanf("%s",s+1);
    tr(s+1);
    while(m--){
	int len,val;
	scanf("%d%d",&len,&val);
	scanf("%s",ch);
	tr(ch);
	split(ch);
	add(ch,val);
    }
    buildfail();
    prep();
    int ans=0,cntt=0;
    sort(S+1,S+1+Scnt,[&](st a,st b){
	    return a.ch<b.ch;
	    });
    int rlen=0;
    for(int i=1;i<=Scnt;i++){
	if(S[i].ch==S[i-1].ch)continue;
	int res=solve(S[i]);
	if(res>ans){
	    ans=res;
	    rlen=S[i].len;
	}
	cntt++;
    }
    /* cout<<rlen<<endl<<cntt<<endl; */

    printf("%d\n",ans);
}
