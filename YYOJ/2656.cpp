#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5, Mo = 998244353;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }

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

int n, m, cnt[4], ans, _2[N];
vector<int > es[N];

inline int dfs(int u) {
    int cnt[4] = {0, 0, 0, 0};
    for (auto &v : es[u]) cnt[dfs(v)]++;
    if ((cnt[0] && cnt[1]) || cnt[3]) return 2;
    if (cnt[0]) return 1;
    if (cnt[1]) return 0;
    if (cnt[2]) return 3;
    return 1;
}

int main() {
    _2[0] = 1; For (i, 1, N - 1) _2[i] = mo(_2[i - 1] << 1);
    es[0].pb(1);
    io >> m;
    For (i, 1, m) {
        io >> n;
        es[1].resize(0);
        int x;
        For (i, 2, n) io >> x, es[x].pb(i), es[i].resize(0);
        cnt[dfs(0)]++;
    }
    if (cnt[2]) add(ans, ml(_2[cnt[2]] - 1, _2[m - cnt[2]]));
    if (cnt[1]) add(ans, _2[cnt[0] + cnt[1] - 1]);
    if (cnt[1] && cnt[3]) add(ans, ml(_2[cnt[0]], ml(_2[cnt[1] - 1], _2[cnt[3]] - 1)));
    printf("%d", ans);

    return 0;
}
