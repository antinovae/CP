#include <bits/stdc++.h>
using namespace std;
template <typename T> void read(T &x){
	x = 0; int f = 1; char ch = getchar();
	while (!isdigit(ch)) {if (ch == '-') f = -1; ch = getchar();}
	while (isdigit(ch)) {x = x * 10 + ch - '0'; ch = getchar();}
	x *= f;
}
inline void write(int x){if (x > 9) write(x/10); putchar(x%10+'0'); }

inline void No(){ puts("There is no route, Karl!"),exit(0); }
const int N = 100050;
int n,m,ex[N],ey[N],deg[N]; vector<int>G[N],fG[N];

int nxt[N],lst[N];

int cntid,id[N];
vector<int>p[24],G2[24]; bitset<24>All,vis;

int nxtt[24];
int ansp[N],len;

inline void check(){
	int i,now = 1;
	vis.reset();
	while (!vis[now]) vis[now] = 1,now = nxtt[now];
	if (All != vis) return;
	vis.reset(),now = 1;
	while (!vis[now]){
		for (i = 0; i < p[now].size(); ++i) ansp[++len] = p[now][i];
		vis[now] = 1,now = nxtt[now];
	}
	bool flag = 0;
	for (i = 1; i <= n; ++i) if (ansp[i] == 1 || flag) flag = 1,cout << ansp[i] << ' ';
	flag = 0;
	for (i = 1; i <= n && !flag && ansp[i] != 1; ++i) cout << ansp[i] << ' ';
	cout << "1\n";
	exit(0); 
}

int indeg[24];
inline void dfs(int dep){
	if (dep > cntid){ check(); return; }
	for (int i = 0; i < G2[dep].size(); ++i){
		nxtt[dep] = G2[dep][i];
		if (!indeg[G2[dep][i]]) ++indeg[G2[dep][i]],dfs(dep+1),--indeg[G2[dep][i]];
	}
}

int main(){
	freopen("king.in","r",stdin); freopen("king.out","w",stdout); 
	int i,x,y;
	read(n),read(m);
	for (i = 1; i <= m; ++i){
		read(ex[i]),read(ey[i]);
		G[ex[i]].push_back(ey[i]),fG[ey[i]].push_back(ex[i]);
	}
	for (i = 1; i <= n; ++i) if (!fG[i].size() || !G[i].size()) No();
	for (i = 1; i <= n; ++i) if (G[i].size() == 1){
		x = i,y = G[i][0];
		if (lst[y] && lst[y] != x) No();
		nxt[x] = y,lst[y] = x;
	}
	for (i = 1; i <= n; ++i) if (fG[i].size() == 1){
		x = fG[i][0],y = i;
		if (nxt[x] && nxt[x] != y) No();
		if (lst[y] && lst[y] != x) No();
		nxt[x] = y,lst[y] = x;
	}
	bool flag = 0;
	vector<int>q;
	for (i = 1; i <= n; ++i) if (!id[i]){
		x = i; id[x] = ++cntid; p[id[x]].push_back(x);
		if (cntid > 20) No();
		x = nxt[x];
		while (x){
			if (id[x]){ flag = 1; break; }
			id[x] = cntid,p[id[x]].push_back(x),x = nxt[x];
		}
		if (lst[i] && !id[lst[i]]){
			q = p[id[i]],p[id[i]].clear(),x = lst[i];
			while (x) id[x] = cntid,p[id[i]].push_back(x),x = lst[x];
			reverse(p[id[i]].begin(),p[id[i]].end());
			for (int t = 0; t < q.size(); ++t) p[id[i]].push_back(q[t]);
		}
	}
	if (flag && cntid == 1){
		for (i = 0; i < n; ++i) cout << p[1][i] << ' ';
		cout << "1\n";
		return 0;
	}
	if (flag) No();
	for (i = 1; i <= m; ++i){
		if (id[ex[i]] != id[ey[i]] 
			&& ex[i] == p[id[ex[i]]].back() 
			&& ey[i] == p[id[ey[i]]][0]){
			G2[id[ex[i]]].push_back(id[ey[i]]);
			//cout << id[ex[i]] << ' ' << id[ey[i]] << '\n';
		}
	}
//	cout << cntid << '\n';
	for (i = 1; i <= cntid; ++i) All[i] = 1,vis[i] = 0;
	dfs(1);
	No();
	return 0;
}
