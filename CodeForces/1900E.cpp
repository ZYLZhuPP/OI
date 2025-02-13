#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 2e5 + 5;
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }

struct IO {
	char c; int f;
	#define gc() (getchar())
	template<class C>
	inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
	}
	inline bool operator ~ () const { return ~c; }
} io;

vector<int > es[N], pt[N];
int T, n, m, dfn[N], low[N], tim, co[N], color, stk[N], top, cnt[N], ans1, a[N];
ll w[N], val[N], ans2;

void Tarjan(int u) {
    dfn[u] = low[u] = ++tim; stk[++top] = u;
    for (auto &v : es[u])
        if (!dfn[v]) Tarjan(v), cmin(low[u], low[v]);
        else if (!co[v]) cmin(low[u], dfn[v]);
    if (low[u] == dfn[u]) {
        color++;
        do co[stk[top]] = color, pt[color].pb(stk[top]), w[color] += a[stk[top]];
        while (stk[top--] ^ u);
    }
}

inline void solve() {
    tim = color = ans1 = ans2 = 0;
    io >> n >> m;
    For (i, 1, n) io >> a[i];
    int u, v;
    For (i, 1, m) io >> u >> v, es[u].pb(v);
    For (i, 1, n) if (!dfn[i]) Tarjan(i);
    rFor (i, color, 1) {
        cnt[i] += pt[i].size(); val[i] += w[i];
        if (cnt[i] > ans1) ans1 = cnt[i], ans2 = val[i];
        else if (cnt[i] == ans1) cmin(ans2, val[i]);
        for (auto &u : pt[i]) {
            int j; for (auto &v : es[u]) if ((j = co[v]) ^ i) {
                if (cnt[i] > cnt[j]) cnt[j] = cnt[i], val[j] = val[i];
                else if (cnt[i] == cnt[j]) cmin(val[j], val[i]);
            }
        }
    }
    printf("%d %lld\n", ans1, ans2);
    For (i, 1, n) dfn[i] = cnt[i] = val[i] = co[i] = w[i] = 0, es[i].resize(0), pt[i].resize(0);
}

int main() {
    io >> T;
    while (T--) solve();

    return 0;
}
