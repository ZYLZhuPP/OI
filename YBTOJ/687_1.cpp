#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
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
    inline bool operator ~ () { return ~c; }
} io;

char a[N], b[N];

inline int mp(const char c) { return c<'a'? 26 + c-'A': c-'a'; }
namespace SAM {
    int tot = 1, to[N << 1][52], fa[N << 1], len[N << 1], ed = 1;
    void add(const int c) {
        int p = ed, np = ed = ++tot;
        len[np] = len[p] + 1;
        while (p && !to[p][c]) to[p][c] = np, p = fa[p];
        if (!p) fa[np] = 1;
        else {
            int q = to[p][c];
            if (len[q] == len[p] + 1) fa[np] = q;
            else {
                int nq = ++tot; memcpy(to[nq], to[q], sizeof to[q]);
                fa[nq] = fa[q]; fa[q] = fa[np] = nq;
                len[nq] = len[p] + 1;
                while (p && to[p][c] == q) to[p][c] = nq, p = fa[p];
            }
        }
    }
    void ins(const char *s) {
        int n = strlen(s + 1);
        For (i, 1, n) add(mp(s[i]));
    }
}

int main() {
    io >> (a + 1);
    io >> (b + 1);
    using namespace SAM;
    ins(a);
    int n = strlen(b + 1), p = 1, ok = 1;
    For (i, 1, n) {
        int c = mp(b[i]);
        if (to[p][c]) p = to[p][c];
        else { ok = 0; break; }
    }
    puts(ok? "Yes": "No");
    
    return 0;
}
