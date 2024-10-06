#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)

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

int T;

const int c[2][2] = {{1, 0}, {1, 1}};
inline int C(int n, int m) {
    if (n < 2 && m < 2) return c[n][m];
    return C(n >> 1, m >> 1) & c[n & 1][m & 1];
}

int main() {
    io >> T;
    int op, n, m;
    while (T--) {
        io >> op >> n >> m;
        if (op == 1) {
            if (m > n || m < n - n / 2) putchar('0');
            else putchar('0' + C(n / 2, n - m));
        } else {
            if (!m && !n) putchar('1');
            else if (m > n || !m) putchar('0');
            else putchar('0' + C(n - m / 2 - 1, (m - 1) / 2));
        }
    }

    return 0;
}
