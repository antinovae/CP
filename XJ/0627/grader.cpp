#include<bits/stdc++.h>
using namespace std;
namespace Grader{
    int n,nx,ny,stp;
    int a[2001][2001];
    int mx[7]={0,-1,0,1,0};
    int my[7]={0,0,1,0,-1};
}
void solve(int);
int move(int np){
    Grader::stp++;
    int ni=Grader::a[Grader::nx+Grader::mx[np]][Grader::ny+Grader::my[np]],nj=Grader::a[Grader::nx+2*Grader::mx[np]][Grader::ny+2*Grader::my[np]];
    if(ni&&nj&&ni!=nj)return 0;
    Grader::a[Grader::nx][Grader::ny]=0;
    if(ni&&!nj)Grader::a[Grader::nx+2*Grader::mx[np]][Grader::ny+2*Grader::my[np]]=Grader::a[Grader::nx+Grader::mx[np]][Grader::ny+Grader::my[np]];
    else if(ni&&nj)Grader::a[Grader::nx+2*Grader::mx[np]][Grader::ny+2*Grader::my[np]]=Grader::a[Grader::nx+2*Grader::mx[np]][Grader::ny+2*Grader::my[np]]+Grader::a[Grader::nx+Grader::mx[np]][Grader::ny+Grader::my[np]];
    Grader::a[Grader::nx+Grader::mx[np]][Grader::ny+Grader::my[np]]=-1;
    Grader::nx+=Grader::mx[np],Grader::ny+=Grader::my[np];
    return 1;
}
void chk(){
    if(Grader::stp>200000000){
	cout<<"GG"<<endl;
	return;
    }
    set<int>se;se.clear();
    for(int i=0;i<=2000;i++){
	for(int j=0;j<=2000;j++){
	    if(Grader::a[i][j]>0){
		if(se.find(Grader::a[i][j])!=se.end()){
		    cout<<"GG"<<endl;
		    return;
		}
		se.insert(Grader::a[i][j]);
	    }
	}
    }
    cout<<"JU"<<endl;
}
signed main(){
    char c;
    cin>>Grader::n;
    for(int i=1000-Grader::n;i<=1000+Grader::n;i++){
	for(int j=1000-Grader::n;j<=1000+Grader::n;j++){
	    cin>>c;
	    if(c=='1')Grader::a[i][j]=1;
	    else if(c=='@')Grader::a[i][j]=-1,Grader::nx=i,Grader::ny=j;
	}
    }
    solve(Grader::n);
    chk();
    return 0;
}
