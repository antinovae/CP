#include<cstdio>
#include<algorithm>
#include<cctype>
#include<vector>
#include<assert.h>
#define pb push_back
using namespace std;
typedef long long ll;
#define G getchar()
inline ll read()
{
	ll x=0; bool flg=false; char ch=G;
	for (;!isdigit(ch);ch=G) if (ch=='-') flg=true;
	for (;isdigit(ch);ch=G) x=(x<<3)+(x<<1)+(ch^48);
	return flg?-x:x;
}
#undef G
const int U=2500;
const ll INF=1.5e18;

int prm[2510]; bool vis[2510];
ll f[2510][380],g[2510][380];
int w[380];

ll A,B; ll C=-1,D=0;  //C real begin; D numbers before current
char s[1<<18]; int top;
vector<int> T;
void print(int x){
	if (x>9) print(x/10);
	s[++top]=(x%10)^48;
}
void dfs(int x,int y,int W){
	ll E;
	if (g[x][y]+1.0*W*f[x][y]>INF) E=INF;
	else E=g[x][y]+W*f[x][y];
	if (!E) return;
	if (D+E<A){
		D+=E;
		return;
	}
	if (!x){
		if (!~C) C=D;
		s[++top]='[';
		for (const int &x: T){
			print(x);
			if (x==T.back()) s[++top]=']',s[++top]=',',s[++top]=' ';
			else s[++top]=',',s[++top]=' ';
		}
		D+=E;
		return;
	}
	T.pb(prm[y]);
	dfs(x-prm[y],y+1,W+w[y]);
	T.pop_back();
	if (D>=B) return;
	dfs(x,y+1,W);
}

int main()
{

	for (int i=2;i<=U;i++){
		if (!vis[i]) prm[++*prm]=i;
		for (int j=1;j<=*prm&&i*prm[j]<=U;j++){
			vis[i*prm[j]]=1;
			if (i%prm[j]==0) break;
		}
	}
	//printf("tot %d\n",*prm);  //367
	for (int i=1;i<=368;i++) f[0][i]=1;
	for (int i=1;i<=367;i++){
		int &t=w[i]; t=2;
		for (int s=prm[i];s;s/=10,t++);
	}
	for (int i=1;i<=U;i++){
		for (int j=367;j;j--){
			int x=prm[j];
			if (x>i) continue;
			f[i][j]=min(INF,f[i][j+1]+f[i-x][j+1]);
			g[i][j]=min(INF,g[i][j+1]+g[i-x][j+1]+f[i-x][j+1]*w[j]);
		}
	}
	
	A=read(),B=read();
	for (int i=2;i<=U&&D<B;i++) dfs(i,1,2);
	
	assert(~C);
	for (ll i=A;i<=B;i++) putchar(s[i-C]);
	putchar(10);
	
	return 0;
}
