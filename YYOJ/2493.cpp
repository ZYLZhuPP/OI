#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 2e5 + 5, inf = 1e9;

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

int n, sz[N], fa[N];
ll ans;
vector<int > son[N];

inline void solve(int u) {
    int res = 0;
    For (o, 0, 50) {
        int s = 0;
        multiset<int > se;
        for (auto &v : son[u]) se.insert(sz[v]);
        while (!se.empty()) {
            multiset<int >::iterator p[3];
            int tot = 1;
            p[0] = se.upper_bound(sz[u] / 2 - s);
            if (p[0] == se.end()) p[0] = prev(p[0]);
            For (i, 0, 1) if (p[i] != se.begin()) p[tot++] = prev(p[i]); else break;
            int x = *p[0], y = tot>1? *p[1]: inf;
            if (abs(2 * s - sz[u]) <= min(abs(2 * s + 2 * x - sz[u]), abs(2 * s + 2 * y - sz[u]))) break;
            int k = rand() % tot, z = *p[k];
            s += z; se.erase(p[k]); se.insert(-z);
        }
        if (abs(2 * s - sz[u]) < abs(2 * res - sz[u])) res = s;
		if (son[u].size() > n / 2) break;
    }
    ans += 1ll * res * (sz[u] - res);
}

int main() {
    srand(time(0));
    io >> n;
    For (i, 2, n) io >> fa[i];
    rFor (i, n, 1) {
        solve(i);
        sz[i]++;
        son[fa[i]].pb(i);
        sz[fa[i]] += sz[i];
    }
    printf("%lld", ans);

    return 0;
}
