#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e6 + 5;

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

int n, dfn[N], dfn_[N], tim, a[N], stk[N], top;
vector<int > es[N];

inline void dfs0(int u) {
    dfn[u] = ++tim;
    for (auto &v : es[u]) dfs0(v);
    dfn_[u] = tim;
}

inline bool in(int a, int b) { return dfn[a] <= dfn[b] && dfn_[b] <= dfn_[a]; }

int main() {
    io >> n;
    int x;
    For (i, 2, n) io >> x, es[x].pb(i);
    dfs0(1);
    stk[++top] = n + 1;
    rFor (i, n, 1) {
        while (in(i, stk[top])) top--;
        a[i]++; a[stk[top]]--;
        stk[++top] = i;
    }
    For (i, 1, n) printf("%d\n", a[i] += a[i - 1]);

    return 0;
}
