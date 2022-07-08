
#include <bits/stdc++.h>
#define maxn 500005
using namespace std;
int T, n, m;
long long k, a[maxn], b[maxn];
__int128 c[maxn];
unsigned long long seed;
long long Get(){
    seed = (seed << 43) ^ (seed >> 15) ^ (seed << 27) ^ seed;
    return seed >> 4;
}
void write(__int128 x){
    if(x >= 10) write(x / 10);
    putchar('0' + x % 10);
}
__int128 f(long long x, long long y) {
    return ((((__int128)x * y >> 60) * (x + y) >> 60) * (x >> 30) * (y >> 30) >> 60) * (x + y);
}
__int128 work()
{
    for (int i = 1; i <= n; i++)
    {
	for (int j = 1; j <= m; j++) 
	{
	    c[(i - 1) * m + j] = f(a[i], b[j]);
	}
    }
    sort(c + 1, c + n * m + 1);
    return c[k];
}
void solve(){
    cin >> n >> m >> k >> seed;
    for (int i = 1; i <= n; i++) a[i] = Get();
    for (int i = 1; i <= m; i++) b[i] = Get();
    write(work()); putchar('\n');
}
int main(){
    cin >> T;
    while(T--) solve();
    return 0;
}


