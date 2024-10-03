#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef vector<int > vec;
typedef unsigned long long ull;
const int N = 505;

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

int n, m, D[N], d[N], ans;

struct Bits {
    ull o[8];
    Bits() { memset(o, 0, sizeof o); }
    inline void upd(int x) { o[x / 64] ^= 1ull << (x % 64); }
    inline vec get(const Bits &a) {
        vec r;
        For (i, 0, 7) {
            ull x = ~o[i] & a.o[i];
            if (x) {
                int k = 63 - __builtin_clzll(x);
                r.pb(i * 64 + k);
                x ^= 1ull << k;
                o[i] ^= 1ull << k;
            }
        }
        return r;
    }
} G[N], F[N], g[N], f[N];

inline bool ok(int K) {
    For (i, 0, n) g[i] = G[i], f[i] = F[i], d[i] = D[i];
    int cnt = n * (n - 1) / 2 - m;
    queue<int > q;
    For (i, 1, n) {
        int x = max(0, K - d[i]);
        if (x < n) {
            vec a = g[i].get(f[x]);
            for (auto &j : a) g[j].upd(i), q.push(i), q.push(j), cnt--;
        }
    }
    while (cnt && !q.empty()) {
        int i = q.front(); q.pop();
        d[i]++; f[d[i]].upd(i);
        int x = max(0, K - d[i]);
        if (x < n) {
            vec a = g[i].get(f[x]);
            for (auto &j : a) g[j].upd(i), q.push(i), q.push(j), cnt--;
        }
    }
    return !cnt;
}

int main() {
    io >> n >> m;
    For (i, 1, n) G[i].upd(i);
    int u, v;
    For (i, 1, m) {
        io >> u >> v;
        G[u].upd(v); G[v].upd(u);
        D[u]++; D[v]++;
    }
    For (i, 1, n) For (j, 0, D[i]) F[j].upd(i);
    int l = 0, r = 2 * n;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (ok(mid)) ans = mid, l = mid + 1;
        else r = mid - 1;
    }
    printf("%d", ans);

    return 0;
}
