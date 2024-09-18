#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e5 + 5;

int T, type;
ll ans, x;

namespace LCT {
    struct Node {
        int f, c[2], v, cnt, rev, tag;
        ll s, sum;
#define l c[0]
#define r c[1]
        Node () { f = l = r = v = cnt = s = sum = rev = tag = 0; }
    } o[N];
#define ls o[u].l
#define rs o[u].r
#define fu o[u].f
    inline bool is(const int &u) { return u==o[fu].r; }
    inline bool nrt(const int &u) { return u==o[fu].l||is(u); }
    inline void up(int u) {
        o[u].s = o[ls].s + o[rs].s + o[u].v;
        o[u].sum = o[ls].sum + o[rs].sum + 1ll * o[u].v * o[u].cnt;
    }
    inline void reverse(int u) { if (u) swap(ls, rs), o[u].rev ^= 1; }
    inline void mark(int u, int d) { if (u) o[u].sum += o[u].s * d, o[u].cnt += d, o[u].tag += d; }
    inline void down(int u) {
        if (o[u].rev) reverse(ls), reverse(rs), o[u].rev = 0;
        if (o[u].tag) mark(ls, o[u].tag), mark(rs, o[u].tag), o[u].tag = 0;
    }
    inline void updown(int u) { if (nrt(u)) updown(fu); down(u); }
    inline void rot(int u) {
        int k = is(u), f = fu, ff = o[f].f, c = o[u].c[!k];
        if (nrt(f)) o[ff].c[is(f)] = u; o[u].c[!k] = f; o[f].c[k] = c;
        if (c) o[c].f = f; o[f].f = u; fu = ff;
        up(f); up(u);
    }
    inline void splay(int u) { updown(u); for (; nrt(u); rot(u)) if (nrt(fu)) rot(is(fu)^is(u)? u: fu); }
    inline void access(int u) { int p = u; for (int v = 0; u; v = u, u = fu) splay(u), rs = v, up(u); splay(p); }
    inline void makert(int u) { access(u); reverse(u); }
    inline int findrt(int u) { access(u); down(u); while (ls) down(u = ls); splay(u); return u; }
    inline void link(int u, int v) { makert(u); if (findrt(v) ^ u) fu = v; splay(u); }
    inline void cut(int u, int v) { makert(u); if (findrt(v) == u && o[v].f == u && !o[v].l) rs = o[v].f = 0; }
    inline void pick(int u, int v) { makert(u); access(v); splay(u); }
}
using namespace LCT;

namespace PAM {
    int to[N][26], fa[N], len[N], s_[N], tot, ed, now;
    void init() { s_[0] = -1; len[tot = 1] = -1; fa[0] = fa[1] = 1; }
    int find(int p) { while (s_[now] ^ s_[now - len[p] - 1]) p = fa[p]; return p; }
    void add(const int c) {
        s_[++now] = c; int p = find(ed);
        if (!to[p][c]) {
            int q = ++tot; len[q] = len[p] + 2;
            fa[q] = to[find(fa[p])][c]; to[p][c] = q;
            o[q + 1].v = len[q] - len[fa[q]];
            link(q + 1, fa[q] + 1);
        }
        ed = to[p][c];
    }
}
using namespace PAM;

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> T >> type;
    init();
    while (T--) {
        cin >> x; if (type) x ^= ans;
        add(x); pick(ed + 1, 0 + 1); mark(ed + 1, 1);
        ans += o[ed + 1].sum;
        cout << ans << endl;
    }

    return 0;
}
