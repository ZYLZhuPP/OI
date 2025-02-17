#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define pb push_back
const int N = 1e5 + 5, _N = 320, M = 1e6 + 5;

struct IO {
    char c; int f;
#define gc() getchar()
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
    }
    inline bool operator ~ () const { return ~c; }
} io;

int n, m, S, a[N], s[N], cnt[_N], be[N], bl[_N], br[_N];
int ans[M];

struct OP {
    int x, y, a, b, id;
    bool operator < (const OP &a) const { return x/S^a.x/S? x/S<a.x/S: y<a.y; }
};
vector<OP > ops;

void init() {
    For (i, 1, 317) bl[i] = br[i - 1] + 1, br[i] = i * 316;
    br[317] = N - 1;
    For (i, 1, 317) For (j, bl[i], br[i]) be[j] = i;
    S = sqrt(n);
}

inline void add(int x) {
    cnt[be[x]] += !s[x]++;
}

inline void del(int x) {
    cnt[be[x]] -= !--s[x];
}

inline void solve(int l, int r, int id) {
    int L = be[l], R = be[r];
    For (i, l, min(br[L], r)) if (s[i]) ans[id]++;
    For (i, L + 1, R - 1) ans[id] += cnt[i];
    if (L ^ R) For (i, bl[R], r) if (s[i]) ans[id]++;
}

int main() {
    io >> n >> m;
    init();
    For (i, 1, n) io >> a[i];
    int l, r, x, y;
    For (i, 1, m) io >> l >> r >> x >> y, ops.pb({l, r, x, y, i});
    sort(ops.begin(), ops.end());
    l = 1, r = 0;
    for (auto &[L, R, x, y, id] : ops) {
        while (l > L) add(a[--l]);
        while (r < R) add(a[++r]);
        while (l < L) del(a[l++]);
        while (r > R) del(a[r--]);
        solve(x, y, id);
    }
    For (i, 1, m) printf("%d\n", ans[i]);

    return 0;
}
