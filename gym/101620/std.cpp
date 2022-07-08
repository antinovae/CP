#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;

#define maxn 4000
#define s second
#define f first

int n, x, y, d;
char q;
int states[maxn][maxn];
bool covered[maxn][maxn];
pair<int, int> change[maxn][maxn];
double ans = 0;
int curr = 0;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for(int i = 0; i < maxn; i++){
        for(int j = 0; j < maxn; j++){
            states[i][j]=0;
            covered[i][j]=false;
            change[i][j]={0, 0};
        }
    }
    for(int i = 0; i < n; i++){
       cin >> q >> x >> y >> d;
        x += 2000;
        y += 2000;
        if(q == 'A'){
            change[x-(d/2)][y-(d/2)].f = max(change[x-(d/2)][y-(d/2)].f, d);
        }
        else{
            change[x-(d/2)][y].s = max(change[x-(d/2)][y].s, d/2);
        }
    }
    for(int i = 0; i < maxn; i++){
        for(int j = 0; j < maxn; j++){
            if(change[i][j].f){
                //cout << i << " " << j << endl;
                covered[i][j]=true;
                change[i][j+1].f = max(change[i][j+1].f, change[i][j].f-1);
                change[i+1][j].f = max(change[i+1][j].f, change[i][j].f-1);
                change[i+1][j+1].f = max(change[i+1][j+1].f, change[i][j].f-1);
            }
            if(change[i][j].s){
                //cout << i << " " << j << " " << change[i][j].s << endl;
                states[i][j]|=1;
                states[i][j-1]|=2;
                states[i+1][j-1]|=4;
                states[i+1][j]|=8;
                change[i+1][j-1].s = max(change[i+1][j-1].s, change[i][j].s-1);
                change[i+1][j+1].s = max(change[i+1][j+1].s, change[i][j].s-1);
                change[i+2][j].s = max(change[i+2][j].s, change[i][j].s-1);
            }
        }
    }
    for(int i = 0; i < maxn; i++){
        for(int j = 0; j < maxn; j++){
            if(covered[i][j]){
		cout<<i<<" "<<j<<" "<<" cover "<<endl;
                ans += 1;
            }
            else if(states[i][j]){
                int sus = states[i][j], btcnt = 0;
                for(int i = 0; i < 4; i++)btcnt+=bool(sus & (1 << i));
		cout<<i<<" "<<j<<" "<<btcnt<<endl;
                if(btcnt == 1)ans+=0.5;
                else{
                    if((bool(sus & (1 << 0)) && bool(sus & (1 << 2))) || (bool(sus & (1 << 1)) && bool(sus & (1 << 3))))ans += 1;
                    else ans += 0.75;
                }
            }
        }
    }
    cout << setprecision(2) << fixed << ans << endl;
}
