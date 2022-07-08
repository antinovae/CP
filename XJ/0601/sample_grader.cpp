#include"graph.h"
#include<bits/stdc++.h>
using namespace std;
static vector<int> v[100000];
static int n, cnt;
static int d[100000], d0[100000], t[100000];
static map<pair<int, int>, bool> s;
bool query(int x, int y) {
	if (x < 1 || x > n) {
		cerr << "First vertex not in [1,n]!" << endl;
		return 0;
	}
	if (y < 1 || y > n) {
		cerr << "Second vertex not in [1,n]!" << endl;
		return 0;
	}
	if (x == y) {
		cerr << "Two vertex are identical!" << endl;
		return 0;
	}
	++cnt;
	int tmp = 0;
	if (x > y) swap(x, y), tmp = 1;
	if (s.find(make_pair(x, y)) != s.end())
		return s[make_pair(x, y)] ^ tmp;
	++t[x], ++t[y];
	int res = v[x-1][y-1];
	if (res == 1) ++d0[x];
	else ++d0[y];
	return (s[make_pair(x, y)] = res) ^ tmp;
}
int main() {
	int type;
	cin >> n >> type;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			int p;
			cin >> p;
			v[i-1].push_back(p);
			++d[i];
		}
	int rep = find(n, type);
	if (rep < 0 || rep > n) {
		cerr << "Report result isn't in [0,n]" << endl;
		return 0;
	}
	if (rep == 0) {
		for (int i = 1; i <= n; i++)
			if (d0[i] <= 1) {
				cerr << "At least one vertex still has potential to be unisolated" << endl;
				return 0;
			}
		cerr << "Correct! You've used " << cnt << "queries." << endl;
	}
	else {
		if (t[rep] < n-1) {
			cerr << "This vertex still has potential to be isolated" << endl;
			return 0;
		}
		if(d0[rep]>1){
		    cerr<<"WA!"<<endl;
		}
		cerr << "Correct! You've used " << cnt << "queries." << endl;
	}
}
