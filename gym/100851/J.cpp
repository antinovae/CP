#include<bits/stdc++.h>
using namespace std;
mt19937 rnd(114514);
int n;
int query(string s){
    int ans=0;
    cout<<s<<endl;
    cin>>ans;
    return ans;
}
string pre(){
    while(1){
	string s;
	for(int i=0;i<n;i++){
	    s+=rnd()%2+'0';
	}
	int ans=query(s);
	if(ans==n){
	    return 0;
	}
	if(ans==n/2)return s;
    }
}
int main(){
    cin>>n;
    string t=pre();
    t[0]^=1;
    vector<int>s1,s2;
    s1.push_back(0);
    for(int i=1;i<n;i++){
	t[i]^=1;
	int ans=query(t);
	t[i]^=1;
	if(ans==n/2)s2.push_back(i);
	else s1.push_back(i);
    }
    t[0]^=1;
    for(auto v:s1)t[v]^=1;
    int ans=query(t);
    if(ans==n)return 0;
    if(ans==0){
	for(int i=0;i<n;i++)t[i]^=1;
	cout<<t;
	return 0;
    }
}
