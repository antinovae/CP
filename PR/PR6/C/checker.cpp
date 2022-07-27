/*
 * Sample Grader for PR #6 communication2
 */

#include <cstdio>
#include <cassert>
#include <algorithm>
#include <vector>

int main(int argc, char **argv) {
	if (argc != 3) {
		fprintf(stderr, "Usage: ./checker <input-file> <output-file>");
		return 0;
	}
	FILE *fin = fopen(argv[1], "r");
	FILE *fout = fopen(argv[2], "r");
	int N, M, Q, K;
	assert(4 == fscanf(fin, "%d%d%d%d", &N, &M, &Q, &K));
	std::vector<int> U(M), V(M), S(Q), T(Q), E(K);
	std::vector<long long> W(M), D(Q);
	std::vector<std::vector<long long>> G(N, std::vector<long long>(N, -1));
	for (int i = 0; i < M; ++i) {
		assert(3 == fscanf(fin, "%d%d%lld", &U[i], &V[i], &W[i]));
		G[U[i]][V[i]] = W[i];
	}
	for (int i = 0; i < Q; ++i) {
		assert(2 == fscanf(fin, "%d%d", &S[i], &T[i]));
	}
	for (int i = 0; i < K; ++i) {
		assert(1 == fscanf(fin, "%d", &E[i]));
	}
	std::vector<std::vector<long long>> dist(N, std::vector<long long>(N, 3e18));
	for (int i = 0; i < N; ++i)
		dist[i][i] = 0;
	for (int i = 0; i < M; ++i)
		dist[U[i]][V[i]] = W[i];
	for (int k = 0; k < N; ++k)
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < N; ++j)
				dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
	for (int i = 0; i < Q; ++i) {
		int k;
		assert(1 == fscanf(fout, "%d", &k));
		std::vector<int> P(k);
		for (int i = 0; i < k; ++i) {
			assert(1 == fscanf(fout, "%d", &P[i]));
			if (!(0 <= P[i] && P[i] < M)) {
				fprintf(stderr, "invalid output\n");
				return 0;
			}
		}
		long long cost = 0;
		if (U[P[0]] != S[i]) {
			fprintf(stderr, "wrong answer\n");
			return 0;
		}
		if (V[P[k - 1]] != T[i]) {
			fprintf(stderr, "wrong answer\n");
			return 0;
		}
		for (int i = 0; i + 1 < k; ++i) {
			if (V[P[i]] != U[P[i + 1]]) {
				fprintf(stderr, "invalid path\n");
				return 0;
			}
		}
		for (int i = 0; i < k; ++i)
			cost += W[P[i]];
		long long realCost = dist[S[i]][T[i]];
		if (cost != realCost) {
			fprintf(stderr, "the length of your path is %lld, but expected %lld\n", cost, realCost);
			return 0;
		}
	}
	fprintf(stderr, "Correct.\n");
}
