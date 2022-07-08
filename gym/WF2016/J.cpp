#include<bits/stdc++.h>
#include <vector>
using namespace std;
const int INF=1e9;
struct point{
    int x,y;
    point operator + (point a) const {return {x+a.x,y+a.y};}
    point operator - (point a) const {return {x-a.x,y-a.y};}
    point operator * (int a) const {return {x*a,y*a};}
    bool operator == (point a) const {return (x==a.x)&&(y==a.y);}
    int operator * (point a) const {return x*a.x+y*a.y;}
    int bel(){
	if(y>=0&&x>0)return 1;
	else if(y>0&&x<=0)return 2;
	else if(y<=0&&x<0)return 3;
	else if(y<0&&x>=0)return 4;
	else assert(0);

    }
};
int cross(point a,point b){
    return a.x*b.y-a.y*b.x;
}
vector<point>upper_hull(const vector<point> &p){
    vector<point>hull(p.size());
    hull[0]=p[0];
    hull[1]=p[1];
    int top=1;
    for(int i=2;i<p.size();i++){
	/* cout<<"in "<<p[i].x<<" "<<p[i].y<<endl; */
	while(top&&cross(p[i]-hull[top],hull[top]-hull[top-1])<=0){
	    /* cout<<"out "<<hull[top].x<<" "<<hull[top].y<<endl; */
	    --top;
	}
	hull[++top]=p[i];
    }
    hull.resize(top+1);
    return hull;
};
vector<point>lower_hull(const vector<point> &p){
    vector<point>hull(p.size());
    hull[0]=p[0];
    hull[1]=p[1];
    int top=1;
    for(int i=2;i<p.size();i++){
	while(top&&cross(p[i]-hull[top],hull[top]-hull[top-1])>=0){
	    --top;
	}
	hull[++top]=p[i];
    }
    hull.resize(top+1);
    return hull;
};
void check_r(point a,point b,point c,point x,vector<point> &ans){
    point p1=b-a;
    point p2=c-b;
    if(cross(p1,x-b)>=0&&cross(x-b,p2)>=0){
	ans.push_back(b);
    }
}
void check_l(point a,point b,point c,point x,vector<point> &ans){
    point p1=b-a;
    point p2=c-b;
    if(cross(p1,x-b)>=0&&cross(x-b,p2)>=0){
	ans.push_back(b);
    }
}
void upper_tangent(const vector<point> &p,point x,vector<point> &ans){
    int M=lower_bound(p.begin(),p.end(),x,[](point a,point b){return a.x<b.x;})-p.begin();
    int L=0,R=p.size()-1;
    cout<<L<<" "<<M<<" "<<R<<endl;
    int l=L+1,r=min(M-1,R-1);
    while(l<=r){
	int mid=(l+r)/2;
	point p1=p[mid]-p[mid+1];
	point p2=p[mid-1]-p[mid];
	if(cross(p1,p[mid]-x)>=0&&cross(p[mid]-x,p2)>=0){
	    ans.push_back(p[mid]);
	    break;
	}
	else if(cross(p1,p[mid]-x)<0&&cross(p[mid]-x,p2)>0){l=mid+1;}
	else if(cross(p1,p[mid]-x)>0&&cross(p[mid]-x,p2)<0){r=mid-1;}
	else assert(0);
    }
    l=max(M,L+1),r=R-1;
    while(l<=r){
	int mid=(l+r)/2;
	point p1=p[mid]-p[mid-1];
	point p2=p[mid+1]-p[mid];
	cout<<l<<' '<<mid<<' '<<r<<endl;
	cout<<p[mid].x<<" "<<p[mid].y<<endl;
	if(cross(p1,p[mid]-x)<=0&&cross(p[mid]-x,p2)<=0){
	    ans.push_back(p[mid]);
	    break;
	}
	else if(cross(p1,p[mid]-x)<0&&cross(p[mid]-x,p2)>0){l=mid+1;}
	else if(cross(p1,p[mid]-x)>0&&cross(p[mid]-x,p2)<0){r=mid-1;}
	else{
	    assert(0);

	}
    }
}
void lower_tangent(const vector<point> &p,point x,vector<point> &ans){
    int M=prev(lower_bound(p.begin(),p.end(),x,[](point a,point b){return a.x<b.x;}))-p.begin();
    int L=0,R=p.size()-1;
    int l=L+1,r=min(M,R-1);
    while(l<=r){
	int mid=(l+r)/2;
	point p1=p[mid]-p[mid+1];
	point p2=p[mid-1]-p[mid];
	if(cross(p1,p[mid]-x)<=0&&cross(p[mid]-x,p2)<=0){
	    ans.push_back(p[mid]);
	    break;
	}
	else if(cross(p1,p[mid]-x)<0&&cross(p[mid]-x,p2)>0){r=mid-1;}
	else if(cross(p1,p[mid]-x)>0&&cross(p[mid]-x,p2)<0){l=mid+1;}
	else assert(0);
    }
    l=max(M+1,L+1),r=R-1;
    /* for(int i=0;i<p.size();i++){ */
	/* cout<<p[i].x<<" "<<p[i].y<<endl; */
    /* } */
    /* cout<<L<<" "<<M<<" "<<R<<endl; */
    while(l<=r){
	int mid=(l+r)/2;
	cout<<"cur "<<p[mid].x<<' '<<p[mid].y<<endl;
	point p1=p[mid]-p[mid-1];
	point p2=p[mid+1]-p[mid];
	if(cross(p1,p[mid]-x)>=0&&cross(p[mid]-x,p2)>=0){
	    ans.push_back(p[mid]);
	    break;
	}
	else if(cross(p1,p[mid]-x)<0&&cross(p[mid]-x,p2)>0){r=mid-1;}
	else if(cross(p1,p[mid]-x)>0&&cross(p[mid]-x,p2)<0){l=mid+1;}
	else assert(0);
    }

    /* for(auto [x,y]:ans){ */
	/* cout<<"ans: "<<x<<" "<<y<<endl; */
    /* } */
}
int n;

