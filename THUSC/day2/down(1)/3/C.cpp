#include<bits/stdc++.h>
#define double long double
using namespace std;
const int maxn=1e4+5;
int n,m;
double Len[maxn],LA;
unordered_map<string,double>t[maxn],q[maxn];
const double k1=1.2,k3=2,b=0.75;
double solve(int dc,const unordered_map<string,double> &Q){
    double ans=0;
    for(auto [q,tftq]:Q){
	double df=0;
	for(int i=1;i<=n;i++)if(t[i].find(q)!=t[i].end()){
	    if(t[i][q]!=0)++df;
	}
	double tftd;

	if(t[dc].find(q)!=t[dc].end()){
	    tftd=t[dc][q];
	}
	else tftd=0;
	double lv=LA/(double)(n);
	double IDF=logl((n-df+0.5)/(df+0.5));
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
	int ps=0;string ss="";
	int len=s.size();
	while(ps<len){
	    ss="";
	    while(s[ps]!=' '&&ps<len){
		ss+=s[ps];
		ps++;
		/* hsh=(hsh*bs+s[ps])%mo,ps++; */
	    }
	    t[i][ss]++;
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
	    /* int hsh=0; */
	    string ss="";
	    while(s[ps]!=' '&&ps<len){
		ss+=s[ps];
		/* hsh=(hsh*bs+s[ps])%mo, */
		ps++;
	    }
	    q[i][ss]++;
	    ++ps;
	}
	double ans=solve(id,q[i]);
	ans+=5*1e-5;
	printf("%.4Lf\n",ans);
    }
}

