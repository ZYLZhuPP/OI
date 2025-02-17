#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e5 + 5;

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

int n, q, pos[N];
ll w[N], a[N * 80], ans[N << 1];
char s[N];
vector<int > T[N << 1];
vector<ll > vis[N << 1];

struct Basis {
    static const int B = 40;
    ll o[B];
    Basis() { memset(o, 0, sizeof o); }
    inline bool ins(ll x) {
        rFor (i, B - 1, 0) if (x >> i & 1) {
            if (!o[i]) return o[i] = x, 1;
            else x ^= o[i];
        }
        return 0;
    }
} B[N << 1];

namespace SAM {
    int to[N << 1][5], fa[N << 1][18], len[N << 1], cnt[N << 1], tot = 1, ed = 1;
    inline int upd(int p, const int c) {
        int q = to[p][c];
        if (len[q] == len[p] + 1) return q;
        int nq = ++tot; memcpy(to[nq], to[q], sizeof to[q]);
        fa[nq][0] = fa[q][0]; fa[q][0] = nq; len[nq] = len[p] + 1;
        while (p && to[p][c] == q) to[p][c] = nq, p = fa[p][0];
        return nq;
    }
    inline void add(const int c) {
        int p = ed, np = ed = ++tot; len[np] = len[p] + 1; cnt[np] = 1;
        while (p && !to[p][c]) to[p][c] = np, p = fa[p][0];
        fa[np][0] = p? upd(p, c): 1;
    }
    inline void ins(const char *s) {
        int n = strlen(s + 1);
        For (i, 1, n) add(s[i] - 'a');
    }
}
using namespace SAM;

inline void dfs(int u) {
    For (i, 1, 17) fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for (auto &v : T[u]) dfs(v), cnt[u] += cnt[v];
    int tot = 1; a[tot] = w[cnt[u]];
    for (auto &v : T[u]) for (auto &x : vis[v]) a[++tot] = x;
    sort(a + 1, a + tot + 1); tot = unique(a + 1, a + tot + 1) - a - 1;
    rFor (i, tot, 1) if (B[u].ins(a[i])) ans[u] += a[i], vis[u].pb(a[i]);
}

inline void solve() {
    ed = tot = 1;
    io >> n;
    scanf("%s", s + 1);
    For (i, 1, n) io >> w[i];
    ins(s);
    For (i, 2, tot) T[fa[i][0]].pb(i);
    dfs(1);
    pos[0] = 1;
    For (i, 1, n) pos[i] = to[pos[i - 1]][s[i] - 'a'];
    io >> q;
    int l, r;
    while (q--) {
        io >> l >> r;
        int u = pos[r];
        rFor (i, 17, 0) if (len[fa[u][i]] >= r - l + 1) u = fa[u][i];
        printf("%lld\n", ans[u]);
    }
    memset(to, 0, sizeof to);
    memset(cnt, 0, sizeof cnt);
    memset(ans, 0, sizeof ans);
    For (i, 1, tot) T[i].resize(0), vis[i].resize(0), B[i] = Basis();
}

int main() {
    int T; io >> T;
    while (T--) solve();

    return 0;
}
