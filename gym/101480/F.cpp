#include<bits/stdc++.h>
using namespace std;
#define float128 __float128
#define int long long
const int maxn=1e6+10,mo=1e6+3;
int res[maxn];
int a[maxn],b[maxn],fac[maxn],rss[maxn],iv[maxn],f[1001][1001];
int qpow(int a,int b,int res=1){
    for(;b;b>>=1,a=a*a%mo)if(b&1)res=res*a%mo;
    return res;
}
namespace poly{
    using namespace std;
    typedef long long ll;
    typedef long double db;
    const db pi=acos(-1.0);
    struct com{
	db real,imag;
	com(){}
	com(db _real,db _imag){real=_real;imag=_imag;} 
	friend com operator + (com p,com q){return com(p.real+q.real,p.imag+q.imag);}
	friend com operator - (com p,com q){return com(p.real-q.real,p.imag-q.imag);}
	friend com operator * (com p,com q){return com(p.real*q.real-p.imag*q.imag,p.real*q.imag+q.real*p.imag);}
	friend com operator * (com p,db q){return com(p.real*q,p.imag*q);} 
	friend com operator / (com p,db q){return com(p.real/q,p.imag/q);} 
	com conj(){return com(real,-imag);} 
    };
    int rev[maxn+5];
    void fft(com* x,int n,int type){
	for(int i=0;i<n;i++) if(i<rev[i]) swap(x[i],x[rev[i]]);
	for(int len=1;len<n;len*=2){
	    int sz=len*2;
	    com wn1=com(cos(2*pi/sz),type*sin(2*pi/sz));
	    for(int l=0;l<n;l+=sz){
		int r=l+len-1;
		com wnk=com(1,0);
		for(int i=l;i<=r;i++){
		    com tmp=x[i+len];
		    x[i+len]=x[i]-wnk*tmp;
		    x[i]=x[i]+wnk*tmp;
		    wnk=wnk*wn1;
		}
	    }
	}
	if(type==-1){
	    for(int i=0;i<n;i++)x[i]=x[i]/n; 
	} 
    } 
    ll mod; 
    void mul(ll *a,ll *b,ll *c,int n,int m){
	static com p[maxn+5],q[maxn+5],r[maxn+5],s[maxn+5];
	int N=1,L=0;
	while(N<=n+m-1){
	    N*=2;
	    L++;
	}
	for(int i=0;i<N;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(L-1));
	for(int i=0;i<N;i++) p[i]=q[i]=r[i]=s[i]=com(0,0);
	for(int i=0;i<n;i++){
	    ll ta=(a[i]%mod+mod)%mod;
	    p[i]=com(ta>>15,ta&((1<<15)-1));
	}
	for(int i=0;i<m;i++){
	    ll tb=(b[i]%mod+mod)%mod;
	    q[i]=com(tb>>15,tb&((1<<15)-1));
	}
	fft(p,N,1);
	fft(q,N,1);
	for(int i=0;i<N;i++){
	    int j=(i==0?0:N-i);
	    com da=(p[i]+p[j].conj())*com(0.5,0);
	    com db=(p[i]-p[j].conj())*com(0,-0.5);
	    com dc=(q[i]+q[j].conj())*com(0.5,0);
	    com dd=(q[i]-q[j].conj())*com(0,-0.5);
	    r[j]=da*dc+da*dd*com(0,1);
	    s[j]=db*dc+db*dd*com(0,1);
	}
	fft(r,N,1);
	fft(s,N,1);
	for(int i=0;i<N;i++){
	    ll ac=(ll)(r[i].real/N+0.5)%mod;
	    ll ad=(ll)(r[i].imag/N+0.5)%mod; 
	    ll bc=(ll)(s[i].real/N+0.5)%mod;
	    ll bd=(ll)(s[i].imag/N+0.5)%mod;
	    c[i]=(((ac<<30)+((ad+bc)<<15)+bd)%mod+mod)%mod;
	}
	for(int i=n+m-1;i<N;i++) c[i]=0;
    } 
    int n,m; 
    ll a[maxn+5],b[maxn+5],c[maxn+5];
    void solve(int _m,int x,int y){
	n=m=_m;
	mod=mo;
	for(int i=0;i<n;i++){
	    a[i]=qpow(x,i);//*iv[i]%mo;
	    a[i]=qpow(x,i)*iv[i]%mo;
	}
	for(int i=0;i<n;i++){
	    b[i]=qpow(y,i);//*iv[i]%mo;
	    b[i]=qpow(y,i)*iv[i]%mo;
	}
	mul(a,b,c,n,m);
	for(int i=0;i<=2*m-2;i++){
	    res[i]=c[i];
	}
    }
}
int ans,n,x,y,z;

int C(int x,int y){
    return fac[x]*iv[y]%mo*iv[x-y]%mo;
}
void init(){
    fac[0]=iv[0]=1;
    for(int i=1;i<maxn;i++)fac[i]=fac[i-1]*i%mo,iv[i]=qpow(fac[i],mo-2);
}
mt19937 rnd(time(0));
signed main(){
    init();

    scanf("%lld%lld%lld%lld",&n,&x,&y,&z);
    // for(int i=0;i<n;i++)scanf("%d",&a[i]);
    // for(int i=0;i<n;i++)scanf("%d",&b[i]);
    for(int i=1;i<=n;i++){
	a[i]=rnd()%mo;
	b[i]=rnd();
    }
    for(int i=0;i<n;i++)f[i][0]=a[i];
    for(int i=0;i<n;i++)f[0][i]=b[i];
    n--;
    for(int i=1;i<=n;i++){
	for(int j=1;j<=n;j++){
	    f[i][j]=(f[i][j-1]*x+f[i-1][j]*y+z)%mo;
	}
    }
    cout<<f[n][n]<<endl;
    for(int i=1;i<=n;i++){
	(ans+=C(2*n-i-1,n-1)*qpow(x,n)%mo*qpow(y,n-i)%mo*a[i]%mo)%=mo;
	(ans+=C(2*n-i-1,n-1)*qpow(x,n-i)%mo*qpow(y,n)%mo*b[i]%mo)%=mo;

    }
    poly::solve(n,x,y);
    for(int i=0;i<2*n;i++){
	(ans+=fac[i]*res[i]%mo*z%mo)%=mo;
    }
    cout<<ans;
}
