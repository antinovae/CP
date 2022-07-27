
#include "operator.h"
#include <vector>
using namespace std;

namespace {
const int a[] = {887377558, 214481174, 71242312, 117771049, 956987625, 98510206, 128414996, 226167609, 725732213, 958193142, 788173257, 276088311, 19518105, 939561443, 366973067}, mo = 1e9 + 7;
}

std::vector<int> solve(int n) {
  vector<int> ans(n);
  int pos = n;
  while (pos > 0) {
    int pre = max(pos - 15, 0);
    vector<int> q;
    for (int i = 0; i <= pre; ++i)
      q.push_back(0);
    for (int i = pre + 1; i <= pos; ++i)
      q.push_back(a[i - pre - 1]);
    for (int i = pos + 1; i <= n; ++i)
      q.push_back(ans[i - 1]);
    int res = query(q);
    for (int i = 0; i < 1 << (pos - pre); ++i) {
      int sum = 0;
      for (int j = 0; j < (pos - pre); ++j)
        if (i >> j & 1)
          sum = (sum + a[j]) % mo;
        else
          sum = 1ll * sum * a[j] % mo;
      if (res == sum) {
        for (int j = 0; j < (pos - pre); ++j) {
          ans[pre + j] = ~i >> j & 1;
        }
        break;
      }
    }
    pos = pre;
  }
  return ans;
}
