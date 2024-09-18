#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5, Mo = 998244353;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, int y) { x = mo(x + y); }

struct IO {
    char c; int f;
#define gc() getchar()
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
    }
    inline bool operator ~ () { return ~c; }
} io;

int n, P, a[N], sum, f[N], l1[N], l2[N], pre1[N], pre2[N];
int B, bl[318], br[318], be[N], p[N], bp[318], s[318][2 * N];

inline void add(int x) {
    add(s[be[x]][p[x]], f[x]);
    if (p[x] <= bp[be[x]]) add(sum, f[x]);
}

inline void del(int x) {
    add(s[be[x]][p[x]], -f[x]);
    if (p[x] <= bp[be[x]]) add(sum, -f[x]);
}

inline void up(int x, int d) {
    del(x); p[x] += d; add(x);
}

inline void upd(int l, int r, int d) {
    if (l > r) return;
    int L = be[l], R = be[r];
    if (L == R) For (i, l, r) up(i, d);
    else {
        For (i, L + 1, R - 1) {
            if (d == 1) add(sum, -s[i][bp[i]]);
            else add(sum, s[i][bp[i] + 1]);
            bp[i] -= d;
        }
        For (i, l, br[L]) up(i, d);
        For (i, bl[R], r) up(i, d);
    }
}

int main() {
    io >> n >> P;
    For (i, 1, n) io >> a[i], pre1[i] = l1[a[i]], pre2[i] = l2[a[i]], l2[a[i]] = l1[a[i]], l1[a[i]] = i;

    B = sqrt(n);
    For (i, 1, B) bl[i] = br[i - 1] + 1, br[i] = i * B, bp[i] = P;
    bl[1] = 0; br[B] = n;
    For (i, 1, B) For (j, bl[i], br[i]) be[j] = i;

    f[0] = 1; add(0);
    For (i, 1, n) {
        upd(pre1[i], i - 1, 1); upd(pre2[i], pre1[i] - 1, -1);
        f[i] = sum; add(i);
    }
    printf("%d", f[n]);

    return 0;
}