#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 6e5 + 5, M = N >> 1;

char s[N];

namespace DPAM {
    int to[N][26], fa[N], len[N], s_[N], tot, ed[2], now[2], d[2] = {-1, 1};
    inline void init() { memset(s_, -1, sizeof s_); len[tot = 1] = -1; fa[0] = fa[1] = 1; now[0] = M; now[1] = M - 1; }
    inline int find(int k, int p) { while (s_[now[k]] ^ s_[now[k] - d[k] * (len[p] + 1)]) p = fa[p]; return p; }
    inline void add(int k, const int c) {
        s_[now[k] += d[k]] = c; int p = find(k, ed[k]);
        if (!to[p][c]) {
            int q = ++tot; len[q] = len[p] + 2;
            fa[q] = to[find(k, fa[p])][c]; to[p][c] = q;
        }
        ed[k] = to[p][c];
        if (len[ed[k]] == now[1] - now[0] + 1) ed[!k] = ed[k];
    }
    inline void ins(int k, const char *s) {
        int n = strlen(s + 1);
        For (i, 1, n) add(k, s[i] - 'a');
    }
}
using namespace DPAM;

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> (s + 1);
    init(); ins(1, s);

    return 0;
}
