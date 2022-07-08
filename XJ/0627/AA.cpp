

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct node {
    ll a[2][2];
    ll tag, tag2;
} t[2000010];
void up(int x) {
    cout<<"up "<<x<<" "<<t[x].a[0][0]<<" "<<t[x].a[0][1]<<" "<<t[x].a[1][0]<<" "<<t[x].a[1][1]<<endl;
    t[x].a[0][0] = max(t[x << 1].a[0][0] + t[x << 1 | 1].a[0][0], t[x << 1].a[0][1] + t[x << 1 | 1].a[1][0]);
    t[x].a[0][1] = max(t[x << 1].a[0][0] + t[x << 1 | 1].a[0][1], t[x << 1].a[0][1] + t[x << 1 | 1].a[1][1]);
    t[x].a[1][0] = max(t[x << 1].a[1][0] + t[x << 1 | 1].a[0][0], t[x << 1].a[1][1] + t[x << 1 | 1].a[1][0]);
    t[x].a[1][1] = max(t[x << 1].a[1][0] + t[x << 1 | 1].a[0][1], t[x << 1].a[1][1] + t[x << 1 | 1].a[1][1]);
    cout<<"up "<<x<<" "<<t[x].a[0][0]<<" "<<t[x].a[0][1]<<" "<<t[x].a[1][0]<<" "<<t[x].a[1][1]<<endl;
}
void add(int x, ll k) {
    cout<<"put "<<x<<" "<<k<<endl;
    cout<<" "<<x<<" "<<t[x].a[0][0]<<" "<<t[x].a[0][1]<<" "<<t[x].a[1][0]<<" "<<t[x].a[1][1]<<endl;
    t[x].tag += k;
    t[x].a[0][1] -= k;
    t[x].a[1][0] += k;
    cout<<" "<<x<<" "<<t[x].a[0][0]<<" "<<t[x].a[0][1]<<" "<<t[x].a[1][0]<<" "<<t[x].a[1][1]<<endl;
}
void add2(int x, ll k) {
    cout<<"put2 "<<x<<" "<<k<<endl;
    cout<<" "<<x<<" "<<t[x].a[0][0]<<" "<<t[x].a[0][1]<<" "<<t[x].a[1][0]<<" "<<t[x].a[1][1]<<endl;
    t[x].tag2 += k;
    t[x].a[0][0] = max(0ll, t[x].a[0][0] + k);
    t[x].a[1][0] += k;
    cout<<" "<<x<<" "<<t[x].a[0][0]<<" "<<t[x].a[0][1]<<" "<<t[x].a[1][0]<<" "<<t[x].a[1][1]<<endl;
}
void down(int x) {
    if (t[x].tag) {
        add(x << 1, t[x].tag);
        add(x << 1 | 1, t[x].tag);
        t[x].tag = 0;
    }
    if (t[x].tag2) {
        add2(x << 1, t[x].tag2);
        add2(x << 1 | 1, t[x].tag2);
        t[x].tag2 = 0;
    }
}
void add(int x, int l, int r, int L, int R, ll k) {
    if (l > R || L > r) return;
    cout<<"add "<<x<<" "<<L<<" "<<R<<" "<<k<<endl;
    if (L <= l && r <= R) {
        add(x, k);
        return;
    }
    int mid = l + r >> 1;
    down(x);
    add(x << 1, l, mid, L, R, k);
    add(x << 1 | 1, mid + 1, r, L, R, k);
    up(x);
}
void add2(int x, int l, int r, int L, int R, ll k) {
    if (l > R || L > r) return;
    cout<<"add2 "<<x<<" "<<L<<" "<<R<<" "<<k<<endl;
    if (L <= l && r <= R) {
        add2(x, k);
        return;
    }
    int mid = l + r >> 1;
    down(x);
    add2(x << 1, l, mid, L, R, k);
    add2(x << 1 | 1, mid + 1, r, L, R, k);
    up(x);
}
void modify(int x, int l, int r, int k, ll v) {
    cout<<"modi "<<x<<" "<<l<<" "<<r<<endl;
    if (l == r) {
        t[x].a[0][0] = max(0ll, t[x].tag2 += v);
        t[x].a[1][0] += v;
        return;
    }
    int mid = l + r >> 1;
    down(x);
    if (k <= mid) modify(x << 1, l, mid, k, v);
    else modify(x << 1 | 1, mid + 1, r, k, v);
    up(x);
}
int q, n, l;
ll m;
int opt[500010], a[500010], c[500010];
pair < int, int > b[500010];
int main() {
    scanf("%d%d", &q, &l);
    for (int i = 1; i <= q; i++) {
        scanf("%d%d%d", opt + i, a + i, c + i);
        if (opt[i] == 1) b[++n] = {a[i], i};
    }
    sort(b + 1, b + 1 + n);
    for (int i = 1; i <= n; i++) a[b[i].second] = i;
    for (int i = 1; i <= q; i++) {
        if (opt[i] == 1) {
            add(1, 1, n, a[i] + 1, n, c[i]);
            modify(1, 1, n, a[i], c[i]);
            m += c[i];
        }
        else {
            int L, R;
            L = lower_bound(b + 1, b + 1 + n, make_pair(a[i] - l, -1)) - b;
            R = upper_bound(b + 1, b + 1 + n, make_pair(a[i] + l, q + 1)) - b - 1;
            add(1, 1, n, R + 1, n, -c[i]);
            add2(1, 1, n, L, R, -c[i]);
        }
        printf("%lld\n", m - t[1].a[0][0]);
    }
}


