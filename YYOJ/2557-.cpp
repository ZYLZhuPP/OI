#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 8e3 + 5;

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

int n, g[N][N], a[N], b[N], ans[N];

inline void dfs(int k) {
    if (k == n - 1) {
        int cnt = 0;
        a[k] = n;
        set<int > se;
        For (i, 1, n) se.insert(i);
        rFor (i, k, 1) if (se.count(a[i])) b[i] = 1, se.erase(a[i]); else b[i] = 0;
        For (i, 1, k) {
            int u = a[i], v = *se.begin();
            cnt += g[u][v]; se.erase(se.begin());
            if (b[i]) se.insert(a[i]);
        }
        ans[cnt]++;
        return ;
    }
    For (i, 1, n) a[k] = i, dfs(k + 1);
}

int main() {
    io >> n;
    int u, v;
    For (i, 1, n - 1) io >> u >> v, g[u][v] = g[v][u] = 1;
    dfs(1);
    For (i, 0, n - 1) printf("%d ", ans[i]);

    return 0;
}
