#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e6 + 5;

struct IO {
    int c, f;
#define gc() getchar()
    template<class C>
    inline IO& operator >> (C *x) {
        while ((c = gc()) < 33 && ~c);
        while (c > 32) *x++ = c, c = gc();
        *x = 0; return *this;
    }
    inline bool operator ~ () const { return ~c; }
} io;

namespace SAM {
    struct Node {
        int len, fa, ch[26];
        Node(){ len = fa = 0; memset(ch, 0, sizeof ch); }
    } o[N << 1];
    int lst = 1, tot = 1, f[N << 1];
    vector<int > es[N << 1];
    ll ans = 0;
    char st[N];

    void add(char ch) {
        int c = ch - 'a';
        int p = lst, np = lst = ++tot;
        o[np].len = o[p].len + 1;
        f[np] = 1;
        
        while (p && !o[p].ch[c]) o[p].ch[c] = np, p = o[p].fa;
        if (!p) o[np].fa = 1;
        else {
            int q = o[p].ch[c];
            if (o[q].len == o[p].len + 1) o[np].fa = q;
            else {
                int nq = ++tot; o[nq] = o[q];
                o[nq].len = o[p].len + 1;
                o[q].fa = o[np].fa = nq;
                while (p && o[p].ch[c] == q) o[p].ch[c] = nq, p = o[p].fa;
           }
        }
    }
    
    void ins(char st[]) {
        int len = strlen(st);
        For (i, 0, len - 1) add(st[i]);
    }

    void dfs(int u) {
        for (auto &v : es[u]) {
            dfs(v); f[u] += f[v];
        }
        if (f[u] > 1) ans = max(ans, 1ll * f[u] * o[u].len);
    }

    int main() {
        io >> st; ins(st);
        For (i, 1, tot) es[o[i].fa].push_back(i);
        
        dfs(1);
        
        printf("%lld", ans);
        
        return 0;
    }
}

int main() {
    return SAM::main();
}
