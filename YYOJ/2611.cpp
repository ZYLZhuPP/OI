#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e5 + 5;
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }

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

int T, n, m, ans;
array<int, 2 > a[N];

int main() {
    io >> T;
    while (T--) {
        ans = 0;
        io >> n >> m;
        For (i, 1, n) io >> a[i][0], a[i][1] = 1;
        For (i, 1, m) io >> a[n + i][0], a[n + i][1] = 0;
        sort(a + 1, a + n + m + 1);
        int lst = -1, cnt = 0;
        For (i, 1, n + m) {
            if (!a[i][1]) cnt = 0, lst = a[i][0];
            else if (a[i][0] ^ lst) cmax(ans, ++cnt);
        }
        printf("%d\n", ans);
    }

    return 0;
}
