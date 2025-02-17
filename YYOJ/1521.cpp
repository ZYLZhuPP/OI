#include<bits/stdc++.h>
using namespace std;

#define INF 0x1f1f1f1f
#define mem(a, x) memset(a, x, sizeof(a))

const int N = 1e3 + 5;

template<class C> inline bool chkmin(C &x, const C &y) {return x>y? x=y, 1: 0;}

struct IO {
    char c, f;
#define gc() getchar()
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc(); x *= f; return *this;
    }
    inline bool operator ~ () const { return ~c; }
}io;

int n, m, dis[N], dep[N], ans;
bool flag;
vector<int > es[N], pts[N];

void dfs(int u, int pre, int rt) {
    pts[rt].push_back(u);
    dep[u] = dep[pre] + 1;
    for (auto &v : es[u]) if (v ^ pre) {
        if (!dep[v]) dfs(v, u, rt);
        else if (!((dep[u] - dep[v]) & 1)) flag = 1;
    }
}

bool test(int rt) {
    dfs(rt, 0, rt);
    return flag;
}

void Dij(int rt) {
    mem(dis, 31); dis[rt] = 0;
    queue<int > q; q.push(rt);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto &v : es[u]) {
            if (chkmin(dis[v], dis[u] + 1)) q.push(v);
        }
    }
}

int main() {
    io >> n >> m;
    int u, v;
    for (int i = 1; i <= m; ++i) {
        io >> u >> v;
        es[u].push_back(v);
        es[v].push_back(u);
    }

    for (int i = 1; i <= n; ++i) if (!dep[i]) {
        if (test(i)) {
            puts("-1");
            return 0;
        }
    }

    for (int i = 1; i <= n; ++i) {
        int res = 0;
        for (auto &u : pts[i]) {
            Dij(u);
            for (auto &v : pts[i]) res = max(res, dis[v]);
        }
        ans += res;
    }

    printf("%d", ans);
    return 0;
}
