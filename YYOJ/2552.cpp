#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef vector<int > V;
const int N = 1e5 + 5;
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

int n, m, q, K, tot, B, es[N], ad[55][32], to[55][32], Ad[350][55], To[350][55];
int bl[350], br[350], be[N];
map<V, int > mp;

inline void dfs(V a) {
    int k = a.size();
    if (k == K) return mp[a] = ++tot, void();
    a.pb(k); dfs(a);
    For (i, 0, k - 1) if (a[i] == i) a[k] = i, dfs(a);
}

inline void init() {
    dfs(V());
    for (auto [a, id] : mp) {
        For (s, 0, (1 << K) - 1) {
            V b = a; bitset<5 > vis;
            For (i, 0, K - 1) if (s >> i & 1 && !vis[b[i]]) vis[b[i]] = 1, ad[id][s]++;
            int x = K;
            For (i, 0, K - 1) if (vis[b[i]]) b[i] = x<K? x: (x = i);
            b.pb(x);
            x = -1;
            For (i, 1, K) if (!b[i]) b[i] = ~x? x: (x = i);
            b.erase(b.begin());
            For (i, 0, K - 1) b[i]--;
            to[id][s] = mp[b];
        }
    }
}

int main() {
    io >> n >> K >> m; B = sqrt(n);
    init();
    int u, v;
    For (i, 1, m) {
        io >> u >> v;
        if (u > v) swap(u, v);
        es[v] |= 1 << (K - (v - u));
    }
    For (i, 1, B) bl[i] = br[i - 1] + 1, br[i] = i * B;
    br[B] = n;
    For (i, 1, B) For (j, bl[i], br[i]) be[j] = i;
    For (i, 1, B) {
        For (j, 1, tot) {
            int x = j, s = 0;
            For (k, bl[i], br[i]) s += ad[x][es[k]], x = to[x][es[k]];
            To[i][j] = x; Ad[i][j] = s;
        }
    }
    io >> q;
    while (q--) {
        int l, r;
        io >> l >> r;
        int x = 1, s = r - l + 1, y = min(r, l + K - 1);
        For (i, l + 1, y) {
            int z = es[i] >> (K - i + l) << (K - i + l);
            s -= ad[x][z]; x = to[x][z];
        }
        if (y == r) { printf("%d\n", s); continue; }
        l = y + 1;
        int L = be[l], R = be[r];
        if (L == R) For (i, l, r) s -= ad[x][es[i]], x = to[x][es[i]];
        else {
            For (i, l, br[L]) s -= ad[x][es[i]], x = to[x][es[i]];
            For (i, L + 1, R - 1) s -= Ad[i][x], x = To[i][x];
            For (i, bl[R], r) s -= ad[x][es[i]], x = to[x][es[i]];
        }
        printf("%d\n", s);
    }

    return 0;
}
