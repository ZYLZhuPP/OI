#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e3 + 5;

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

int n, pos[N], s[N], a[N];

inline int query(int l, int r) {
    printf("? %d %d\n", l, r); fflush(stdout);
    int x; io >> x;
    return x;
}

int main() {
    io >> n;
    pos[1] = 1;
    For (i, 2, n) {
        int l = 1, r = i - 1, res = 0;
        while (l <= r) {
            int m = (l + r) >> 1, p = pos[m];
            int x = query(p, i);
            if (p == i - 1) {
                if (x) r = m - 1;
                else res = m, l = m + 1;
            } else {
                int y = query(p + 1, i);
                if (x ^ y ^ s[p]) r = m - 1;
                else res = m, l = m + 1;
            }
        }
        rFor (j, i, res + 2) s[pos[j] = pos[j - 1]] ^= 1;
        pos[res + 1] = i;
    }
    For (i, 1, n) a[pos[i]] = i;
    putchar('!'); For (i, 1, n) printf(" %d", a[i]);

    return 0;
}
