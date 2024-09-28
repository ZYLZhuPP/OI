#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 105, M = 1e4 + 5;

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

const int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
int n, m, mp[256], a[M], id[N][N], tot, ans, mch[M], s1, s2;
char g[N][N], st[N];
bitset<M > vis;
vector<int > es[M];

inline bool dfs(int u) {
    for (auto &v : es[u]) if (!mch[v]) return mch[v] = u, 1;
    else if (!vis[v]) {
        vis[v] = 1;
        if (dfs(mch[v])) return mch[v] = u, 1;
    }
    return 0;
}

int main() {
    mp['L'] = 3; mp['U'] = 2; mp['R'] = 1; mp['D'] = 0;
    io >> n >> m;
    For (i, 1, n) scanf("%s", g[i] + 1);
    For (i, 1, n) {
        scanf("%s", st + 1);
        For (j, 1, m) a[id[i][j] = ++tot] = mp[st[j]], s1 += a[tot];
    }
    For (i, 1, n) For (j, 1, m) if (g[i][j] == 'L') {
        For (k, 0, 3) {
            int x = i + dx[k], y = j + dy[k];
            if (x && x <= n && y && y <= m && g[x][y] == 'R') es[id[i][j]].pb(id[x][y]);
        }
    }
    For (i, 1, n) For (j, 1, m) if (g[i][j] == 'L') {
        vis = 0;
        ans += dfs(id[i][j]);
    }
    if (ans == (n * m + 1) / 2) {
        For (i, 1, n) For (j, 1, m) if (g[i][j] == 'R') {
            int x = id[i][j], y = mch[x];
            if (m > 1 && abs(x - y) == 1) continue;
            s2 += 2;
        }
        if (s1 % 4 != s2 % 4) ans --;
    }
    printf("%d", ans);

    return 0;
}
