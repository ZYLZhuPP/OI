#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e6 + 5, M = 3e6 + 5;

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

int n, m;
char s[M];

namespace GSAM {
    int ch[N][26], len[N], fa[N], tot = 1, ed;
    vector<int > vis[N];
    inline int upd(int p, int c) {
        int q = ch[p][c];
        if (len[q] == len[p] + 1) return q;
        int nq = ++tot; len[nq] = len[p] + 1;
        fa[nq] = fa[q]; vis[nq] = vis[q]; memcpy(ch[nq], ch[q], sizeof ch[q]);
        while (p && ch[p][c] == q) ch[p][c] = nq, p = fa[p];
        return fa[q] = nq;
    }
    inline void add(int c) {
        if (ch[ed][c]) return ed = upd(ed, c), void();
        int p = ed, np = ed = ++tot; len[np] = len[p] + 1;
        while (p && !ch[p][c]) ch[p][c] = np, p = fa[p];
        fa[np] = p? upd(p, c): 1;
    }
    inline void ins(char s[], int k) {
        ed = 1;
        int n = strlen(s + 1);
        For (i, 1, n) {
            add(s[i] - 'a');
            for (int p = ed; p && (vis[p].empty() || vis[p].back() < k); p = fa[p]) vis[p].pb(k);
        }
    }
    inline int query(char s[], int k) {
        int p = 1, n = strlen(s + 1);
        For (i, 1, n) p = ch[p][s[i] - 'a'];
        if (!p || (int)vis[p].size() < k) return -1;
        return vis[p][(int)vis[p].size() - k];
    }
}
using namespace GSAM;

int main() {
    io >> m;
    int op, k;
    while (m--) {
        io >> op;
        if (op == 1) {
            scanf("%s", s + 1);
            ins(s, ++n);
        } else {
            scanf("%s", s + 1); io >> k;
            printf("%d\n", query(s, k));
        }
    }

    return 0;
}
