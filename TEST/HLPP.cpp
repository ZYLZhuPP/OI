#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 505, V = 1e6 + 5, M = 3e6 + 5, inf = 1e9;
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }

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

int tot;

namespace HLPP {
    int S, T, en = 1, head[V], nxt[M], to[M], cap[M], top, h[V], ex[V], gap[V];
    vector<int > stk[V];
    inline void add(int u, int v, const int &w) {
        nxt[++en] = head[u]; to[en] = v; cap[en] = w; head[u] = en;
        nxt[++en] = head[v]; to[en] = u; cap[en] = 0; head[v] = en;
    }
    inline bool bfs() {
        memset(h, 63, (tot + 1) << 2);
        queue<int > q; h[T] = 1; q.push(T);
        while (!q.empty()) {
            int u = q.front(); q.pop(); gap[h[u]]++;
            for (int i = head[u], v; v = to[i], i; i = nxt[i]) if (cap[i ^ 1] && cmin(h[v], h[u] + 1)) q.push(v);
        }
        return h[S] < inf;
    }
    inline bool push(int u) {
        for (int i = head[u], v; v = to[i], i; i = nxt[i]) if (cap[i] && (u == S || h[u] == h[v] + 1)) {
            int x = min(u^S? ex[u]: inf, cap[i]);
            if (v ^ S && v ^ T && !ex[v]) stk[h[v]].pb(v), cmax(top, h[v]);
            ex[u] -= x; ex[v] += x; cap[i] -= x; cap[i ^ 1] += x;
            if (!ex[u]) return 0;
        }
        return 1;
    }
    inline void relabel(int u) {
        h[u] = inf;
        for (int i = head[u], v; v = to[i], i; i = nxt[i]) if (cap[i] && h[v] < inf) cmin(h[u], h[v] + 1);
        if (h[u] <= tot) stk[h[u]].pb(u), cmax(top, h[u]), gap[h[u]]++;
    }
    inline int maxflow(int s, int t) {
        S = s; T = t;
        if (!bfs()) return 0;
        h[S] = tot + 1; push(S);
        while (top) {
            int u = stk[top].back(); stk[top].pop_back();
            if (push(u)) {
                if (!--gap[h[u]]) For (i, 1, tot) if (h[i] > h[u] && i ^ S && i ^ T) h[i] = tot + 2;
                relabel(u);
            }
            while (top && stk[top].empty()) top--;
        }
        return ex[T];
    }
}
using namespace HLPP;

int main() {

    return 0;
}
