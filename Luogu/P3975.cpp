#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 5e5 + 5;

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

int n, f[N << 1], T, cnt[N << 1], sd[N << 1], K;
ll s[N << 1];
char a[N];

inline int mp(const char c) { return c-'a'; }
namespace SAM {
    int tot = 1, to[N << 1][26], fa[N << 1], len[N << 1], ed = 1;
    void add(const int c) {
        int p = ed, np = ed = ++tot; f[np] = 1;
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
using namespace SAM;

void out(int u, int k) {
    if (k <= f[u]) return;
    k -= f[u];
    For (c, 0, 25) if (to[u][c]) {
        int v = to[u][c];
        if (k > s[v]) k -= s[v];
        else {
            putchar(c + 'a');
            out(v, k);
            return;
        }
    }
}

int main() {
    io >> (a + 1); n = strlen(a + 1);
    io >> T >> K;
    ins(a);
    
    For (i, 1, tot) cnt[len[i]]++;
    For (i, 1, tot) cnt[i] += cnt[i - 1];
    For (i, 1, tot) sd[cnt[len[i]]--] = i;
    rFor (i, tot, 1) f[fa[sd[i]]] += f[sd[i]];
    For (i, 1, tot) T? (s[i] = f[i]): (s[i] = f[i] = 1);
    s[1] = f[1] = 0;

    rFor (i, tot, 1) For (c, 0, 25) if (to[sd[i]][c]) s[sd[i]] += s[to[sd[i]][c]];
    if (s[1] < K) puts("-1");
    else out(1, K);

    return 0;
}
