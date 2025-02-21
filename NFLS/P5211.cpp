#include<ext/pb_ds/priority_queue.hpp>
#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 3e5 + 5;

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

int n, a[N];
vector<int > es[N];
__gnu_pbds::priority_queue<ll > q[N];

inline void dfs(int u, int pre) {
    for (auto &v : es[u]) if (v ^ pre) dfs(v, u), q[u].join(q[v]);
    ll s = a[u];
    For (i, 1, 2) if (!q[u].empty()) s += q[u].top(), q[u].pop();
    q[u].push(s);
}

int main() {
    freopen("travel.in", "r", stdin);
    freopen("travel.out", "w", stdout);
    io >> n;
    For (i, 1, n) io >> a[i];
    int u, v;
    For (i, 1, n - 1) io >> u >> v, u++, v++, es[u].pb(v), es[v].pb(u);
    dfs(1, 0);
    printf("%lld", q[1].top());

    fclose(stdin); fclose(stdout);
    return 0;
}