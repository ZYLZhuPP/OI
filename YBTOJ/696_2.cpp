#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e6 + 5, Mo = 1e9 + 7;
inline void add(int &x, int y) { x += y; if (x >= Mo) x -= Mo; }

int n, f[N], g[N];
char s[N], ss[N];

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
    cin >> (s + 1); n = strlen(s + 1);
    For (i, 1, n / 2) ss[i * 2 - 1] = s[i], ss[i * 2] = s[n - i + 1];
    init(); s_ = ss;
    f[0] = 1;
    For (i, 1, n) {
        add(ss[i] - 'a');
        for (int x = ed; x; x = link[x]) {
            g[x] = f[i - len[link[x]] - d[x]];
            if (link[x] ^ fa[x]) add(g[x], g[fa[x]]);
            if (!(i & 1)) add(f[i], g[x]);
        }
    }
    cout << f[n];

    return 0;
}
