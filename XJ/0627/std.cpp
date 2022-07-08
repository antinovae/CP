#include<bits/stdc++.h>
#define LL long long
#define pb push_back
#define SZ(x) ((int)x.size()-1)
#define ms(a,b) memset(a,b,sizeof a)
#define F(i,a,b) for (int i=(a);i<=(b);++i)
#define DF(i,a,b) for (int i=(a);i>=(b);--i)
//#define mp make_pair
//#define OO(x) fixed<<setprecision(x)
using namespace std;
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
inline LL read(){
    char ch=getchar(); LL w=1,c=0;
    for(;!isdigit(ch);ch=getchar()) if (ch=='-') w=-1;
    for(;isdigit(ch);ch=getchar()) c=(c<<1)+(c<<3)+(ch^48);
    return w*c;
}
const int M=2e6+10;
 
int sz[M],c[M][2],tot;
LL val[M],tgv[M],w[M][2],pri[M],mx[M][2];
LL shift;
void pu(int x){
    sz[x]=sz[c[x][0]]+sz[c[x][1]]+1;
    F(o,0,1){
        mx[x][o]=w[x][o];
        if (c[x][0]) mx[x][o]=max(mx[x][o],mx[c[x][0]][o]);
        if (c[x][1]) mx[x][o]=max(mx[x][o],mx[c[x][1]][o]);
    }
     
}
int nw(LL x,LL y){
    tot++;
    sz[tot]=1; mx[tot][0]=w[tot][0]=y; mx[tot][1]=w[tot][1]=y-x; val[tot]=x; pri[tot]=rnd();
    return tot;
}
void add(int x,LL y){
    if (!x) return ;
     
    F(i,0,1) mx[x][i]+=y,w[x][i]+=y; tgv[x]+=y;
}
void pd(int x){
    if (tgv[x]){
        add(c[x][0],tgv[x]);
        add(c[x][1],tgv[x]);
        tgv[x]=0;
    }
    return ;
}
int merge(int x,int y){
    if (!x || !y) return x|y;
    pd(x); pd(y);
    if (pri[x]>pri[y]){
        c[x][1]=merge(c[x][1],y);
        pu(x);
        return x;
    }
    else{
        c[y][0]=merge(x,c[y][0]);
        pu(y);
        return y;
    }
}
void split(int now,LL k,int &x,int &y){
    if (!now) return x=y=0,void();
    pd(now);
    if (val[now]<=k){
        x=now;
        split(c[now][1],k,c[x][1],y);
    }
    else{
        y=now;
        split(c[now][0],k,x,c[y][0]);
    }
    pu(now);
}
void ins(int &rt,int x){
    sz[x]=1; c[x][0]=c[x][1]=0;
    int tx,ty;
    split(rt,val[x],tx,ty);
    rt=merge(tx,merge(x,ty));
}
 
 
 
const LL inf=3e18;
int n,m,ct;
struct node{
    LL l,r;
}a[M],b[M];
LL t[M],C;
int h[M];
struct pv{
    LL x,y;
};
vector<pv> dp;
 
int main(){
    n=read(); m=read(); C=read();
    F(i,1,n){
        a[i]=(node){read(),read()};
        t[++ct]=a[i].l; t[++ct]=a[i].r;
    }
    F(i,1,m){
        b[i]=(node){read(),read()};
        t[++ct]=b[i].l; t[++ct]=b[i].r;
    }
    sort(t+1,t+ct+1);
    int N=unique(t+1,t+ct+1)-t-1;
    F(i,1,n){
        a[i].l=lower_bound(t+1,t+N+1,a[i].l)-t;
        a[i].r=lower_bound(t+1,t+N+1,a[i].r)-t;
        h[a[i].l]+=1;
        h[a[i].r]-=1;
    }
    F(i,1,m){
        b[i].l=lower_bound(t+1,t+N+1,b[i].l)-t;
        b[i].r=lower_bound(t+1,t+N+1,b[i].r)-t;
        h[b[i].l]+=2;
        h[b[i].r]-=2;
    }
    LL la=0;
    LL ta=0,tb=0;
    int rt=nw(0,0);
    mx[0][0]=mx[0][1]=-inf;
//  dp.pb((pv){0,0});
    F(i,1,N){
//      if (i%1000==0){
//          cerr<<i<<"\n";
//      }
        h[i]+=h[i-1];
        if (h[i]==3){
            LL mxc=-inf,mxcc=-inf;
            LL tmp=ta-tb,le=t[i+1]-t[i];
            shift+=tmp;
            LL L=-C-1-shift,R=C-shift;
            int tx=0,ty=0,tz=0;
            split(rt,L,tx,ty);
            split(ty,R,ty,tz);
            add(tx,ta+le);
            add(ty,ta+2*le);
            add(tz,ta+le);
//          cerr<<mx[tx][0]<<" "<<mx[ty][0]<<" "<<mx[tz][0]<<" ???\n";
            if (tz){
                int no=nw(C-shift,mx[tz][1]-shift+C+le);
//              cerr<<mx[tz][1]-shift+C+le<<" !!!\n";
//              cerr<<mx[ty][0]<<"\n";
 
                ty=merge(ty,merge(no,tz));
//              cerr<<mx[ty][0]<<"\n";
            }
            if (tx){
                int no=nw(-C-shift,mx[tx][0]+le);
                rt=merge(tx,merge(no,ty));
            }
            else rt=ty;
             
//          cerr<<ta<<" "<<tb<<" "<<tmp<<" "<<le<<" "<<i<<" !!!!!\n";
//          for (auto &O:dp){
//              O.x+=tmp;
//              O.y+=ta;
//              if (O.x>C){
//                  mxc=max(mxc,O.y-(O.x-C)+2*le);
//                  O.y+=le;
//              }
//              else if (O.x<-C){
//                  mxcc=max(mxcc,O.y+2*le);
//                  O.y+=le;
//              }
//              else O.y+=2*le;
//          }
//          if (mxc!=-inf) dp.pb((pv){C,mxc});
//          if (mxcc!=-inf) dp.pb((pv){-C,mxcc});
//          la=i;
            ta=tb=0;
        }
        else{
            if (h[i]==1) ta+=t[i+1]-t[i];
            if (h[i]==2) tb+=t[i+1]-t[i];
        }
    }
//  cerr<<tot<<"\n";
//  LL ans=-inf;
//  for (auto &O:dp){
//      ans=max(ans,O.y);
//  }
//  cout<<ans+ta<<"\n";
    cout<<ta+mx[rt][0]<<"\n";
    return 0;
}
/* stuff you should look for
    * int overflow, array bounds
    * special cases (n=1?)
    * do smth instead of nothing and stay organized
    * WRITE STUFF DOWN
    * DON'T GET STUCK ON ONE APPROACH
*/
