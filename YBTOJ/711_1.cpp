#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e5 + 5;

int n, fa[N], d[N], cnt[N], rt[N];
ll m, c[N], l[N], s[N], ans;

namespace LT {
    struct Node {
        int l, r, v, d;
        Node() { l = r = v = d = 0; }
    } o[N];
    int tot;
#define ls o[u].l
#define rs o[u].r
    void up(int u) { if (o[ls].d < o[rs].d) swap(ls, rs); o[u].d = o[rs].d + 1; }
    int merge(int u, int v) {
        if (!u || !v) return u | v;
        if (o[v].v > o[u].v) swap(u, v);
        rs = merge(rs, v); up(u);
        return u;
    }
    void ins(int &u, int x) {
        int v = ++tot; o[v].v = x;
        u = merge(u, v);
    }
    int pop(int &u) {
        int r = o[u].v;
        u = merge(ls, rs);
        return r;
    }
}
using namespace LT;

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    For (i, 1, n) cin >> fa[i] >> c[i] >> l[i], d[fa[i]]++;
    queue<int > q;
    For (i, 1, n) if (!d[i]) q.push(i);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        ins(rt[u], c[u]); s[u] += c[u]; cnt[u]++;
        while (s[u] > m) s[u] -= pop(rt[u]), cnt[u]--;
        ans = max(ans, cnt[u] * l[u]);
        int f = fa[u];
        rt[f] = merge(rt[f], rt[u]); s[f] += s[u]; cnt[f] += cnt[u];
        if (!--d[f]) q.push(f);
    }
    cout << ans;

    return 0;
}
