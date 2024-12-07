#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e6 + 5;

int n, m, cnt[N << 1], vis[N << 1];
string s[N], ss;

namespace GSAM {
    int to[N << 1][26], fa[N << 1], len[N << 1], tot = 1, ed = 1;
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
    void ins(const string &s) {
        ed = 1; int n = s.length();
        For (i, 0, n - 1) add(s[i] - 'a');
    }
}
using namespace GSAM;

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    For (i, 1, n) cin >> s[i], ins(s[i]);

    For (i, 1, n) {
        int k = 1, l = s[i].length();
        For (j, 0, l - 1) {
            int p = k = to[k][s[i][j] - 'a'];
            while (p && vis[p] ^ i) cnt[p]++, vis[p] = i, p = fa[p];
        }
    }

    while (m--) {
        cin >> ss;
        int l = ss.length(), k = 1;
        For (i, 0, l - 1) k = to[k][ss[i] - 'a'];
        cout << cnt[k] << endl;
    }
    
    return 0;
}
//Luogu SP8093
