#include <bits/stdc++.h>
#define ru(i, l, r) for (int i = l; i <= r; i++)
#define rd(i, r, l) for (int i = r; i >= l; i--)
#define maxn 405
#define pb push_back
using namespace std;
int n, m, a[maxn][maxn], k, x, y, c;
int vis[maxn][maxn];
int stx[maxn * maxn], sty[maxn * maxn], h, t;
mt19937 rnd(0);
int main()
{
	/* freopen("checker.out", "w", stdout); */
	freopen("language.in", "r", stdin);
	scanf("%d%d", &n, &m);
	ru(i, 1, n) ru(j, 1, n) {
	    cin>>a[i][j];
	    /* a[i][j]=rnd()%n+1; */
	}
	freopen("language.out", "r", stdin);
	scanf("%d", &k);
	cout<<k<<endl;
	if(k > m) {printf("Queries Exceed"); return 0;}
	while(k--)
	{
		scanf("%d%d%d", &x, &y, &c); int c2 = a[x][y];
		stx[1] = x, sty[1] = y; vis[x][y] = h = t = 1;
		while(h <= t)
		{
			int x = stx[h], y = sty[h]; h++;
			a[x][y] = c;
			if(!vis[x - 1][y] && a[x - 1][y] == c2) vis[x - 1][y] = 1, t++, stx[t] = x - 1, sty[t] = y;
			if(!vis[x][y - 1] && a[x][y - 1] == c2) vis[x][y - 1] = 1, t++, stx[t] = x, sty[t] = y - 1;
			if(!vis[x + 1][y] && a[x + 1][y] == c2) vis[x + 1][y] = 1, t++, stx[t] = x + 1, sty[t] = y;
			if(!vis[x][y + 1] && a[x][y + 1] == c2) vis[x][y + 1] = 1, t++, stx[t] = x, sty[t] = y + 1;
		}
		ru(i, 1, n) ru(j, 1, n) vis[i][j] = 0;
	}
	for(int i=1;i<=n;i++){
	    for(int j=1;j<=n;j++){
		cout<<a[i][j]<<" ";
	    }
	    cout<<endl;
	}
	ru(i, 1, n) ru(j, 1, n) if(a[i][j] != 1) {printf("Wrong Answer"); return 0;}
	printf("Accepted");
	return 0;
}
