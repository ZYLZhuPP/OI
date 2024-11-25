#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e7 + 5;
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

int T, n;
char s[N];

inline void out(int l, int r) {
    while (r <= n) putchar('0' + (s[l] ^ s[r])), l++, r++;
    puts("");
}

int main() {
    io >> T;
    while (T--) {
        bool flag = 0;
        io >> n;
        scanf("%s", s + 1);
        int pos = n + 1;
        For (i, 1, n) {
            if (s[i] & 1) cmin(pos, i);
            else flag = 1;
        }
        if (pos > n) { puts("0"); continue; }
        if (!flag) { printf("%s0\n", s + 2); continue; }
        int p = pos; while (p <= n && s[p] & 1) p++;
        if (p > n) { printf("%s\n", s + pos); continue; }
        int q = p; while (q <= n && !(s[q] & 1)) q++;
        For (i, 1, p - pos) putchar('1');
        if (q - p >= p - pos) out(pos, p);
        else out(p - (q - p), p);
    }

    return 0;
}
