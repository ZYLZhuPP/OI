#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)

struct IO {
    char c; int f;
#define gc() getchar()
    template<class C>
    IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
    }
    bool operator ~ () const { return ~c; }
} io;

int T, a[40], b[40], n, m, K;
char s[40];

inline void out() {
    int m = 39;
    while (!b[m]) m--;
    rFor (i, m, 1) putchar(b[i] ^ 48);
    puts("");
}

inline void solve(int n, int K) {
    int m = 1;
    if (!K) {
        while (a[m] == 9) m++;
        b[m] = 1;
    } else {
        while (!a[m]) m++;
        int l = m, r = m, R = m, x = 0;
        do {
            l = r = R;
            for (; r <= n && a[r] ^ 9 && x + (r - l) < K; ++r);
            R = r;
            for (; R <= n && a[R] == 9; ++R);
            x += R - l;
        } while (x < K && R <= n);
        if (x >= K) m = R - K;
        if (!a[m]) {
            int c = 0;
            while (!a[m]) c++, m++;
            K -= c;
            int d = m - 1;
            while (!a[d]) d--;
            solve(d, c);
        }
        bool flag = 0;
        while (K) {
            b[m] = 10 - flag - a[m], flag = 1;
            if (!--K) break;
            m++;
        }
    }
}

int main() {
    io >> T;
    while (T--) {
        memset(a, 0, sizeof a); memset(b, 0, sizeof b);
        scanf("%s", s + 1); io >> K;
        n = strlen(s + 1); For (i, 1, n) a[i] = s[n - i + 1] ^ 48;
        solve(n, K);
        out();
    }

    return 0;
}