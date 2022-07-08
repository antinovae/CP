#include <bits/stdc++.h>
using namespace std;
const int maxn = 5000005;
char s[maxn], t[maxn], str[maxn];
int nxt[maxn],S[maxn];

inline void kmp(char t[]) {
  int m = (int)strlen(t + 1);
  nxt[1] = 0;
  int i = 1, j = 0;
  while (i <= m) {
    if (j && t[i] != t[j])
      j = nxt[j];
    else
      nxt[++i] = ++j;
  }
}

int a[maxn];

void brute_1(int n) {
  int m = (int)strlen(t + 1), num = 0, Q;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= a[i]; j++) {
      str[++num] = s[j];
    }
  }
  int i = 1;
  for (int k = 1; k <= num; k++) {
    S[k] = S[k - 1];
    while (i && t[i] != str[k]) {
      i = nxt[i];
    }
    if ((++i) == m + 1) {
      i = nxt[i], S[k]++;
    }
  }
  scanf("%d", &Q);
  while (Q--) {
    int l, r;
    scanf("%d%d", &l, &r);
    printf("%d\n", max(0, S[r] - S[min(num, l + m - 2)]));
  }
}

void brute_2(int l,int r){
  for(int i=l;i<=r;i++){

  }

}
int main() {
  freopen("youl.in", "r", stdin);
  freopen("youl.out", "w", stdout);
  int n;
  scanf("%s%s%d", s + 1, t + 1, &n);
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]);
  kmp(t);
  brute_1(n);
}
