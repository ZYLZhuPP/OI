#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e4 + 5, Mo = 1e9 + 7;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }
inline void mul(int &x, const int &y) { x = ml(x, y); }

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
    inline bool operator ~ () const { return ~c; }
} io;

int n, a[N], cnt[4], ans;

int main() {
    io >> n;
    For (i, 1, n) io >> a[i];
    For (i, 0, 29) {
        cnt[0] = cnt[1] = 0;
        For (j, 1, n) cnt[a[j] >> i & 1]++;
        add(ans, ml(ml(cnt[0], cnt[1]), ml(1 << i, 1 << i)));
    }
    For (i, 0, 29) For (j, i + 1, 29) {
        cnt[0] = cnt[1] = cnt[2] = cnt[3] = 0;
        For (k, 1, n) cnt[(a[k] >> i & 1) << 1 | (a[k] >> j & 1)]++;
        add(ans, ml(mo(ml(cnt[0], cnt[3]) + ml(cnt[1], cnt[2])), ml(2 << i, 1 << j)));
    }
    mul(ans, 2);
    printf("%d", ans);

    return 0;
}
