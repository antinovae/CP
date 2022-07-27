/*
 * Sample Grader for PR #6 communication2
 */
#include "Participant.h"
#include "Spy.h"
//#include "QOJManagerLib.h"
#include <cassert>

void Report(std::vector<int>);

namespace {

namespace QOJManager {
constexpr int Lim = 1000;
int N, M, Q, K;
std::vector<int> U, V, S, T, E;
std::vector<std::vector<int>> Answer;
std::vector<long long> W;

class dummy {
public:
  dummy() {
    assert(4 == scanf("%d%d%d%d", &N, &M, &Q, &K));
    U = std::vector<int>(M);
    V = std::vector<int>(M);
    W = std::vector<long long>(M);
    for (int i = 0; i < M; ++i)
      assert(3 == scanf("%d%d%lld", &U[i], &V[i], &W[i]));
    S = std::vector<int>(Q);
    T = std::vector<int>(Q);
    for (int i = 0; i < Q; ++i)
      assert(2 == scanf("%d%d", &S[i], &T[i]));
    E = std::vector<int>(K);
    for (int i = 0; i < K; ++i)
      assert(1 == scanf("%d", &E[i]));
  }
} _;

void firstInteractionValidation(std::string S) {
  if (S.length() > Lim) {
    fprintf(stderr, "First Interaction Error: Length Limit Exceeded");
    exit(0);
  }
  for (char ch : S)
    if (ch != '0' && ch != '1') {
      fprintf(stderr, "First Interaction Error: The returned string contains other characters.");
      exit(0);
    }
}

void secondInteractionValidation() {
  if (Answer.size() != Q) {
    fprintf(stderr, "Second Interaction Error: You should call Report() exactly Q times!");
    exit(0);
  }
}

void Report(std::vector<int> P) {
  if (P.size() < 1 || P.size() > N) {
    fprintf(stderr, "Second Interaction Error: Invalid Answer for Query #%d", (int)Answer.size());
    exit(0);
  }
  Answer.push_back(P);
}

void managerReportAnswer() {
  for (int i = 0; i < Q; ++i) {
    fprintf(stdout, "%d", Answer[i].size());
    for (int x : Answer[i])
      fprintf(stdout, " %d", x);
    fprintf(stdout, "\n");
  }
  fflush(stdout);
}

void startInteraction() {
  std::string Z = SpySolve(N, M, Q, K, U, V, W, S, T, E);
  int L = Z.length();
  firstInteractionValidation(Z);
  for (int i = 0; i < K; ++i)
    W[E[i]] = -1;
  ParticipantSolve(N, M, Q, K, U, V, W, S, T, E, Z);
  secondInteractionValidation();
  managerReportAnswer();
}
} // namespace QOJManager

void __main() {
  QOJManager::startInteraction();
}
} // namespace

void Report(std::vector<int> P) {
  QOJManager::Report(P);
}

int main() {
  __main();
  return 0;
}
