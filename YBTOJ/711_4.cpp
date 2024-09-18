#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e6 + 5;

int n, x[N], t;
ll ans;

namespace LT {
    struct Node {
        int l, r, d;
        Node() { l = r = d = 0; }
    } o[N];
#define ls o[p].l
#define rs o[p].r
    void up(int p) { if (o[ls].d < o[rs].d) swap(ls, rs); o[p].d = o[rs].d + 1; }
    int merge(int p, int q) {
        if (!p || !q) return p | q;
        if (x[q] > x[p]) swap(p, q);
        rs = merge(rs, q); up(p);
        return p;
    }
    void pop(int &p) { p = merge(ls, rs); }
}
using namespace LT;

struct P {
    int rt, l, r, s, v;
} s[N];

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    For (i, 1, n) cin >> x[i], x[i] -= i;
    For (i, 1, n) {
        s[++t] = P{i, i, i, 1, x[i]};
        while (t > 1 && s[t - 1].v > s[t].v) {
            t--;
            s[t].rt = merge(s[t].rt, s[t + 1].rt);
            s[t].s += s[t + 1].s;
            s[t].r = s[t + 1].r;
            while (s[t].s > (s[t].r - s[t].l + 2) >> 1)
                --s[t].s, pop(s[t].rt);
            s[t].v = x[s[t].rt];
        }
    }
    int j = 1;
    For (i, 1, n) {
        if (s[j].r < i) j++;
        ans += abs(x[i] - s[j].v);
    }
    cout << ans;

    return 0;
}
