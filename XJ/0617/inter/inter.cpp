#include<bits/stdc++.h>
using namespace std;
int query(int x,int y);
int n,m;
int INF=1e9+5;
int flag;
struct row{
    int a[1005];
    int l,r,pos,mid;
    pair<int,int>div(){
	if(l>r)return {-1,-1};
	mid=(l+r)/2;
	if(!a[mid])a[mid]=query(pos,mid),flag++;
	return {a[mid],mid};
    }
    void modify(int x){
	if(x==1){
	    l=mid+1;
	    mid=(l+r)/2;

	}
	else {
	    r=mid-1;
	    mid=(l+r)/2;
	}
    }
}t[55];
void init(){
    flag=0;
    for(int i=1;i<=n;i++){
	t[i].l=1,t[i].r=m,t[i].pos=i,t[i].mid=-1;
    }
}
mt19937 rnd(time(0));
void guess(int num_testcase,int n,int m,int K){
    ::n=n;::m=m;
    init();
    tuple<int,int,int>res;
    for(int i=0;i<=20;i++){
	pair<int,int>mn={INF,-1},mx={0,-1};
	int mx_sum=0,mn_sum=0;
	for(int i=1;i<=n;i++){
	    auto [val,cnt]=t[i].div();
	    cout<<"is "<<val<<" "<<cnt<<endl;
	    if(cnt>=0){
		mx=max(mx,{val,i});
		mx_sum+=cnt;
		if(val==mn.first){
		    mn=min(mn,{val,i});
		    mn_sum+=cnt;
		}
		else{
		    mn=min(mn,{val,i});
		    mn_sum=cnt;
		}
		cout<<mn_sum<<endl;
	    }
	}
	cout<<mn_sum<<" mn "<<mn.first<<' '<<mn.second<<endl<<mx_sum<<"  mx "<<mx.first<<" "<<mx.second<<endl;
	if(mx_sum>K){
	    t[mx.second].modify(0);
	}
	else {
	    t[mn.second].modify(1);
	    /* res={mn.first,mn.second,t[mn.second].mid}; */
	}
	for(int i=1;i<=n;i++)cout<<t[i].l<<" "<<t[i].r<<endl;
	cout<<endl;
    }
    auto [v,x,y]=res;
    printf("%d %d %d\n",v,x,y);
} 

inline char gc() {
    return getchar();
    /* static char buf[1048580], *p1 = buf, *p2 = buf; */
    /* return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1048576, stdin), p1 == p2) ? EOF : *p1++; */
}
inline int read() {
    int x = 0;
    char ch = gc();

    while (ch < '0' || ch > '9') {
        ch = gc();
    }

    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = gc();
    }

    return x;
}
int Sgyuzwmreg87928[55][1010], Dsbqhrvgjg94635;
int Iujxecswgw89067, Vvkdhktmiv24781, Ybvrruilwi79848;
int query(int x, int y) {
    if (x < 1 || x > Iujxecswgw89067 || y < 1 || y > Vvkdhktmiv24781) {
        cerr << "Wrong parameter for query() on test " << Ybvrruilwi79848 << endl;
        exit(0);
    }

    Dsbqhrvgjg94635++;

    if (Dsbqhrvgjg94635 > 100000) {
        cerr << "Query too much on test " << Ybvrruilwi79848 << endl;
        exit(0);
    }

    return Sgyuzwmreg87928[x][y];
}
void guess(int num_testcase, int N, int M, int K);
int main() {
    /* freopen("inter.in", "r", stdin); */
    /* freopen("inter.out", "w", stdout); */
    int T = read(), maxcnt = 0;

    for (int i = 1; i <= T; i++) {
        int n = read(), m = read(), k = read();

        for (int I = 1; I <= n; I++) {
            for (int J = 1; J <= m; J++) {
                Sgyuzwmreg87928[I][J] = read();
            }
        }
        Iujxecswgw89067 = n;
        Vvkdhktmiv24781 = m;
        Dsbqhrvgjg94635 = 0;
        Ybvrruilwi79848 = i;
        guess(i, n, m, k);
        maxcnt = max(maxcnt, Dsbqhrvgjg94635);
    }

    cerr << "Number of queries: " << maxcnt << endl;
    return 0;
}
