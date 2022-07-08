#include<bits/stdc++.h>
#define double long double
using namespace std;
const int maxn=1e4+5;
int n,m;
#define ll long long
ll bs=137,mo=1e9+7;
double Len[maxn],LA;
unordered_map<ll,double>t[maxn],q[maxn];
const double k1=1.2,k3=2,b=0.75;
double solve(int dc,const unordered_map<ll,double> &Q){
    double ans=0;
    for(auto [q,tftq]:Q){
	double df=0;
	for(int i=1;i<=n;i++)if(t[i].find(q)!=t[i].end())++df;
	double tftd=t[dc][q];
	double lv=LA/(double)(n);
	double IDF=log((n-df+0.5)/(df+0.5));
	double SK=((k1+1)*tftd)/(k1*(1-b+b*(Len[dc]/lv))+tftd);
	double S=((k3+1)*tftq)/(k3+tftq);
	ans+=IDF*SK*S;
    }
    return ans;
}
int main(){
    scanf("%d%d",&n,&m);
    string s;
    getline(cin,s);
    for(int i=1;i<=n;i++){
	string s;getline(cin,s);
	int ps=0;ll hsh=0;
	int len=s.size();
	while(ps<len){
	    hsh=0;
	    while(s[ps]!=' '&&ps<len){
		hsh=(hsh*bs+s[ps])%mo,ps++;
	    }
	    t[i][hsh]++;
	    ++ps;
	    Len[i]++;
	}
	LA+=Len[i];
    }
    for(int i=1;i<=m;i++){
	string s;
	getline(cin,s);
	int ps=0,id=0;
	while(s[ps]!=','){
	    id=id*10+s[ps]-'0';
	    ++ps;
	}
	++ps;
	int len=s.size();
	while(ps<len){
	    int hsh=0;
	    while(s[ps]!=' '&&ps<len){
		hsh=(hsh*bs+s[ps])%mo,ps++;
	    }
	    q[i][hsh]++;
	    ++ps;
	}
	double ans=solve(id,q[i]);
	printf("%.4Lf\n",ans);
    }
}

