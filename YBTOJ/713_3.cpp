#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 105;

int n, Mn, x, ans;
char op[2];

namespace Splay {
    int rt, tot;
    struct Node {
        int f, c[2], sz, v, t;
        Node() { f = c[0] = c[1] = sz = v = t = 0; }
        Node(int v, int f = 0): f(f), v(v) { sz = 1; c[0] = c[1] = t = 0; }
    } o[N];
#define fu o[u].f
#define ls o[u].c[0]
#define rs o[u].c[1]
    inline bool is(int u) { return o[fu].c[1] == u; }
    inline void up(int u) { if (u) o[u].sz = o[ls].sz + o[rs].sz + 1; }
    inline void mark(int u, int d) { if (u) o[u].v += d, o[u].t += d; }
    inline void down(int u) { if (o[u].t) mark(ls, o[u].t), mark(rs, o[u].t), o[u].t = 0; }
    inline void rot(int u) {
        int k = is(u), f = fu, ff = o[f].f, c = o[u].c[!k];
        if (ff) o[ff].c[is(f)] = u; o[u].c[!k] = f; o[f].c[k] = c;
        if (c) o[c].f = f; o[f].f = u; fu = ff;
        up(f); up(u);
    }
    inline void splay(int u, int g = 0) { for (; fu ^ g; rot(u)) if (o[fu].f ^ g) rot(is(fu)^is(u)? u: fu); if (!g) rt = u; }
    inline void ins(int &u, int k, int f = 0) {
        if (!u) return o[u = ++tot] = Node(k, f), splay(u);
        down(u); ins(o[u].c[k > o[u].v], k, u);
    }
    inline int kth(int u, int k) {
        down(u);
        if (o[rs].sz >= k) return kth(rs, k);
        else { k -= o[rs].sz + 1; return k? kth(ls, k): (splay(u), o[u].v); }
    }
}
using namespace Splay;

int main() {
    cin >> n >> Mn;
    while (n--) {
        scanf("%s%d", op, &x);
        if (op[0] == 'I') { if (x >= Mn) ins(rt, x); }
        else if (op[0] == 'A') mark(rt, x);
        else if (op[0] == 'S') {
            mark(rt, -x);
            ins(rt, Mn);
            ans += o[o[rt].c[0]].sz;
            rt = o[rt].c[1]; o[rt].f = 0;
        } else printf("%d\n", x<=o[rt].sz? kth(rt, x): -1);
    }
    cout << ans;

    return 0;
}
