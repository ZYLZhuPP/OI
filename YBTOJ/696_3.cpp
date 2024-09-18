#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e6 + 5;

int T, n, f[N], ans;
int q[N];
char s[N];

int mp(const char &c) { return c=='A'? 0: c=='T'? 1: c=='C'? 2: 3; }
namespace PAM {
    int to[N][4], fa[N], len[N], hf[N], tot, ed, now, s_[N];
    void init(int n) {
        s_[0] = -1; now = ed = 0;
        For (i, 0, n + 5) {
            For (j, 0, 3) to[i][j] = 0;
            fa[i] = len[i] = hf[i] = 0;
        }
        len[tot = 1] = -1;
        fa[0] = fa[1] = hf[0] = hf[1] = 1;
    }
    int find(int p) { while (s_[now] ^ s_[now - len[p] - 1]) p = fa[p]; return p; }
    int half(int p, int l) { while (len[p] + 2 > l || s_[now] ^ s_[now - len[p] - 1]) p = fa[p]; return p; }
    void add(const int c) {
        s_[++now] = c; int p = find(ed);
        if (!to[p][c]) {
            int q = ++tot; len[q] = len[p] + 2;
            fa[q] = to[find(fa[p])][c];
            if (len[q] >= 2) hf[q] = to[half(hf[p], len[q] >> 1)][c];
            to[p][c] = q;
        }
        ed = to[p][c];
    }
    void ins(const char *s) {
        int n= strlen(s + 1);
        For (i, 1, n) add(mp(s[i]));
    }
}
using namespace PAM;

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> T;
    while (T--) {
        cin >> (s + 1); n = strlen(s + 1);
        init(n); ins(s);
        For (i, 2, tot) f[i] = n;
        int h = 1, t = 0; q[++t] = 0;
        while (h <= t) {
            int u = q[h++];
            For (c, 0, 3) if (to[u][c]) {
                int v = to[u][c];
                q[++t] = v;
                f[v] = min(f[v], u? f[u] + 1: 2);
                if (!(len[hf[v]] & 1)) f[v] = min(f[v], f[hf[v]] + (len[v] >> 1) - len[hf[v]] + 1);
            }
        }
        ans = n;
        For (i, 2, tot) ans = min(ans, n - len[i] + f[i]);
        cout << ans << endl;
    }

    return 0;
}
