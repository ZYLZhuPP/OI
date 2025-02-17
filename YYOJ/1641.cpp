#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
const int N = 5e5 + 5;

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
    inline bool operator ~() {return ~c;}
} io;

int n, k, c, u, rt, g[55], ok[N], S, dep[N], tod[N], fa[N], l[N], r[N];
int an[N], ned[N], mad[N];

void dfs(int u, int pre) {
    mad[u] = dep[u] = dep[pre] + 1;
    if (l[u]) dfs(l[u], u);
    if (r[u]) dfs(r[u], u);
    mad[u] = max(mad[u], max(mad[l[u]], mad[r[u]]));
}

void init() {
    g[0] = 0; g[1] = 1;
    For (i, 2, 30) g[i] = g[i - 2] + g[i - 1] + 1;
}

int main() {
    io >> n >> k;
    init();
    For (i, 1, n) {
        io >> u; fa[i] = u;
        if (~u) {
            if (i < u) l[u] = i;
            else r[u] = i;
        } else rt = i;
    }
    fa[rt] = 0;
    dfs(rt, 0);
    
    For (i, 1, n) {
        if (ok[i]) putchar('1');
        else {
            int t = 0;
            for (int x = i; x; x = fa[x]) an[++t] = x;
            
            /*bool flag = 1;
            For (i, 1, t) {
                int u = an[i], f = fa[u];
                if (ok[f] && u == r[f] && dep[i] > tod[f] + 1) flag = 0;
            }
            if (!flag) {putchar('0'); continue;}*/
            
            ned[rt] = tod[rt];
            rFor (j, t, 1) {
                int u = an[j], f = fa[u];
                if (u == l[f]) {
                    if (mad[u] >= ned[f]) ned[u] = ned[f];
                    else ned[u] = max(tod[u], ned[f] - 1);
                } else {
                    if (tod[l[f]] >= ned[f]) ned[u] = max(tod[u], ned[f] - 1);
                    else ned[u] = max(tod[u], ned[f]);
                }
            }
            
            int s = S;
            rFor (j, t, 1) {
                int u = an[j], f = fa[u];
                int d = max(tod[f], dep[i]);
                s += !ok[u];
                if (u == l[f]) {
                    if (max(d, mad[u]) >= ned[f]) s += g[max(d - 1, ned[f] - 1) - dep[f]];
                    else s += g[ned[f] - dep[f]];
                }
            }
            
            if (s <= k) {
                For (j, 1, t) {
                    int u = an[j];
                    S += !ok[u]; ok[u] = 1;
                    tod[u] = max(tod[u], dep[i]);
                }
                putchar('1');
            } else putchar('0');
        }
    }
    
    return 0;
}

