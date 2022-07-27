#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=j;i<=k;i++)
#define mo 998244353
using namespace std;
template<typename T> void read(T &num){
     char c=getchar();T f=1;num=0;
     while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
     while(c>='0'&&c<='9'){num=(num<<3)+(num<<1)+(c^48);c=getchar();}
     num*=f;
}
template<typename T> void qwq(T x){
    if(x>9)qwq(x/10);
    putchar(x%10+'0');
}
template<typename T> void write(T x){
    if(x<0){x=-x;putchar('-');}
    qwq(x);putchar('\n');
}
template<typename T> void chkinc(T &x,T y){x=(x+y>=mo)?(x+y-mo):(x+y);}
int n;long long m;
int Pr[110];
int f[20000010];int prime[40010];int pre[20000010];int len=0;
void Pre(int n){
    int tmp=0;
    rep(i,2,n){
        pre[i]=pre[i-1]+(f[i]==0);
        if(!f[i]&&i<=40000)prime[++len]=i;
        rep(j,1,len){
            if(1ll*prime[j]*i>n)break;
            f[i*prime[j]]=f[i]+1;
            if(i%prime[j]==0)break;
        }
    }
    return;
}
int cnt[40];
struct mat{
    int w[40][40];
};
struct Vec{
    int w[40];
};
mat operator *(mat a,mat b){
    mat c;
    rep(i,0,31){
        rep(j,0,31){
            c.w[i][j]=0;
            rep(k,0,31){int nop=(1ll*a.w[i][k]*b.w[k][j])%mo;chkinc(c.w[i][j],nop);}
        }
    }
    return c;
}
Vec operator *(Vec a,mat b){
    Vec c;
    rep(j,0,31){
        c.w[j]=0;
        rep(k,0,31){int nop=(1ll*a.w[k]*b.w[k][j])%mo;chkinc(c.w[j],nop);}
    }
    return c;
}
int F(int n,int m){
    if(!m)return n;
    if(n<prime[m+1])return 1;
    return F(n,m-1)-F(n/prime[m],m-1);
}
int Ans(int x){
    int ret=pre[(int)sqrt(x)];
    int num=0;
    rep(i,1,4000){if(prime[i]>(int)sqrt(x)){num=i-1;break;}}
    return ret+F(x,num)-1;
}
int s;
void dfs(int dep,int w,int lst){
    s=((n/w<=20000000)?pre[n/w]:Pr[w])-lst+1;
    if(s<=0)return;
    cnt[dep-1]+=max(0,s);
    rep(i,lst,4000){
        if(w>n/prime[i]/prime[i])break;
        dfs(dep+1,w*prime[i],i);
    }
    return;
}
int main(){
    freopen("game.in","r",stdin);
    freopen("game.out","w",stdout);
    read(n);read(m);
    Pre(20000000);
    if(n>10000000){rep(i,1,49)Pr[i]=Ans(n/i);}
    cnt[0]++;
    dfs(1,1,1);
    Vec ret;
    rep(i,0,31)ret.w[i]=(i==0);
    mat trans;
    rep(i,0,31){
        rep(j,0,31)trans.w[i][j]=cnt[i^j];
    }
     
    while(m){
        if(m&1)ret=ret*trans;
        trans=trans*trans;
        m>>=1;
    }
    write(ret.w[0]);
    return 0;
}
