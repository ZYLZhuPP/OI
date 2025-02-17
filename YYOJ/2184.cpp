#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5;

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

int T, n, a[N], mx1, mx2, c1, c2, cnt[N], s1, s2, ans;

int main() {
    io >> T;
    while (T--) {
        mx1 = mx2 = 0; c1 = c2 = 1;
        io >> n;
        For (i, 1, n) {
            int x;
            io >> x; a[i] = x;
            cnt[x]++;
            if (c1 == x) mx1 = cnt[x];
            else if (cnt[x] > mx1) mx2 = mx1, c2 = c1, mx1 = cnt[x], c1 = x;
            else if (cnt[x] > mx2) mx2 = cnt[x], c2 = x;
        }
        ans = mx1 | mx2;
        if (mx1 & mx2) ans |= (1 << (31 - __builtin_clz(mx1 & mx2))) - 1;
        printf("%d\n", ans);
        s1 = s2 = 0;
        For (i, 1, n) {
            if (a[i] == c1) s1++;
            if (a[i] == c2) s2++;
            if ((s1 | s2) == ans) {
                printf("%d %d\n%d %d\n", 1, i, c1, c2);
                break;
            }
        }
        For (i, 1, n) cnt[a[i]]--;
    }

    return 0;
}
