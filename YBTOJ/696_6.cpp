#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e6 + 5;

int n, f[N], g[N], from[N];
char s1[N], s2[N], s[N];

namespace PAM {
    int to[N][26], fa[N], len[N], d[N], link[N], tot, ed, now; const char *s_;
    void init() { len[tot = 1] = -1; fa[0] = fa[1] = 1; }
    int find(int p) { while (s_[now] ^ s_[now - len[p] - 1]) p = fa[p]; return p; }
    void add(const int c) {
        now++; int p = find(ed);
        if (!to[p][c]) {
            int q = ++tot; len[q] = len[p] + 2;
            fa[q] = to[find(fa[p])][c]; to[p][c] = q;
            d[q] = len[q] - len[fa[q]];
            link[q] = d[q]^d[fa[q]]? fa[q]: link[fa[q]];
        }
        ed = to[p][c];
    }
}
using namespace PAM;

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> (s1 + 1) >> (s2 + 1); n = strlen(s1 + 1);
    For (i, 1, n) s[i * 2 - 1] = s1[i], s[i * 2] = s2[i];
    n *= 2; init(); s_ = s;
    memset(f, 31, sizeof f);
    f[0] = 0;
    For (i, 1, n) {
        add(s[i] - 'a');
        if (!(i & 1) && s[i] == s[i - 1]) f[i] = f[i - 2], from[i] = i - 2;
        for (int x = ed; x; x = link[x]) {
            g[x] = i - len[link[x]] - d[x];
            if (link[x] ^ fa[x] && f[g[fa[x]]] < f[g[x]]) g[x] = g[fa[x]];
            if (!(i & 1) && f[g[x]] + 1 < f[i]) f[i] = f[from[i] = g[x]] + 1;
        }
    }
    if (f[n] > n) puts("-1");
    else {
        cout << f[n] << endl;
        for (int i = n; i; i = from[i]) if (i - from[i] > 2)
            cout << (from[i] / 2 + 1) << ' ' << (i / 2) << endl;
    }

    return 0;
}
