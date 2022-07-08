#include <stdio.h>
#include <cstdlib>
#include <iostream>
using namespace std;
inline char gc() {
    return getchar();
    /* static char buf[1048580], *p1 = buf, *p2 = buf; */
    /* return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1048576, stdin), p1 == p2) ? EOF : *p1++; */
}
inline int read() {
    int x = 0;
    char ch = gc();

    while (ch < '0' || ch > '9') {
        ch = gc();
    }

    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = gc();
    }

    return x;
}
int Sgyuzwmreg87928[55][1010], Dsbqhrvgjg94635;
int Iujxecswgw89067, Vvkdhktmiv24781, Ybvrruilwi79848;
int query(int x, int y) {
    if (x < 1 || x > Iujxecswgw89067 || y < 1 || y > Vvkdhktmiv24781) {
        cerr << "Wrong parameter for query() on test " << Ybvrruilwi79848 << endl;
        exit(0);
    }

    Dsbqhrvgjg94635++;

    if (Dsbqhrvgjg94635 > 100000) {
        cerr << "Query too much on test " << Ybvrruilwi79848 << endl;
        exit(0);
    }

    return Sgyuzwmreg87928[x][y];
}
void guess(int num_testcase, int N, int M, int K);
int main() {
    /* freopen("inter.in", "r", stdin); */
    /* freopen("inter.out", "w", stdout); */
    int T = read(), maxcnt = 0;

    for (int i = 1; i <= T; i++) {
        int n = read(), m = read(), k = read();

        for (int I = 1; I <= n; I++) {
            for (int J = 1; J <= m; J++) {
                Sgyuzwmreg87928[I][J] = read();
            }
        }

        Iujxecswgw89067 = n;
        Vvkdhktmiv24781 = m;
        Dsbqhrvgjg94635 = 0;
        Ybvrruilwi79848 = i;
        guess(i, n, m, k);
        maxcnt = max(maxcnt, Dsbqhrvgjg94635);
    }

    cerr << "Number of queries: " << maxcnt << endl;
    return 0;
}
