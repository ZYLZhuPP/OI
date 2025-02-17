#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
typedef long long ll;
const int N = 1e5 + 5, Mo = 1e9 + 7;
template<class C> inline void cmax(C &x, const C &y) { x = y>x? y: x; }
inline int mo(int x) { return x -= x>=Mo? Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(ll x, ll y) { x %= Mo; y %= Mo; return 1ll * x * y % Mo; }

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

int n, m, vis[N], ans, S, pt[N], cnt;
ll val[N];
vector<pair<int, ll > > G[N];

struct Basis {
    static const int B = 60;
    ll o[B]; bool zero;
    Basis() { memset(o, 0, sizeof o); zero = 0; }
    bool ins(ll x) {
        rFor (i, B - 1, 0) if (x >> i & 1) {
            if (!o[i]) return o[i] = x, 1;
            else x ^= o[i];
        }
        return zero = 1, 0;
    }
} B;

void dfs(int u) {
    pt[++cnt] = u;
    vis[u] = 1;
    for (auto &[v, w] : G[u]) 
        if (!vis[v]) val[v] = val[u] ^ w, dfs(v);
        else S += B.ins(val[u] ^ val[v] ^ w);
}

int main() {
    io >> n >> m;
    int u, v; ll w;
    For (i, 1, m) io >> u >> v >> w, G[u].pb({v, w}), G[v].pb({u, w});
    For (u, 1, n) if (!vis[u]) {
        cnt = S = 0;
        B = Basis();
        dfs(u);
        For (i, 0, 59) {
            int flag = 0, x[2] = {0, 0};
            For (j, 0, 59) flag |= B.o[j] >> i & 1;
            For (j, 1, cnt) x[val[pt[j]] >> i & 1]++;
            For (j, 1, cnt) {
                if (flag) add(ans, ml(1ll << i, ml(1ll << (S - 1), cnt - 1)));
                else add(ans, ml(1ll << i, ml(1ll << S, x[~val[pt[j]] >> i & 1])));
            }
        }
    }
    printf("%d", ml(ans, 5e8 + 4));
    
    return 0;
}
