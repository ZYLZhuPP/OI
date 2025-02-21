#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e5 + 5;

int n, f[N << 1], top[N << 1], buc[N], a[N << 1], rt[N << 1];
int ans = 1;
char s[N];

namespace SAM {
    int to[N << 1][26], fa[N << 1], len[N << 1], pos[N << 1], tot = 1, ed = 1;
    int upd(int p, const int c) {
        int q = to[p][c];
        if (len[q] == len[p] + 1) return q;
        int nq = ++tot; memcpy(to[nq], to[q], sizeof to[q]);
        fa[nq] = fa[q]; fa[q] = nq; len[nq] = len[p] + 1; pos[nq] = pos[q];
        while (p && to[p][c] == q) to[p][c] = nq, p = fa[p];
        return nq;
    }
    void add(const int c) {
        int p = ed, np = ed = ++tot;
        len[np] = len[p] + 1; pos[np] = pos[p] + 1;
        while (p && !to[p][c]) to[p][c] = np, p = fa[p];
        fa[np] = p? upd(p, c): 1;
    }
}
using namespace SAM;

namespace Seg {
    struct Node {
        int l, r;
        Node(int l = 0, int r = 0): l(l), r(r) { }
    } o[N * 40];
    int tot = 0;
#define ls o[p].l
#define rs o[p].r
#define M int m = (l + r) >> 1;
#define goL ls, l, m
#define goR rs, m + 1, r
    void upd(int &p, int l, int r, int x) {
        if (l > x || r < x) return;
        if (!p) p = ++tot;
        if (l == r) return;
        M; upd(goL, x); upd(goR, x);
    }
    int merge(int p, int q) {
        if (!p || !q) return p | q;
        int r = ++tot;
        o[r] = Node(merge(ls, o[q].l), merge(rs, o[q].r));
        return r;
    }
    bool query(int p, int l, int r, int x, int y) {
        if (!p || l > y || r < x) return 0;
        if (x <= l && r <= y) return 1;
        M; return query(goL, x, y) || query(goR, x, y);
    }
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> (s + 1);
    For (i, 1, n) add(s[i] - 'a'), Seg::upd(rt[ed], 1, n, i);
    For (i, 1, tot) buc[len[i]]++;
    For (i, 1, n) buc[i] += buc[i - 1];
    For (i, 1, tot) a[buc[len[i]]--] = i;
    rFor (i, tot, 1) rt[fa[a[i]]] = Seg::merge(rt[fa[a[i]]], rt[a[i]]);

    For (i, 2, tot) {
        int u = a[i], v = fa[u], t = top[v];
        if (v == 1) { f[u] = 1, top[u] = u; continue; }
        if (Seg::query(rt[t], 1, n, pos[u] - len[u] + len[t], pos[u] - 1))
            f[u] = f[t] + 1, top[u] = u, ans = max(ans, f[u]);
        else f[u] = f[t], top[u] = t;
    }
    cout << ans;

    return 0;
}
