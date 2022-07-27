#include "operator.h"
#include <iostream>
#include <vector>
namespace {
	int n, Q;
	const int mod = 1e9 + 7;
	std::vector<int> op;
}
int query(std::vector<int> a) {
	++Q;
	assert(a.size() == n + 1);
	int ret = a[0];
	for (int i = 1; i <= n; ++i) {
		assert(0 <= a[i] && a[i] < mod);
		if (op[i - 1] == 0) {
			ret = (ret + a[i]) % mod;
		}
		else {
			ret = 1ll * ret * a[i] % mod;
		}
	}
	return ret;
}
int main() {
	scanf("%d", &n);
	op.resize(n);
	for (int i = 0; i < n; ++i)
		scanf("%d", &op[i]);
	std::vector<int> ret = solve(n);

	assert(ret.size() == n);
	for (int i = 0; i < n; ++i)
		if (ret[i] != op[i]) {
			fprintf(stderr, "Wrong Answer! read %d but expected %d\n", ret[i], op[i]);
			exit(0);
		}
	printf("%d\n", Q);
	return 0;
}
