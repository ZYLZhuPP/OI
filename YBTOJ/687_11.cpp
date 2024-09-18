#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 5e5 + 5;

int n, m, T, ma[N << 1], l, r, rt[N << 1];
ll ans;
char s[N], t[N];
vector<int > es[N << 1];

struct SAM {
    vector<vector<int > > to;
    vector<int > fa, len;
    int tot, ed;
    SAM (int n = 0) {
        to.resize(n * 2, vector<int >(26, 0));
        fa.resize(n * 2, 0); len.resize(n * 2, 0);
        tot = ed = 1;       
    }
    int upd(int p, const int c) {
        int q = to[p][c];
        if (len[q] == len[p] + 1) return q;
        int nq = ++tot; to[nq] = to[q];
        fa[nq] = fa[q]; fa[q] = nq; len[nq] = len[p] + 1;
        while (p && to[p][c] == q) to[p][c] = nq, p = fa[p];
        return nq;
    }
    void add(const int c) {
        int p = ed, np = ed = ++tot; len[np] = len[p] + 1;
        while (p && !to[p][c]) to[p][c] = np, p = fa[p];
        fa[np] = p? upd(p, c): 1;
    }
} ss, st;

namespace Seg {
    struct Node {
        int l, r;
        Node(int l = 0, int r = 0): l(l), r(r) { }
    } o[N * 40];
    int tot;
#define ls o[p].l
#define rs o[p].r
#define M int m = (l + r) >> 1
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
        o[r].l = merge(ls, o[q].l); o[r].r = merge(rs, o[q].r);
        return r;
    }
    bool query(int p, int l, int r, int x, int y) {
        if (!p || l > y || r < x) return 0;
        if (x <= l && r <= y) return 1;
        M; return query(goL, x, y) || query(goR, x, y);
    }
}
using namespace Seg;

void init(int u) { for (auto &v : es[u]) init(v), rt[u] = merge(rt[u], rt[v]); }

void dfs(int u) {
    for (auto &v : es[u]) {
        dfs(v);
        ma[u] = max(ma[u], ma[v]);
    }
    ans += max(0, st.len[u] - max(ma[u], st.len[st.fa[u]]));
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> (s + 1); n = strlen(s + 1);
    ss = SAM(n); For (i, 1, n) {
        ss.add(s[i] - 'a');
        upd(rt[ss.ed], 1, n, i);
    }
    For (i, 2, ss.tot) es[ss.fa[i]].emplace_back(i);
    init(1);

    cin >> T;
    while (T--) {
        cin >> (t + 1) >> l >> r; m = strlen(t + 1);
        st = SAM(m); For (i, 1, m) st.add(t[i] - 'a');
        For (i, 1, st.tot) es[i].resize(0), ma[i] = 0;
        For (i, 2, st.tot) es[st.fa[i]].emplace_back(i);

        int p = 1, u = 1, v = 1;
        For (i, 1, m) {
            int c = t[i] - 'a';
            while (p < i && !ss.to[u][c]) {
                p++;
                if (i - p <= ss.len[ss.fa[u]]) u = ss.fa[u];
                if (i - p <= st.len[st.fa[v]]) v = st.fa[v];
            }
            if (!ss.to[u][c]) {
                p = i + 1;
                u = v = 1;
                continue;
            }
            u = ss.to[u][c]; v = st.to[v][c];
            while (p <= i && !query(rt[u], 1, n, l + i - p, r)) {
                p++;
                if (i - p + 1 <= ss.len[ss.fa[u]]) u = ss.fa[u];
                if (i - p + 1 <= st.len[st.fa[v]]) v = st.fa[v];
            }
            ma[v] = max(ma[v], i - p + 1);
        }

        ans = 0;
        dfs(1);
        cout << ans << endl;
    }

    return 0;
}
