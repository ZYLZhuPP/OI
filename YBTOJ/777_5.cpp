#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
const int N = 1e3 + 5, S = 1e3;
typedef bitset<S> B;

int n, m, ID, pre[N];
char st[N];
B a[N];

namespace Seg {
    vector<B > o[N << 2];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline void upd(int p, int l, int r, int x, int y, const B &v) {
        if (l > y || r < x) return;
        if (x <= l && r <= y) return o[p].pb(v);
        M; upd(goL, x, y, v); upd(goR, x, y, v);
    }
    B b[S];
    inline void solve(int p, int l, int r) {
        vector<int > back;
        for (auto v : o[p]) rFor (i, S - 1, 0) if (v[i]) {
            if (b[i][i]) v ^= b[i];
            else {
                b[i] = v; back.pb(i);
                break;
            }
        }
        if (l == r) {
            B ans;
            rFor (i, S - 1, 0) if (!ans[i] && b[i][i]) ans ^= b[i];
            //cout << ans << endl;
            int pos = S - 1;
            while (pos && !ans[pos]) pos--;
            while (~pos) putchar(ans[pos--] ^ 48);
            puts("");
            for (auto &x : back) b[x].reset();
            return;
        }
        M; solve(goL); solve(goR);
        for (auto &x : back) b[x].reset();
    }
}
using namespace Seg;

int main() {
    scanf("%d%d%d", &ID, &n, &m);
    For (i, 1, n) pre[i] = 1;
    For (i, 1, m) {
        int u, v; B x;
        scanf("%d%d %s", &u, &v, st + 1);
        if (u == v) continue;
        int len = strlen(st + 1);
        For (j, 1, len) x[len - j] = st[j] ^ 48;
        upd(1, 1, m, pre[u], i - 1, a[u]); a[u] ^= x; pre[u] = i;
        upd(1, 1, m, pre[v], i - 1, a[v]); a[v] ^= x; pre[v] = i;
    }
    For (i, 1, n) upd(1, 1, m, pre[i], m, a[i]);
    solve(1, 1, m);

    return 0;
}
