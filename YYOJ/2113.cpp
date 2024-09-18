#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 105, NN = 4 * N * N + 5, M = NN * N + 2 * N + 5;

struct IO {
    int c, f;
#define gc() getchar()
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
    }
    inline bool operator ~ () { return ~c; }
} io;

int n, u, v, m, k, ans;
vector<int > es[N];

int num, head[NN], nxt[M << 1], to[M << 1], val[M << 1];
void add(int u, int v, int d) {
    nxt[++num] = head[u]; head[u] = num;
    val[num] = d; to[num] = v;
    nxt[++num] = head[v]; head[v] = num;
    val[num] = 0; to[num] = u;
}

namespace Dinic {
    int S, T;
    int lev[NN];
    bool bfs() {
        memset(lev, 0, sizeof lev); lev[S] = 1;
        queue<int > q; q.push(S);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int i = head[u]; i; i = nxt[i]) if (val[i]) {
                int v = to[i];
                if (!lev[v]) lev[v] = lev[u] + 1, q.push(v);
                if (v == T) return 1;
            }
        }
        return 0;
    }
    int dfs(int u, int s) {
        if (u == T || !s) return s;
        int flow = 0, f;
        for (int i = head[u]; i; i = nxt[i]) if (val[i]) {
            int v = to[i];
            if (lev[v] > lev[u] && (f = dfs(v, min(s - flow, val[i])))) {
                val[i] -= f; val[i ^ 1] += f;
                flow += f; if (flow == s) break;
            }
        }
        if (flow < s) lev[u] = -1;
        return flow;
    }
    int solve(int s, int t) {
        S = s; T = t;
        int res = 0;
        while (bfs()) res += dfs(S, n + 1);
        return res;
    }
}

bool check(int d) {
    memset(head, 0, sizeof head);
    memset(nxt, 0, sizeof(nxt));
    num = 1;
    For (i, 0, d) {
        int s = i * 2 * n;
        For (j, 0, n - 1) add(s + (j << 1), s + (j << 1 | 1), 1);
        if (i) {
            int s_ = (i - 1) * 2 * n;
            For (j, 0, n - 1) add(s_ + (j << 1), s + (j << 1 | 1), n + 1);
            For (j, 0, n - 1) for (auto &v : es[j]) add(s_ + (v << 1 | 1), s + (j << 1), n + 1);
            add(s_ + ((n - 1) << 1), s + ((n - 1) << 1), n + 1);
        }
    }
    return Dinic::solve(1, (d + 1) * 2 * n - 2) <= k;
}

int main() {
    io >> n >> m >> k;
    For (i, 1, m) {
        io >> u >> v;
        es[u].push_back(v);
        es[v].push_back(u);
    }
    
    int l = 1, r = n << 1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid - 1)) ans = mid, l = mid + 1;
        else r = mid - 1;
    }

    printf("%d", ans);
    return 0;
}
