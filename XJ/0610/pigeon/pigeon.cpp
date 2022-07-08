#include<bits/stdc++.h>
using namespace std;
const int maxn=1001;
int cnt[maxn];
vector<int>res[maxn];
int main(){
    vector<int>s;
    for(int i=0;i<(1<<4);i++){
	int p=[&]{
	for(int j=0;j<3;j++){
	    if((i>>j&1)&&(i>>(j+1))&1)return 0;
	}
	return 1;}();
	if(p)s.push_back(i);
    }
    for(int i=0;i<(1<<4);i++){
	vector<int>t;
	for(auto v:s)t.push_back({v^i});
	sort(t.begin(),t.end());t.erase(unique(t.begin(),t.end()),t.end());
	cout<<i<<" : ";
	for(auto v:t){
	    res[v].push_back(i);
	    cout<<v<<' ';
	    cnt[v]++;
	}
	cout<<endl;
    }
    /* for(int i=0;i<(1<<3);i++){ */
	/* cout<<i<<" : "; */
	/* for(auto v:res[i])cout<<v<<" "; */
	/* cout<<endl; */
    /* } */
}
