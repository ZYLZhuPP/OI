#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e6 + 5;

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

int n, tot = 1, ch[N][2], cnt[N], vis[N], ans, f[N];
char s[N];

inline void ins(char s[]) {
    int n = strlen(s + 1), u = 1;
    For (i, 1, n) {
        int c = s[i] & 1;
        if (!ch[u][c]) ch[u][c] = ++tot;
        u = ch[u][c];
    }
    cnt[u]++;
}

inline void up(int u) {
    f[u] = ch[u][0] || ch[u][1]? min(f[ch[u][0]], f[ch[u][1]]) + 1: (2 * vis[u]);
}

inline void solve(int &u) {
    if (!ch[u][0] && !ch[u][1]) {
        if (!u) u = ++tot;
        if (!vis[u]) vis[u] = 1;
        else solve(ch[u][0]), solve(ch[u][1]);
    } else solve(ch[u][f[ch[u][1]] < f[ch[u][0]]]);
    up(u);
}

inline void dfs(int u) {
    if (!u) return;
    For (i, 0, 1) dfs(ch[u][i]);
    up(u);
    For (i, 1, cnt[u]) ans += f[u], solve(u);
}

int main() {
    io >> n;
    For (i, 1, n) scanf("%s", s + 1), ins(s);
    dfs(1);
    printf("%d", ans);

    return 0;
}
