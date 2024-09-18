#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e6 + 5;

int n, m, T, ans, f[N];
int q[N];
char s[N];

namespace GSAM {
    int to[N << 1][2], fa[N << 1], len[N << 1], tot = 1, ed = 1;
    int upd(int p, const int c) {
        int q = to[p][c];
        if (len[q] == len[p] + 1) return q;
        int nq = ++tot; memcpy(to[nq], to[q], sizeof to[q]);
        fa[nq] = fa[q]; fa[q] = nq; len[nq] = len[p] + 1;
        while (p && to[p][c] == q) to[p][c] = nq, p = fa[p];
        return nq;
    }
    void add(const int c) {
        if (to[ed][c]) return void(ed = upd(ed, c));
        int p = ed, np = ed = ++tot; len[np] = len[p] + 1;
        while (p && !to[p][c]) to[p][c] = np, p = fa[p];
        fa[np] = p? upd(p, c): 1;
    }
    void ins(const char *s) {
        ed = 1; int n = strlen(s + 1);
        For (i, 1, n) add(s[i] - '0');
    }
}
using namespace GSAM;

bool ok(int k) {
    int w = 0, u = 1, h = 1, t = 0;
    For (i, 1, n) {
        f[i] = f[i - 1];

        int c = s[i] - '0';
        if (to[u][c]) w++;
        else {
            while (u && !to[u][c]) u = fa[u];
            if (!u) { w = 0; u = 1; continue; }
            w = len[u] + 1;
        }
        u = to[u][c];
        int l = i - w; 
        
        if (i >= k) {
            while (h <= t && f[q[t]] - q[t] <= f[i - k] - (i - k)) t--;
            q[++t] = i - k;
        }
        while (h <= t && q[h] < l) h++;
        if (h <= t) f[i] = max(f[i], f[q[h]] + i - q[h]);
        if (f[i] >= 0.9 * n) return 1;
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> T >> m;
    For (i, 1, m) cin >> (s + 1), ins(s);
    while (T--) {
        cin >> (s + 1); n = strlen(s + 1);
        ans = 0;
        int l = 1, r = n;
        while (l <= r) {
            int m = (l + r) >> 1;
            if (ok(m)) ans = m, l = m + 1;
            else r = m - 1;
        }
        cout << ans << endl;
    }

    return 0;
}
