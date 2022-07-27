#include "Participant.h"
#include <vector>

namespace {
}

int Query(int x, int col, int deg, std::vector<int> tar, std::vector<int> cols) {
  for (int i = 0; i < deg; i++) {
    int v = tar[i], c = cols[i];
    if (x < v && c == col) {
      return v;
    }
    if (x > v && c != col) {
      return v;
    }
  }
  return x;
}
