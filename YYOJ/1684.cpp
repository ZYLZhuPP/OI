#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e6 + 5;

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
} io;

int n, m, a, b, fa, q, x, y, ans, res;
bool kil[N];
int tot, head[N], to[N], nxt[N];

void add(int u, int v) {
    nxt[++tot] = head[u];
    head[u] = tot;
    to[tot] = v;
}

void dfs(int u) {
    res--; kil[u] = 1;
    for (int i = head[u]; i; i = nxt[i]) if (!kil[to[i]]) dfs(to[i]);
}

int solve(int u) {
    if (kil[u]) return res;
    dfs(u);
    return res;
}

int main() {
    io >> n >> m;
    io >> a >> b;
    fa = 1; add(1, 2);
    For (i, 3, n) {
        fa = ((1ll * fa * a + b) ^ 19760817) % (i - 1) + 1;
        add(fa, i);
    }
    
    res = n;
    io >> q >> x >> y;
    ans = solve(q);
    For (i, 2, m) {
        q = (((1ll * q * x + y) ^ 19760817) ^ (i << 1)) % (n - 1) + 2;
        ans ^= solve(q);
    }
    
    printf("%d", ans);
    
    return 0;
} 
