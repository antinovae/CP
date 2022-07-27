#include <bits/stdc++.h>
using namespace std;
const int N = 100001;
using ll = long long;

struct info {
  ll mx, mn;

  info operator+(ll x) {
    return (info){mx + x, mn + x};
  }

  void reverse() {
    swap(mx, mn);
    mx = -mx, mn = -mn;
  }
};

info merge(info a, info b) {
  return {a.mx + b.mx, a.mn + b.mn};
}

info chk(info a, info b) {
  return {max(a.mx, b.mx), min(a.mn, b.mn)};
}

info chk(initializer_list<info> s) {
  auto [mx, mn] = *s.begin();
  for (auto [x, y] : s) {
    mx = max(x, mx);
    mn = min(y, mn);
  }
  return {mx, mn};
}

struct seg {
  info pre, suf, full;
  int sum, tag;

  void reverse() {
    tag ^= 1;
    pre.reverse(), suf.reverse(), full.reverse();
    sum = -sum;
  }
};

seg t[N * 4];

void pushdown(int x) {
  if (t[x].tag) {
    t[x << 1].reverse();
    t[x << 1 | 1].reverse();
    t[x].tag ^= 1;
  }
}

void pushup(int x) {
  t[x].pre = chk(t[x << 1].pre, t[x << 1 | 1].pre + t[x << 1].sum);
  t[x].suf = chk(t[x << 1 | 1].suf, t[x << 1].suf + t[x << 1 | 1].sum);
  t[x].full = chk({t[x << 1].full,
                   t[x << 1 | 1].full,
                   /* t[x].pre, */
                   /* t[x].suf, */
                   merge(t[x << 1].suf,
                         t[x << 1 | 1].pre)});
  t[x].sum = t[x << 1].sum + t[x << 1 | 1].sum;
}

void modify_l_fixed(int x, int l, int r) {
  if (l == r) {
    t[x].reverse();
  }
  else {
    pushdown(x);
    int mid = (l + r) / 2;
    if (t[x].full.mx == t[x << 1].full.mx) {
      modify_l_fixed(x << 1, l, mid);
    }
    else {
      t[x << 1].reverse();
      modify_l_fixed(x << 1 | 1, mid + 1, r);
    }
    pushup(x);
  }
}

void modify_r_fixed(int x, int l, int r) {
  if (l == r) {
    t[x].reverse();
  }
  else {
    pushdown(x);
    int mid = (l + r) / 2;
    if (t[x].full.mx == t[x << 1 | 1].full.mx) {
      modify_r_fixed(x << 1 | 1, mid + 1, r);
    }
    else {
      t[x << 1 | 1].reverse();
      modify_r_fixed(x << 1, l, mid);
    }
    pushup(x);
  }
}

void modify(int x, int l, int r) {
  if (l == r) {
    t[x].reverse();
  }
  else {
    pushdown(x);
    int mid = (l + r) / 2;
    if (t[x].full.mx == t[x << 1].full.mx) {
      modify(x << 1, l, mid);
    }
    else if (t[x].full.mx == t[x << 1 | 1].full.mx) {
      modify(x << 1 | 1, mid + 1, r);
    }
    else {
      modify_r_fixed(x << 1, l, mid);
      modify_l_fixed(x << 1 | 1, mid + 1, r);
    }
    pushup(x);
  }
}

int a[N];

void build(int x, int l, int r) {
  if (l == r) {
    t[x].pre = t[x].suf = t[x].full = {a[l], a[l]};
    t[x].sum = a[l];
  }
  else {
    int mid = (l + r) / 2;
    if (l <= mid)
      build(x << 1, l, mid);
    if (r > mid)
      build(x << 1 | 1, mid + 1, r);
    pushup(x);
  }
}

void pr(int x, int l, int r) {
  cout << x << " " << l << " " << r <<                   //
      " full " << t[x].full.mx << " " << t[x].full.mn << //
      " pre " << t[x].pre.mx << " " << t[x].pre.mn <<    //
      " suf " << t[x].suf.mx << " " << t[x].suf.mn <<    //
      " tag " << t[x].tag << endl;
  if (l == r) {
  }
  else {

    int mid = (l + r) / 2;
    if (l <= mid)
      pr(x << 1, l, mid);
    if (r > mid)
      pr(x << 1 | 1, mid + 1, r);
  }
}

int main() {
  int n;
  scanf("%d", &n);
  int sum = 0;
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    sum += a[i];
  }
  ll K;
  scanf("%lld", &K);
  build(1, 1, n);
  static ll f[N];
  int m = sum;
  for (int i = 1; i <= n; i++) {
    f[i] = t[1].full.mx;
    if (f[i] >= 0) {
      f[i] = sum - f[i];
      m = i;
      cout << "round " << i << " " << f[i] << endl;
      /* pr(1, 1, n); */
      modify(1, 1, n);
    }
  }
  /* vector<int> st; */
  /* auto get_inter = [&](int x, int y) { */
  /*   return (double)(f[y] - f[x]) / (double)(x - y); */
  /* }; */
  /* auto cal = [&](int v, ll x) -> ll { */
  /*   return x * v + f[v]; */
  /* }; */
  /* static double p[N]; */
  /* for (int i = m; i >= 1; i--) { */
  /*   while (st.size() >= 2) { */
  /*     p[i] = get_inter(st.back(), i); */
  /*     if (p[i] <= p[st.back()]) */
  /*       st.pop_back(); */
  /*     else */
  /*       break; */
  /*   } */
  /*   p[i] = get_inter(st.back(), i); */
  /*   st.push_back(i); */
  /* } */
  /* static ll l[N], r[N]; */
  /* for (int i = 0; i < st.size(); i++) { */
  /*   if (i > 0) */
  /*     l[st[i]] = max((ll)(ceil(p[st[i]])), 1ll); */
  /*   else */
  /*     l[i] = 1; */
  /*   if (i < st.size() - 1) { */
  /*     r[st[i]] = min((ll)(floor(p[st[i + 1]])), K); */
  /*   } */
  /* } */
  /* ll ans = 0; */
  /* for (int i = 0; i < st.size(); i++) { */
  /*   int x = st[i]; */
  /*   ll res = (l[x] + r[x] - 1) * (r[x] - l[x]) / 2; */
  /*   ans += res * x; */
  /*   if (i < st.size() - 1) { */
  /*     int y = st[i + 1]; */
  /*     ll res = (cal(y, l[y]) - cal(x, r[x])) * r[x]; */
  /*     ans += res; */
  /*   } */
  /* } */
  /* cout << ans << endl; */
}
