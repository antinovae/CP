#include <cmath>
#include <vector>
#include "testlib.h"
const int Maxn=5000;
int n;
std::string s,v;
std::string lis[Maxn+5];
std::vector<int> id[Maxn+5];
bool del[Maxn+5],used[Maxn+5];
int num[Maxn+5];
int v_s[Maxn+5];
int main(int argc,char* argv[]){
	registerTestlibCmd(argc,argv);
	n=inf.readInt();
	s=ouf.readString();
	if((int)s.size()!=n){
		quitf(_wa,"The length of the string is not n");
	}
	for(char c:s){
		if(c!='0'&&c!='1'){
			quitf(_wa,"The word of string must be 0 or 1");
		}
	}
	v=ouf.readString();
	if(s.find(v)==std::string::npos){
		quitf(_wa,"The second string is not a substring of the first string");
	}
	int m=(int)v.size();
	for(int i=0;i<=n-m;i++){
		for(int j=0;j<m;j++){
			lis[i]+=s[i+j];
		}
	}
	int len=n-m+1;
	std::sort(lis,lis+len);
	len=std::unique(lis,lis+len)-lis-1;
	v_s[0]=v[0]-'0';
	for(int i=1;i<m;i++){
		v_s[i]=v_s[i-1]+v[i]-'0';
	}
	for(int i=0;i<len;i++){
		int sum=0;
		for(int j=0;j<m;j++){
			sum+=lis[i][j]-'0';
			if(sum==v_s[j]){
				num[j]++;
			}
			else{
				id[j].push_back(i);
			}
		}
	}
	int ans_num=0;
	int lst=len;
	while(lst>1){
		ans_num++;
		int mn_val=n+1,mn_id=-1;
		for(int i=0;i<m;i++){
			if(used[i]){
				continue;
			}
			if(num[i]<mn_val){
				mn_val=num[i],mn_id=i;
			}
		}
		used[mn_id]=1;
		for(int i:id[mn_id]){
			if(del[i]){
				continue;
			}
			del[i]=1;
			lst--;
			int sum=0;
			for(int j=0;j<m;j++){
				sum+=lis[i][j]-'0';
				if(sum==v_s[j]){
					num[j]--;
				}
			}
		}
	}
	if(ans_num>=n/4){
		quitf(_ok,"OK with %d operations",ans_num);
	}
	else{
		double score=1.0*ans_num/(n/4);
		if(score<=0.7){
			score=exp(-0.6)*score/0.7;
		}
		else{
			score=exp(2*score)/exp(2);
		}
		int all=ans.readInt();
		quitf(_pc(score*all),"Correct with %d operations",ans_num);
	}
	return 0;
}
