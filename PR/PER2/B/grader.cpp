#include "Participant.h"
#include "Spy.h"
#include <algorithm>
#include <cstdio>
#include <vector>

int main() {
  int N, S, T;
  scanf("%d%d%d", &N, &S, &T);
  std::vector<int> A(N - 1), B(N - 1);
  for (int i = 0; i < N - 1; ++i)
    scanf("%d%d", &A[i], &B[i]);
  std::vector<int> X = Init(N, T, A, B);
  std::vector<int> P, Q;
  for (int i = 0; i < N - 1; ++i)
    if (A[i] == S || B[i] == S) {
      int x = (A[i] == S ? B[i] : A[i]);
      P.push_back(x);
      Q.push_back(X[x - 1]);
    }
  printf("%d\n", Query(S, X[S - 1], P.size(), P, Q));
  printf("%d\n", *std::max_element(X.begin(), X.end()));
}