const int maxn=100001;
bool cmp(point a,point b){
    if(a.bel()!=b.bel())return a.bel()<b.bel();
    else return cross(a,b)>0;
}
int main(){
    scanf("%d",&n);
    vector<point>p,a;
    for(int i=1;i<=n;i++){
	int x,y,z;scanf("%d%d%d",&x,&y,&z);
	if(z==1){
	    p.push_back({x,y});
	}
	else a.push_back({x,y});
    }
    int cc=p.size();
    sort(p.begin(),p.end(),[](point a,point b){
	    if(a.x!=b.x)return a.x<b.x;
	    else return a.y>b.y;});
    /* for(auto [x,y]:p){ */
	/* cout<<x<<' '<<y<<endl; */
    /* } */
    auto h1=upper_hull(p),h2=lower_hull(p);
    for(auto [x,y]:h1){
	cout<<x<<" "<<y<<endl;
    }
    for(auto [x,y]:h2){
	cout<<x<<" "<<y<<endl;
    }
    /* vector<point>cur; */
    /* check_l(h2[1],h1[0],h1[1],{-1,1},cur); */
    /* check_r(h1[h1.size()-2],h1[h1.size()-1],h2[h2.size()-2],{-1,1},cur); */
    /* for(auto [x,y]:cur){ */
	/* cout<<"ans: "<<x<<" "<<y<<endl; */
    /* } */
    /* assert(h1.front()==h2.front()); */
    /* assert(h1.back()==h2.back()); */
    vector<point>in,out,sp;
    auto put=[&](point a,point b){
	if(cross(a,b)<=0)swap(a,b);
	if(cross(a,{1,0})>0&&cross({1,0},b)>0){
	    in.push_back({1,0});
	    out.push_back(b);
	    in.push_back(a);
	}
	else{
	    in.push_back(a);
	    if(b.y!=0)out.push_back(b);
	}
    };
    for(auto v:a){
	vector<point>cur;
	cout<<"solve "<<v.x<<' '<<v.y<<endl;
	check_l(h2[1],h1[0],h1[1],v,cur);
	check_l(h1[h1.size()-2],h1[h1.size()-1],h2[h2.size()-2],v,cur);
	upper_tangent(h1,v,cur);
	lower_tangent(h2,v,cur);
	assert(cur.size()<=2);
	for(auto [x,y]:cur)cout<<x<<" "<<y<<"   ";
	cout<<endl;
	if(cur.size()==2){
	    if(cross(cur[0]-v,cur[1]-v)==0){
		cc++;
	    }
	    else{
		put(cur[0]-v,cur[1]-v);
		put(v-cur[0],v-cur[1]);
	    }
	}
	else cc++;
    }
    cout<<"cc: "<<cc<<endl;
    sort(in.begin(),in.end(),cmp);
    sort(out.begin(),out.end(),cmp);
    int cur=0,ans=INF;
    for(auto [x,y]:in){
	cout<<x<<" "<<y<<" in "<<(point){x,y}.bel()<<endl;
    }
    for(auto [x,y]:out){
	cout<<x<<" "<<y<<" out "<<(point){x,y}.bel()<<endl;
    }
    if(!(in[0]==(point){1,0}))ans=cur;
    for(int i=0,j=0;i<in.size();){
	while(j<out.size()&&cmp(out[j],in[i]))j++,cur--;
	ans=min(ans,cur);
	while(i<in.size()&&(i==in.size()-1||(cross(in[i],in[i+1])==0&&in[i]*in[i+1]>=0))){
	    cout<<in[i].x<<" "<<in[i].y<<"  "<<in[i+1].x<<" "<<in[i+1].y<<"  "<<cross(in[i],in[i+1])<<endl;
	    i++,cur++;
	}
	i++;cur++;
	if(j)cout<<i<<" "<<in[i-1].x<<" "<<in[i-1].y<<" | "<<j<<" "<<out[j-1].x<<" "<<out[j-1].y<<"  | "<<cur<<endl;
	else cout<<i<<" "<<in[i-1].x<<" "<<in[i-1].y<<" | "<<cur<<endl;
    }
    printf("%d\n",ans+cc);
}
