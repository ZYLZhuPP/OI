#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (register int i = (r); i >= (l); --i)
#define For(i, l, r) for (register int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e5 + 5;

struct IO {
    int c, f;
#define gc() getchar()
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
    }
    inline bool operator ~ () const { return ~c; }
} io;

int n, s[N], cnt, mi[N], mu[N], mv[N], id[N];
ll ans;

namespace Trie {
    int tot = 0, ch[N * 20][2], cnt[N * 20], id[N * 20];
    inline void ins(const int &x, const int &u) {
        int k = 0;
        rFor (i, 29, 0) {
            int c = x >> i & 1;
            if (!ch[k][c]) ch[k][c] = ++tot;
            cnt[k = ch[k][c]]++;
        }
        id[k] = u;
    }
    inline void upd(const int &x, const int &d) {
        int k = 0;
        rFor (i, 29, 0) cnt[k = ch[k][x >> i & 1]] += d;
    }
    inline int solve(const int &x) {
        int k = 0;
        rFor (i, 29, 0) {
            int c = x >> i & 1;
            if (cnt[ch[k][c]]) k = ch[k][c];
            else k = ch[k][!c];
        }
        return id[k];
    }
}

int fa[N];
inline int find(const int &u) { return fa[u]^u? fa[u]=find(fa[u]): u; }
inline void merge(const int &u, const int &v) { fa[find(u)] = find(v); }

int main() {
    io >> n;
    For (i, 1, n) io >> s[i], s[i] ^= s[i - 1];
    sort(s, s + n + 1); n = unique(s, s + n + 1) - s - 1;

    For (i, 0, n) Trie::ins(s[i], fa[i] = i);
    while (1) {
        cnt = 0;
        For (i, 0, n) if (find(i) == i) mi[id[i] = ++cnt] = INT_MAX;
        if (cnt == 1) break;
        vector<int > blg[cnt + 1];
        For (i, 0, n) blg[id[find(i)]].push_back(i);
        For (i, 1, cnt) {
            for (auto &u : blg[i]) Trie::upd(s[u], -1);
            for (auto &u : blg[i]) {
                int v = Trie::solve(s[u]);
                if ((s[u] ^ s[v]) < mi[i])
                    mi[i] = s[u] ^ s[v], mu[i] = u, mv[i] = v;
            }
            for (auto &u : blg[i]) Trie::upd(s[u], 1);
        }
        int fu, fv;
        For (i, 1, cnt) {
            fu = find(mu[i]); fv = find(mv[i]);
            if (fu ^ fv) {
                ans += mi[i];
                merge(fu, fv);
            }
        }
    }

    printf("%lld", ans);

    return 0;
}
