#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 305;
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

int n, m, dep[N], dfn[N], dfn_[N], tim, ls[N], rs[N], pos[N], be[N], f[N][N], val[N];
vector<int > op[N], pt[N], re[N], a[N][2];

inline void dmax(int &x, const int &y) { dep[y]>dep[x]? x=y: 0; }

inline void dfs(int u, int pre) {
    if (!u) return;
    dfn[u] = ++tim; dep[u] = dep[pre] + 1;
    dfs(ls[u], u); dfs(rs[u], u);
    dfn_[u] = tim;
}

inline void solve(int u, int pre) {
    if (!u) return;
    solve(ls[u], u); solve(rs[u], u);
    if (pt[u].empty()) {
        swap(re[u], re[ls[u]]);
        for (auto &x : re[rs[u]]) re[u].pb(x);
        re[rs[u]].resize(0);
        re[u].pb(u);
        return;
    }
    vector<int > vec[2];
    for (auto &rt : pt[u]) {
        for (auto &v : pt[u]) be[v] = -1;
        bool flag = 1;
        int s[2] = {(int)re[ls[u]].size(), (int)re[rs[u]].size()};
        vec[0].resize(0); vec[1].resize(0);
        queue<int > q;
        for (auto &v : pt[u]) if (v ^ rt) {
            for (auto &x : op[v]) {
                int y = dfn[pos[x]];
                if (y >= dfn[ls[u]] && y <= dfn_[ls[u]]) {
                    if (be[v] == 0) flag = 0;
                    be[v] = 1;
                } else if (y >= dfn[rs[u]] && y <= dfn_[rs[u]]) {
                    if (be[v] == 1) flag = 0;
                    be[v] = 0;
                }
            }
            if (~be[v]) q.push(v);
        }
        if (!flag) continue;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            s[be[u]]--; vec[be[u]].pb(u);
            for (auto &v: op[u]) if (v ^ rt && pos[v] == pos[u])  {
                if (be[v] == be[u]) flag = 0;
                if (!~be[v]) be[v] = !be[u], q.push(v);
            }
        }
        if (!flag) continue;
        int tot = 0, cnt = 0;
        for (auto &p : pt[u]) if (p ^ rt && !~be[p]) {
            tot++; a[tot][0].resize(0); a[tot][1].resize(0);
            be[p] = 0; q.push(p);
            while (!q.empty()) {
                int u = q.front(); q.pop(); cnt++;
                a[tot][be[u]].pb(u);
                for (auto &v: op[u]) if (v ^ rt && pos[v] == pos[u])  {
                    if (be[v] == be[u]) flag = 0;
                    if (!~be[v]) be[v] = !be[u], q.push(v);
                }
            }
        }
        if (!flag) continue;
        For (i, 0, tot) For (j, 0, cnt) f[i][j] = -1;
        f[0][0] = 1;
        For (i, 1, tot) {
            For (j, 0, cnt) if (~f[i - 1][j]) {
                f[i][j + a[i][0].size()] = 0;
                f[i][j + a[i][1].size()] = 1;
            }
        }
        For (i, 0, cnt) if (s[0] >= i && s[1] >= cnt - i && ~f[tot][i]) {
            int x = i;
            rFor (j, tot, 1) {
                int y = f[j][x];
                for (auto &v : a[j][y]) vec[0].pb(v);
                for (auto &v : a[j][!y]) vec[1].pb(v);
                x -= a[j][y].size();
            }
            val[rt] = u;
            flag = 0;
            break;
        }
        if (!flag) break;
    }
    For (i, 0, (int)vec[0].size() - 1) val[vec[0][i]] = re[ls[u]][i];
    For (i, (int)vec[0].size(), (int)re[ls[u]].size() - 1) re[u].pb(re[ls[u]][i]);
    For (i, 0, (int)vec[1].size() - 1) val[vec[1][i]] = re[rs[u]][i];
    For (i, (int)vec[1].size(), (int)re[rs[u]].size() - 1) re[u].pb(re[rs[u]][i]);
    re[ls[u]].resize(0); re[rs[u]].resize(0);
}

int main() {
    io >> n >> m;
    For (i, 1, n) io >> ls[i] >> rs[i];
    dfs(1, 0);
    For (i, 1, n) pos[i] = 1;
    int u, v, x;
    For (i, 1, m) {
        io >> u >> v >> x;
        op[u].pb(v); op[v].pb(u);
        dmax(pos[u], x); dmax(pos[v], x);
    }
    For (i, 1, n) pt[pos[i]].pb(i);
    solve(1, 0);
    For (i, 1, n) printf("%d ", val[i]);

    return 0;
}
