#include<bits/stdc++.h>
using namespace std;
const int maxn=1000001;
int ch[maxn][2],fa[maxn],cnt[maxn],n;
set<int>s;
struct info{
    int c[2];
}f[maxn];
#define ls ch[x][0]
#define rs ch[x][1]
int isrt(int x){
    return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;
}
int get(int x){
    return ch[fa[x]][1]==x;
}
info merge(info x,info y){
    return {x.c[y.c[0]],x.c[y.c[1]]};
}
void pushup(int x){
    info p;
    if(cnt[x]==0)p={1,0};
    else p={0,0};
    if(rs)p=merge(p,f[rs]);
    if(ls)p=merge(f[ls],p);
    f[x]=p;
}
void rotate(int x){
    int y=fa[x],z=fa[y],k=get(x);
    if(!isrt(y)&&z)ch[z][get(y)]=x;
    ch[y][k]=ch[x][!k],fa[ch[x][!k]]=y;
    ch[x][!k]=y;fa[y]=x;fa[x]=z;
    pushup(y);pushup(x);
}
 
void splay(int x){
    while(!isrt(x)){
        int y=fa[x];
        if (!isrt(y))rotate(get(y)==get(x)?y:x);
        rotate(x);
    }
}
void access(int x){
    /* cout<<"access "<<x<<endl; */
    for(int y=0;x;y=x,x=fa[x]){
        splay(x);
        cnt[x]+=f[ch[x][1]].c[0];
        ch[x][1]=y;
        cnt[x]-=f[ch[x][1]].c[0];
        pushup(x);
    }
}
void make_rt(int x){
    access(x);splay(x);
}
int a[maxn];
int real_rt(int x){
    while(ch[x][0])x=ch[x][0];
    return x;
}
void check(int x,int tp){
    if(!x)return;
    make_rt(x);
    if(f[x].c[0]){
        int y=real_rt(x);
        if((y-a[y]+n)%n==0){
            if(tp==1)s.insert(y);
            else s.erase(y);
        }
        splay(y);
    }
}
void link(int x,int y){
    check(x,-1);
    if(y>x||y==0||y==x){check(x,1);return;}
    check(y,-1);
    make_rt(x);
    fa[x]=y;
    cnt[y]+=f[x].c[0];
    pushup(y);
    check(x,1); check(y,1);
}
void cut(int x,int y){
    check(x,-1);
    if(y>x||y==0||y==x){ check(x,1);return; }
    check(y,-1);
    if(y>x)return;
    make_rt(x);splay(y);
    fa[x]=ch[y][1]=0;
    check(x,1);check(y,1);
}
int x,y;
void cal(){
    if(s.empty())puts("0");
    else printf("%d\n",*(s.begin()));
}
int main(){
    freopen("match.in","r",stdin);
    freopen("match.out","w",stdout);
    int Q;
    scanf("%d%d",&n,&Q);
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
        if(i){
            int x=(i-a[i]+n)%n;
            if(x<i&&x)link(i,x);
            else check(i,1);
        }
    }
    cal();
    for(int i=1;i<=Q;i++){
        scanf("%d%d",&x,&y);
        int z=(x-a[x]+n)%n;
        if(z<x&&z)cut(x,z);
        else check(x,-1);
        a[x]=y;
        z=(x-a[x]+n)%n;
        if(z<x&&z)link(x,z);
        else check(x,1);
        cal();
    }
}
