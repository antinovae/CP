#include <bits/stdc++.h>
using namespace std;
const int N = 3005;
int a[N][N];
int st[N];

int main() {
  int n;
  static char s[N];
  scanf("%d", &n);
  for (int i = 2; i <= n; i++) {
    scanf("%s", s + 1);
    for (int j = 1; j < i; j++) {
      a[i][j] = s[j] == '1';
    }
  }
  int idx = 0;
  for (int i = 0; i < (1 << 14) && idx < n; i++) {
    if (__builtin_popcount(i) == 7) {
      st[++idx] = i;
    }
  }
  for (int i = 2; i <= n; i++) {
    for (int j = 1; j < i; j++) {
      for (int k = 0; k < 14; k++) {
        if (a[i][j]) {
          if ((st[i] >> k & 1) && !(st[j] >> k & 1)) {
            putchar('a' + k);
            break;
          }
        }
        else {
          if (!(st[i] >> k & 1) && (st[j] >> k & 1)) {
            putchar('a' + k);
            break;
          }
        }
      }
    }
    puts("");
  }
}
