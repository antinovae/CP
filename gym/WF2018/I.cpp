#include<bits/stdc++.h>
using namespace std;
#define ll long long
using pii=pair<int,int>;
using vi=vector<int>;
struct BIT{
    vector<ll>a;
    BIT(int n):a(n,0){}
    void add(int p,ll x){for(p++;p<=a.size();p+=p&-p)a[p-1]+=x;}
    ll sum(int p){ll ret=0;for(p++;p>0;p&=p-1)ret+=a[p-1];return ret;}
};
const int maxn=3005;
int vl[maxn][2*maxn],vr[maxn][2*maxn],a[2*maxn];
int r,c;
void add(int p,ll x){for(p++;p<=c;p+=p&-p)a[p]+=x;}
ll sum(int p){ll ret=0;for(p++;p>0;p&=p-1)ret+=a[p];return ret;}
int main() {
    ios::sync_with_stdio(0),cin.tie(0);
    cin>>r>>c;
    vector<string>ar(r*2-1);
    getline(cin,ar[0]);
    for(auto &i:ar){
        getline(cin,i);
        i.resize(2*c-1,' ');
    }
    ll ans=0;
    auto solve=[&](){
	memset(vl,0,sizeof(vl));
	memset(vr,0,sizeof(vr));
        for(int i=1;i<r;i++){
	    memset(a,0,sizeof(a));
	    priority_queue<pii,vector<pii>,greater<pii>>s;
            for(int j=ar[i*2][0]==' ';j<c;j+=2){
                int x=i*2,y=j*2;
                vl[i][j]=j==0||ar[x-1][y-1]==' '?0:vl[i-1][j-1]+1;
                vr[i][j]=j==c-1||ar[x-1][y+1]==' '?0:vr[i-1][j+1]+1;
                ans+=sum(j)-sum(j-vl[i][j]*2-1);
                s.push({j+vr[i][j]*2,j});
                add(j,1);
                while(!s.empty()&&(j+2>=c||ar[x][y+1]==' '||s.top().first==j)){
                    add(s.top().second,-1);
		    s.pop();
                }
            }
        }
    };
    solve();
    reverse(ar.begin(),ar.end());
    solve();
    cout<<ans;
}
 
