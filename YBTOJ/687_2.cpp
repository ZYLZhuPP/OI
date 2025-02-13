#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
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
    template<class C>
    inline IO& operator >> (C *x) {
        while ((c = gc()) < 33 && ~c);
        while (c > 32) *x++ = c, c = gc();
        *x = 0; return *this;
    }
    inline bool operator ~ () { return ~c; }
} io;

int n;
ll ans;
char a[N];

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
    io >> n;
    io >> (a + 1);
    using namespace SAM;
    ins(a);
    For (i, 1, tot) ans += len[i] - len[fa[i]];
    printf("%lld", ans);
    
    return 0;
}
