#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e6 + 5;
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }

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

int T, n, m, cnt[N], tot, ans;
array<int, 2 > a[N];

int main() {
    io >> T;
    while (T--) {
        tot = 0;
        io >> n;
        For (i, 1, n) {
            io >> cnt[i];
            int x;
            For (j, 1, cnt[i]) io >> x, a[++tot] = {x, i};
        }
        sort(a + 1, a + tot + 1); ans = a[tot][0] - a[1][0];
        int l = 1; while (cnt[a[l][1]] > 1) cnt[a[l++][1]]--;
        rFor (i, tot, 1) {
            cmin(ans, a[i][0] - a[l][0]);
            if (!--cnt[a[i][1]]) {
                while (l > 1 && a[l - 1][1] ^ a[i][1]) cnt[a[--l][1]]++;
                if (l <= 1) break; else cnt[a[--l][1]]++;
            }
        }
        printf("%d\n", ans);
    }

    return 0;
}
