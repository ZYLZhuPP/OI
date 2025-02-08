#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5;

char s[N];

namespace PAM {
    int to[N][26], fa[N], len[N], s_[N], tot, ed, now;
    inline void init() { s_[0] = -1; len[tot = 1] = -1; fa[0] = fa[1] = 1; }
    inline int find(int p) { while (s_[now] ^ s_[now - len[p] - 1]) p = fa[p]; return p; }
    inline void add(const int c) {
        s_[++now] = c; int p = find(ed);
        if (!to[p][c]) {
            int q = ++tot; len[q] = len[p] + 2;
            fa[q] = to[find(fa[p])][c]; to[p][c] = q;
        }
        ed = to[p][c];
    }
    inline void ins(const char *s) {
        now = 0; int n = strlen(s + 1);
        For (i, 1, n) add(s[i] - 'a');
    }
}
using namespace PAM;

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> (s + 1);
    init(); ins(s);

    return 0;
}
