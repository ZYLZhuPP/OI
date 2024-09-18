#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5;

int n, buc[N], a[N << 1], ans[N];
set<int > id[N << 1];
char s[N];

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
    void ins(const char *s, int pos) {
        ed = 1; int n = strlen(s + 1);
        For (i, 1, n) add(s[i] - 'a'), id[ed].insert(pos);
    }
}
using namespace GSAM;

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    For (i, 1, n) {
        cin >> (s + 1);
        ins(s, i);
    }
    For (i, 1, tot) buc[len[i]]++;
    For (i, 1, N - 1) buc[i] += buc[i - 1];
    rFor (i, tot, 1) a[buc[len[i]]--] = i;
    rFor (i, tot, 2) {
        int u = a[i], f = fa[u]; 
        if (id[u].size() == 1) ans[*id[u].begin()] += len[u] - len[f];
        if (id[f].size() < id[u].size()) swap(id[f], id[u]);
        for (auto &x : id[u]) id[f].insert(x);
    }
    For (i, 1, n) cout << ans[i] << endl;

    return 0;
}
