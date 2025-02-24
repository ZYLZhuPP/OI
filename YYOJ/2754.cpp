#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5, B = 2000, inf = 1e9;
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }

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

struct Q {
    int l, r, t, k, id;
    bool operator < (const Q &a) const {
        if (l / B != a.l / B) return l < a.l;
        if (r / B != a.r / B) return r < a.r;
        return t < a.t;
    }
};
vector<Q > qs;

int n, m, q, a[N], b[N], c[N], p[N], op[N], cnt[N], Cnt[N], suf[N], pre[N], L, R, T;
int o[N], d[N], ans[N];

inline void Add(int x) {
    if (!Cnt[x]) {
        if (Cnt[x - 1]) {
            pre[x] = x - 1; suf[x] = suf[x - 1];
            pre[suf[x - 1]] = x; suf[x - 1] = x;
        } else {
            suf[x] = x + 1; pre[x] = pre[x + 1];
            suf[pre[x + 1]] = x; pre[x + 1] = x;
        }
    }
    Cnt[x]++;
}

inline void Del(int x) {
    if (!--Cnt[x]) {
        suf[pre[x]] = suf[x];
        pre[suf[x]] = pre[x];
    }
}

inline void add(int x) {
    Add(++cnt[x]);
    Del(cnt[x] - 1);
}

inline void del(int x) {
    Add(--cnt[x]);
    Del(cnt[x] + 1);
}

inline void upd(int k, int x) {
    if (L <= k && k <= R) del(a[k]), add(x);
    a[k] = x;
}

inline int solve(int K) {
    int t = 0, x = suf[0];
    while (x <= n) o[++t] = x, d[t] = Cnt[x], x = suf[x];
    int res = inf, r = 0, s = 0;
    For (i, 1, t) {
        while (s < K && r < t) s += d[++r];
        if (s >= K) cmin(res, o[r] - o[i]);
        s -= d[i];
    }
    return res<inf? res: -1;
}

int main() {
    io >> n >> q;
    For (i, 1, n) io >> a[i];
    int l, r, k, x;
    For (i, 1, q) {
        io >> op[i];
        if (op[i] == 1) {
            io >> k >> x;
            p[++m] = k; b[m] = a[k]; c[m] = a[k] = x;
        } else {
            io >> l >> r >> k;
            qs.pb({l, r, m, k, i});
        }
    }
    sort(qs.begin(), qs.end());
    L = 1, R = 0, T = m; Cnt[0] = inf; suf[0] = n + 1;
    for (auto &[l, r, t, k, id] : qs) {
        while (l < L) add(a[--L]);
        while (r > R) add(a[++R]);
        while (L < l) del(a[L++]);
        while (R > r) del(a[R--]);
        while (t > T) T++, upd(p[T], c[T]);
        while (T > t) upd(p[T], b[T]), T--;
        ans[id] = solve(k);
    }
    For (i, 1, q) if (op[i] == 2) printf("%d\n", ans[i]);

    return 0;
}
