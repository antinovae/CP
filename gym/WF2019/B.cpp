#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e5+5;
const int INF=1e15;
int x[maxn],y[maxn],H,n,a,b,f[maxn];
template<class T>T sqr(T x){return x*x;}
pair<double,double> get_root(int A,int B,int C){
    double delta=B*B-4*A*C;
    if(delta<0)return {INF,INF};
    delta=sqrt(delta);
    double x1=(-B-delta)/A/2.0,x2=(-B+delta)/A/2.0;
    return {x1,x2};
}
signed main(){
    scanf("%lld%lld%lld%lld",&n,&H,&a,&b);
    for(int i=1;i<=n;i++)scanf("%lld%lld",&x[i],&y[i]);
    memset(f,0x3f,sizeof(f));
    f[1]=a*(H-y[1]);
    for(int i=2;i<=n;i++) {
        double L=x[i]-(H-y[i])*2,R=x[i]; int Tx=x[i];
        for(int j=i-1;j>=1;j--) {
            double A=1;
	    double B=2.0*(-2*x[j]+2*H-2*y[j]+Tx);
	    double C=sqr(Tx-2*x[j])+sqr(2*H-2*y[j]-Tx)-sqr(Tx);
	    auto [x1,x2]=get_root(A,B,C);
	    if(x1==INF)break;
            if(Tx-x[j]<=2*(H-y[j]))x2=x[j];
            L=max(L,x1),R=min(R,x2);
            if(L>R)break;
            if(L<=x[j]&&x[j]<=R) {
                f[i]=min(f[i],f[j]+b*sqr(x[i]-x[j])+a*(H-y[i]));
            }
        }
    }
    if(f[n]>=INF) cout<<"impossible\n";
    else cout<<f[n]<<endl;
    return 0;
}
